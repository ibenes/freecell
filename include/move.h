#ifndef MOVE_H
#define MOVE_H

#include "card-storage.h"

#include <utility>
#include <iterator>

bool moveLegal(const CardStorage *from, const CardStorage *to) ;
void move(CardStorage *from, CardStorage *to) ;

using RawMove = std::pair<const CardStorage *, const CardStorage *>;

template <typename T_ptr_It_from, typename T_ptr_It_to>
std::vector<RawMove> availableMoves(T_ptr_It_from from_begin, T_ptr_It_from from_end, T_ptr_It_to to_begin, T_ptr_It_to to_end) {
	std::vector<RawMove> moves;

	for (auto from = from_begin; from != from_end; ++from) {
		for (auto to = to_begin; to != to_end; ++to) {
			if (moveLegal(*from, *to))
				moves.push_back({*from, *to});
		}
	}

	return moves;
}

#endif
