#include "search-strategies.h"
#include <set>

std::vector<SearchAction> BreadthFirstSearch::solve(const SearchState& init_state) {
	std::vector<SearchAction> solution;
	SearchState working_state(init_state);



	//for (size_t depth = 0; depth < max_depth_; ++depth) {
	//	auto actions = working_state.actions();

	//	// on a dead end
	//	if (actions.size() == 0)
	//		break; // start over

	//	auto action = actions[0];
	//	// actually, pick a random action
	//	std::sample(actions.begin(), actions.end(), &action, 1, rng_);

	//	solution.push_back(action);
	//	working_state = action.execute(working_state);

	//	if (working_state.isFinal())
	//		return solution;
	//}

	return {};
}

std::vector<SearchAction> DepthFirstSearch::solve(const SearchState& init_state) {
	return {};
}

double StudentHeuristic::distanceLowerBound(const GameState& state) const {
	return 0;
}

std::vector<SearchAction> AStarSearch::solve(const SearchState& init_state) {
	return {};
}
