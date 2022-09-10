#include "move.h"

bool moveLegal(CardStorage *from, CardStorage *to) {
    auto card_ref = from->topCard();
    if (!card_ref.has_value())
        return false;

    return to->canAccept(*card_ref);
}

void move(CardStorage *from, CardStorage *to) {
    if (!moveLegal(from, to))
        return;

    to->acceptCard(*from->getCard());
}

std::vector<RawMove> availableMoves(Locations froms, Locations tos) {
	std::vector<RawMove> moves;

	for (auto from : froms) {
		for (auto to : tos) {
			if (moveLegal(from, to))
				moves.push_back({from, to});
		}
	}

	return moves;
}
