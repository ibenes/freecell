#include "search-strategies.h"

#include <chrono>
#include <thread>
#include <algorithm>

double compute_heuristic(const SearchState &state, const AStarHeuristicItf &heuristic) {
    return heuristic.distanceLowerBound(state.state_);
}

DummySearch::DummySearch(size_t max_depth, size_t nb_attempts) :
        max_depth_(max_depth),
        nb_attempts_(nb_attempts),
        rng_(1337) {
	; // just for initializer list	
}

std::vector<SearchAction> DummySearch::solve(const SearchState &init_state) {
	for (size_t i = 0; i < nb_attempts_; ++i) {
		std::vector<SearchAction> solution;
		SearchState working_state(init_state);

		for (size_t depth = 0; depth < max_depth_ ; ++depth) {
			auto actions = working_state.actions();

			// on a dead end
			if (actions.size() == 0)
				break; // start over

			auto action = actions[0];
			// actually, pick a random action
			std::sample(actions.begin(), actions.end(), &action, 1, rng_);

			solution.push_back(action);
			working_state = action.execute(working_state);

			if (working_state.isFinal())
				return solution;
		}
	}

	return {};
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

