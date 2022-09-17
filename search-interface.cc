#include "search-interface.h"
#include "game.h"

#include <cassert>

SearchState SearchAction::execute(const SearchState& state) const {
	SearchState new_state(state);
	bool succeeded = new_state.execute(from, to);
	assert(succeeded);

	return new_state;
}

bool SearchState::execute(Location from, Location to) {
	auto from_ptr = ptrFromLoc(state_, from);
	auto to_ptr = ptrFromLoc(state_, to);

	if (!moveLegal(from_ptr, to_ptr))
		return false;

	move(const_cast<CardStorage *>(from_ptr), const_cast<CardStorage *>(to_ptr));

	runSafeMoves_();

	return true;
}

void SearchState::runSafeMoves_() {
	std::vector<RawMove> safe_moves;
	while ((safe_moves = safeHomeMoves(state_)), safe_moves.size() > 0) {
		const CardStorage *from = safe_moves[0].first;
		const CardStorage *to = safe_moves[0].second;

		move(const_cast<CardStorage *>(from), const_cast<CardStorage *>(to));
	}
}

bool SearchState::isFinal() const {
	for (auto color : colors_list) {
		if (!cardIsHome(state_, {color, king_value}))
			return false;
	}

	return true;
}

std::ostream& operator<< (std::ostream& os, const SearchState & ss) {
	os << ss.state_;
	return os;
}
