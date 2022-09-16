#include "game.h"
#include "move.h"

#include <algorithm>
#include <cassert>
#include <random>

template <typename In>
std::vector<CardStorage *> collect_location_pointers(In begin, In end) {
    std::vector<CardStorage *> adresses;
    for (auto it=begin; it != end; ++it)
        adresses.push_back(it);

    return adresses;
}

GameState::GameState(void) {
    assert(nb_freecells == nb_homes);
    for (int i=0; i<nb_freecells; ++i)
        non_homes[i] = &free_cells[i];

    for (int i=0; i<nb_stacks; ++i)
        non_homes[i + nb_freecells] = &stacks[i];
}

std::vector<Card> topCards(const GameState &gs) {
    std::vector<Card> cards;

    for (auto &cs : gs.non_homes) {
        auto opt_card = cs->topCard();
        if (opt_card.has_value())
            cards.push_back(*opt_card);
    }

    return cards;
}

int moveCardsFromHomes(GameState *gs, int max_nb_cards, size_t stack_begin, size_t stack_end, std::default_random_engine rng) {
    int nb_cards_moved = 0;
    for (; nb_cards_moved < max_nb_cards; ++nb_cards_moved) {
        std::vector<CardStorage *> considered_froms{&gs->homes[nb_cards_moved % gs->homes.size()]};
        std::vector<CardStorage *> considered_tos = collect_location_pointers(gs->stacks.begin() + stack_begin, gs->stacks.begin() + stack_end);

        auto moves = availableMoves(
            considered_froms.begin(),
            considered_froms.end(),
            considered_tos.begin(),
            considered_tos.end()
        );

        if (moves.size() == 0)
            break;

        int pick = std::uniform_int_distribution<std::mt19937::result_type>(0, moves.size()-1)(rng);
        // we have a non-const access to GameState (gs), so we are allowed to de-const the pointers in RawMove
        move(const_cast<CardStorage *>(moves[pick].first), const_cast<CardStorage *>(moves[pick].second));
    }

    return nb_cards_moved;
}

void forceMove(CardStorage *from, WorkStack *to) {
    to->forceCard(*from->getCard());
}

const CardStorage * ptrFromLoc(const GameState &gs, Location const& loc) {
    switch (loc.cl) {
        case LocationClass::FreeCells:
            return &gs.free_cells[loc.id];
            break;
        case LocationClass::Homes:
            return &gs.homes[loc.id];
            break;
        case LocationClass::Stacks:
            return &gs.stacks[loc.id];
            break;
        default:
            return nullptr;
    }
}

bool operator== (const Location &lhs, const Location &rhs) {
    return lhs.cl == rhs.cl && lhs.id == rhs.id;
}

bool operator!= (const Location &lhs, const Location &rhs) {
    return !(lhs == rhs);
}

// to be used only with continuous-storage containers
template<typename T>
bool isInContainer(const CardStorage *ptr, const T& container) {
    return ptr >= &container[0] && ptr <= &container[container.size()-1];
}

// to be used only with continuous-storage containers
template<typename T>
long positionInContainer(const CardStorage *ptr, const T& container) {
    return static_cast<const decltype(&container[0])>(ptr) - &container[0];
}


Location locFromPtr(const GameState &gs, const CardStorage *ptr) {
    if (isInContainer(ptr, gs.homes))
        return {LocationClass::Homes, positionInContainer(ptr, gs.homes)};
    else if (isInContainer(ptr, gs.stacks))
        return {LocationClass::Stacks, positionInContainer(ptr, gs.stacks)};
    else if (isInContainer(ptr, gs.free_cells))
        return {LocationClass::FreeCells, positionInContainer(ptr, gs.free_cells)};
    else
        throw std::out_of_range("Pointer doesn't match any of homes, freecells or stacks in the given GameState");
}

