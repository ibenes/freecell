#include "move.h"

bool moveLegal(const CardStorage *from, const CardStorage *to) {
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
