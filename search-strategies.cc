#include "search-strategies.h"

#include <chrono>
#include <thread>
#include <algorithm>

DummySearch::DummySearch(size_t max_depth, size_t nb_attempts, std::default_random_engine &rng) :
		max_depth_(max_depth),
		nb_attempts_(nb_attempts),
		rng_(rng) {
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
