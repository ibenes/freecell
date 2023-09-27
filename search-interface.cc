#include "search-interface.h"
#include "game.h"

#include <cassert>
#include <algorithm>


unsigned long long SearchState::nbExpanded() {
    return SearchState::nb_expanded;
}

bool operator<(const SearchState &a, const SearchState &b) {
    return a.state_ < b.state_;
}

SearchState SearchAction::execute(const SearchState& state) const {
	SearchState new_state(state);
	bool succeeded = new_state.execute(*this);
	assert(succeeded);

	return new_state;
}

const Location& SearchAction::from() const {
    return from_;
}

const Location& SearchAction::to() const {
    return to_;
}

bool SearchState::execute(const SearchAction& action) {
	auto from_ptr = ptrFromLoc(state_, action.from());
	auto to_ptr = ptrFromLoc(state_, action.to());

	if (!moveLegal(from_ptr, to_ptr))
		return false;

	move(const_cast<CardStorage *>(from_ptr), const_cast<CardStorage *>(to_ptr));

	runSafeMoves_();

    SearchState::nb_expanded++;

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

unsigned long long SearchState::nb_expanded = 0;

std::vector<SearchAction> SearchState::actions() const {
	auto raw_moves = availableMoves(
		state_.non_homes.begin(),
		state_.non_homes.end(),
		state_.all_storage.begin(),
		state_.all_storage.end()
	);	

	std::vector<SearchAction> moves;
	std::transform(
		raw_moves.begin(),
		raw_moves.end(),
		std::back_inserter(moves),
		[&](RawMove raw_move){
			return SearchAction{locFromPtr(state_, raw_move.first), locFromPtr(state_, raw_move.second)};
		}
	);
	return moves;
}

std::ostream& operator<< (std::ostream& os, const SearchState & state) {
	os << state.state_;
	return os;
}

std::ostream& operator<< (std::ostream& os, const SearchAction & action) {
	os << action.from_ << " " << action.to_;
	return os;
}
