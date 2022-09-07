#include "card-storage.h"

bool HomeDestination::canAccept(const Card & card) {
    if (storage_.size() == 0) {
        if (card.value == 1) {
            return true;
        } else {
            return false;
        }
    } else {
        if (card.color == topCard()->color && card.value == topCard()->value + 1) {
            return true;
        } else {
            return false;
        }
    }
}

bool HomeDestination::acceptCard(const Card & card) {
	auto move_ok = canAccept(card);
	if (move_ok) 
		storage_.push_back(card);

	return move_ok;
}

const std::optional<Card> HomeDestination::topCard() const {
	if (storage_.size() > 0)
		return storage_.back();
	else
		return std::nullopt;
}


std::optional<Card> HomeDestination::getCard() {
	auto card = storage_.back();
	storage_.pop_back();
	return card;
}

std::ostream& operator<< (std::ostream& os, const HomeDestination & hd) {
	if (hd.storage_.size() == 0)
        os << "_"; 
    else
        os << *hd.topCard();

    return os;
}


bool FreeCell::canAccept([[maybe_unused]] const Card & card) {
    if (cell_.has_value()) {
        return false;
    } else {
        return true;
    }
}

bool FreeCell::acceptCard(const Card & card) {
	auto move_ok = canAccept(card);
    if (move_ok)
        cell_.emplace(card);

    return move_ok;
}

const std::optional<Card> FreeCell::topCard() const {
	return cell_;
}

std::optional<Card> FreeCell::getCard() {
	auto card = std::move(cell_);
	cell_.reset();
	return card;
}

std::ostream& operator<< (std::ostream& os, const FreeCell & fc) {
    auto card = fc.topCard();
    if (card.has_value()) {
        os << *card;
    } else {
        os << "_"; 
    }

    return os;
}
