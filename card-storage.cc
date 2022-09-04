#include "card-storage.h"

bool HomeDestination::canAccept(const Card & card) {
    if (topCard() == nullptr) {
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

bool HomeDestination::acceptCard(std::unique_ptr<Card> card) {
	auto move_ok = canAccept(*card);
	if (move_ok) 
		storage_.push_back(std::move(card));

	return move_ok;
}

const Card * HomeDestination::topCard() const {
	if (storage_.size() == 0)
		return nullptr;
	else
		return storage_.back().get();
}


std::unique_ptr<Card> HomeDestination::getCard() {
	if (storage_.size() == 0) {
		return nullptr;
	} else {
		std::unique_ptr<Card> card = std::move(storage_.back());
		storage_.pop_back();
		return card;
	}
}

std::ostream& operator<< (std::ostream& os, const HomeDestination & hd) {
	auto card = hd.topCard();
    if (card == nullptr)
        os << "_"; 
    else
        os << *card;

    return os;
}


bool FreeCell::canAccept(const Card & card) {
    if (cell_ == nullptr) {
        return true;
    } else {
        return false;
    }
}

bool FreeCell::acceptCard(std::unique_ptr<Card> card) {
	auto move_ok = canAccept(*card);
    if (move_ok)
        cell_ = std::move(card);

    return move_ok;
}

const Card * FreeCell::topCard() const {
	return cell_.get();
}

std::unique_ptr<Card> FreeCell::getCard() {
	if (cell_ == nullptr) {
		return nullptr;
	} else {
		std::unique_ptr<Card> card = std::move(cell_);
		cell_ = nullptr;
		return card;
	}
}


Card const * FreeCell::card() const {
    return cell_.get();
}

std::ostream& operator<< (std::ostream& os, const FreeCell & fc) {
    auto card = fc.card();
    if (card == nullptr) {
        os << "_"; 
    } else {
        os << *card;
    }

    return os;
}
