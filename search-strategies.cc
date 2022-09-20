#include "search-strategies.h"

#include <chrono>
#include <thread>
#include <algorithm>

DummySearch::DummySearch(size_t max_len, std::default_random_engine &rng) :
		max_len_(max_len),
		rng_(rng) {
	; // just for initializer list	
}

std::vector<SearchAction> DummySearch::solve(const SearchState &init_state) {
	std::vector<SearchAction> solution;

	SearchState working_state(init_state);
	while(true) {
		auto actions = working_state.actions();

		// detect a dead end
		if (actions.size() == 0)
			return {};

		auto action = actions[0];
		// actually, pick a random action
		std::sample(actions.begin(), actions.end(), &action, 1, rng_);

		solution.push_back(action);

		// detect a likely loop
		if (solution.size() > 1000)
			return {};

		working_state = action.execute(working_state);

		if (working_state.isFinal())
			break;
	}

	return solution;
}
