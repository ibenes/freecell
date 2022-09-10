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
	moves.push_back({froms[0], tos[0]});
	return moves;
}
