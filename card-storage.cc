#include "card-storage.h"

bool HomeDestination::canAccept(const Card & card) {
    if (storage_.size() == 0) {
        if (card.value == 1) {
            return true;
        } else {
            return false;
        }
    } else {
        if (card.color == top()->color && card.value == top()->value + 1) {
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


std::unique_ptr<Card> HomeDestination::getCard() {
	if (storage_.size() == 0) {
		return nullptr;
	} else {
		std::unique_ptr<Card> card = std::move(storage_.back());
		storage_.pop_back();
		return card;
	}
}


Card const * HomeDestination::top() const {
    return storage_.rbegin()->get();
}

std::ostream& operator<< (std::ostream& os, const HomeDestination & hd) {
    if (hd.storage_.size() == 0) {
        os << "_"; 
    } else {
        os << *hd.top();
    }

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
