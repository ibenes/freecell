#ifndef SEARCH_STRATEGIES_H
#define SEARCH_STRATEGIES_H

#include "search-interface.h"
#include "game.h"

#include <memory>
#include <vector>

class DummySearch : public SearchStrategyItf {
public:
	DummySearch(size_t max_depth, size_t nb_attempts);
	std::vector<SearchAction> solve(const SearchState &init_state) override ;

private:
	size_t max_depth_;
	size_t nb_attempts_;
	std::default_random_engine rng_;
};


class BreadthFirstSearch : public SearchStrategyItf {
public:
    BreadthFirstSearch(size_t mem_limit) : mem_limit_(mem_limit) {}
	std::vector<SearchAction> solve(const SearchState &init_state) override ;

private:
    size_t mem_limit_;
};

class DepthFirstSearch : public SearchStrategyItf {
public:
    DepthFirstSearch(int depth_limit, size_t mem_limit) :
        depth_limit_(depth_limit), mem_limit_(mem_limit) {}
	std::vector<SearchAction> solve(const SearchState &init_state) override ;
private:
    int depth_limit_;
    size_t mem_limit_;
};


class AStarHeuristicItf {
public:
    virtual double distanceLowerBound(const GameState &state) const =0;
};


class AStarSearch : public SearchStrategyItf {
public:
    AStarSearch(std::unique_ptr<AStarHeuristicItf> &&heuristic, size_t mem_limit) : 
        heuristic_(std::move(heuristic)),
        mem_limit_(mem_limit)
        {}
	std::vector<SearchAction> solve(const SearchState &init_state) override ;

private:
    const std::unique_ptr<AStarHeuristicItf> heuristic_;
    size_t mem_limit_;
};

// beware, this has been proven to NOT be a valid heuristic!
class OufOfHome_Pseudo : public AStarHeuristicItf {
public:
    double distanceLowerBound(const GameState &state) const override;
};

class StudentHeuristic : public AStarHeuristicItf {
public:
    double distanceLowerBound(const GameState &state) const override;
};

#endif
