#ifndef SEARCH_STRATEGIES_H
#define SEARCH_STRATEGIES_H

#include "search-interface.h"

#include <vector>

class DummySearch : public SearchStrategyItf {
public:
	DummySearch(size_t max_len, std::default_random_engine &rng);
	std::vector<SearchAction> solve(const SearchState &init_state) override ;

private:
	size_t max_len_;
	std::default_random_engine rng_;
};

#endif
