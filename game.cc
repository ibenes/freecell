#include "game.h"
#include "move.h"

#include <algorithm>
#include <random>

template <typename In>
std::vector<CardStorage *> collect_location_pointers(In begin, In end) {
    std::vector<CardStorage *> adresses;
    for (auto it=begin; it != end; ++it)
        adresses.push_back(it);

    return adresses;
}

GameState::GameState(void) {
    for (int i=0; i<4; ++i)
        non_homes[i] = &free_cells[i];

    for (int i=0; i<8; ++i)
        non_homes[i + 4] = &stacks[i];
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

void initializeGameState(GameState *gs) {
    for (int i=0; i <= 13; ++i)
        gs->homes[0].acceptCard({Color::Heart, i});    

    for (int i=0; i <= 13; ++i)
        gs->homes[1].acceptCard({Color::Diamond, i});    

    for (int i=0; i <= 13; ++i)
        gs->homes[2].acceptCard({Color::Club, i});    

    for (int i=0; i <= 13; ++i)
        gs->homes[3].acceptCard({Color::Spade, i});    

    std::random_device dev;
    std::default_random_engine rng(dev());

    moveCardsFromHomes(gs, 26, 4, rng);
}

int moveCardsFromHomes(GameState *gs, int max_nb_cards, int nb_homes_available, std::default_random_engine rng) {
    int i = 0;
    for (; i < max_nb_cards; ++i) {
        auto moves = availableMoves(
            collect_location_pointers(gs->homes.begin(), gs->homes.end()),
            collect_location_pointers(gs->stacks.begin(), gs->stacks.begin()+nb_homes_available)
        );

        if (moves.size() == 0)
            break;

        int pick = std::uniform_int_distribution<std::mt19937::result_type>(0, moves.size()-1)(rng);
        move(moves[pick].first, moves[pick].second);
    }

    return i;
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

    auto render_color{render_color_map[card.color]}; 
    std::vector<Color> opposite_rc_colors;
    bool safe = true;

    for (auto & color : colors_list) {
        if (render_color_map[color] == render_color)
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
        if (home_it != gs.homes.end())
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