void initializeGameState(GameState *gs, std::default_random_engine &rng) {
    for (size_t i=0; i<colors_list.size(); ++i) {
        for (int j=1; j <= king_value; ++j)
            gs->homes[i].acceptCard({colors_list[i], j});
    }

    moveCardsFromHomes(gs, 20, 0, 5, rng);
    moveCardsFromHomes(gs, 32, 0, 8, rng);
}

std::optional<std::pair<CardStorage *, WorkStack *>> findIrreversibleMove(GameState *gs, std::default_random_engine &rng) {
    // number of cards that cannot be moved from the given stack 
    // as it is irreversibely placed in its location
    std::vector<size_t> frozen_level(gs->stacks.size(), 0);

    std::vector<CardStorage *> possible_from;
    for (auto &fc : gs->free_cells) {
        if (fc.topCard().has_value())
            possible_from.push_back(&fc);
    }
    for (size_t i=0; i < gs->stacks.size(); ++i) {
        auto &stack = gs->stacks[i];
        if (stack.topCard().has_value() && stack.nbCards() > frozen_level[i])
            possible_from.push_back(&stack);
    }
    if (possible_from.size() == 0)
        return std::nullopt;

    int pick_from = std::uniform_int_distribution<std::mt19937::result_type>(0, possible_from.size()-1)(rng);
    auto from = possible_from[pick_from];

    std::vector<WorkStack *> possible_to;
    for (size_t i=0; i < gs->stacks.size(); ++i) {
        auto &stack = gs->stacks[i];
        bool move_elsewhere = &stack != from;
        bool stack_not_overfull =stack.nbCards() <= 7;
        if (move_elsewhere && stack_not_overfull)
            possible_to.push_back(&stack);
    }
    if (possible_to.size() == 0)
        return std::nullopt;

    int pick_to = std::uniform_int_distribution<std::mt19937::result_type>(0, possible_to.size()-1)(rng);
    auto to = possible_to[pick_to];

    return std::make_pair(from, to);
}

auto findHomeFor(GameState &gs, Card card) -> decltype(gs.homes)::iterator {
    return std::find_if(
        gs.homes.begin(),
        gs.homes.end(),
        [&](CardStorage &cs){return cs.canAccept(card);}
    );
}

bool cardIsHome(const GameState &gs, Card card) {
    for (const auto & home : gs.homes) {
        auto opt_top_card = home.topCard();
        if (!opt_top_card.has_value())
            continue;

        if (opt_top_card->color == card.color && opt_top_card->value >= card.value)
            return true;
    }

    return false;
}

bool cardCouldGoHome(const GameState &gs, Card card) {
    // Aces can always go home
    // Thus, twos can go too, as an Ace will never need to rest
    // on a two
    if (card.value == 1 or card.value == 2)
        return true;

    auto render_color{render_color_map.at(card.color)}; 
    std::vector<Color> opposite_rc_colors;
    bool safe = true;

    for (auto & color : colors_list) {
        if (render_color_map.at(color) == render_color)
            continue;

        if (!cardIsHome(gs, {color, card.value-1}))
            safe = false;
    }

    return safe;
}

std::vector<RawMove> safeHomeMoves(GameState &gs) {
    std::vector<RawMove> moves;

    for (auto &cs : gs.non_homes) {
        auto opt_card = cs->topCard();

        if (!opt_card.has_value())
            continue;

        auto home_it = findHomeFor(gs, *opt_card);
        if (home_it != gs.homes.end() && cardCouldGoHome(gs, *opt_card))
            moves.push_back({cs, home_it});
    }

    return moves;
}

std::ostream& operator<< (std::ostream& os, const GameState & state) {
    os << "Homes: " <<
        state.homes[0] << " " <<
        state.homes[1] << " " <<
        state.homes[2] << " " <<
        state.homes[3] << "\n";

    os << "FreeCells: " <<
        state.free_cells[0] << " " <<
        state.free_cells[1] << " " <<
        state.free_cells[2] << " " <<
        state.free_cells[3] << "\n";

    for (auto stack : state.stacks) {
        os << stack << "\n";
    }

    return os;
}

