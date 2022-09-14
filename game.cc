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

std::vector<Card> topCards(const GameState &gs) {
    std::vector<Card> cards;

    for (auto &cs : gs.free_cells) {
        auto opt_card = cs.topCard();
        if (opt_card.has_value())
            cards.push_back(*opt_card);
    }

    for (auto &cs : gs.stacks) {
        auto opt_card = cs.topCard();
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

