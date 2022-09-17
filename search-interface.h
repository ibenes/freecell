#ifndef SEARCH_INTERFACE_H
#define SEARCH_INTERFACE_H

#include "move.h"
#include "game.h"

#include <ostream>

class SearchState;

class SearchAction {
public:
	SearchState execute(const SearchState& state) const ;

private:
	Location from;
	Location to;
};

class SearchState {
public:
	SearchState(GameState state) : state_(state) {}
	bool isFinal() const;
	std::vector<SearchAction> actions() const;

	bool execute(Location from, Location to);

    friend std::ostream& operator<< (std::ostream& os, const SearchState & hd) ;
private:
	void runSafeMoves_();
	GameState state_;
};

#endif
