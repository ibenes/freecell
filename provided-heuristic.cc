#include "search-strategies.h"

double compute_heuristic(const SearchState &state, const AStarHeuristicItf &heuristic) {
    return heuristic.distanceLowerBound(state.state_);
}

double OufOfHome_Pseudo::distanceLowerBound(const GameState &state) const {
    int cards_out_of_home = king_value * colors_list.size();
    for (const auto &home : state.homes) {
        auto opt_top = home.topCard();
        if (opt_top.has_value())
            cards_out_of_home -= opt_top->value;
    }

    return cards_out_of_home;
}

