#include "search-strategies.h"

#include <chrono>
#include <thread>

std::vector<SearchAction> DummySearch::solve(const SearchState &init_state) {
	std::vector<SearchAction> solution;
	solution.push_back(init_state.actions()[14]);

	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	return solution;
}
