#ifndef SEARCH_STRATEGIES_H
#define SEARCH_STRATEGIES_H

#include "search-interface.h"

#include <vector>

class DummySearch : public SearchStrategyItf {
	std::vector<SearchAction> solve(const SearchState &init_state) override ;
};

#endif
