#include "search-strategies.h"

std::vector<SearchAction> DummySearch::solve(const SearchState &init_state) {
	std::vector<SearchAction> solution;
	solution.push_back(init_state.actions()[14]);

	return solution;
}
