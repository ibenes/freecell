#include "card-storage.h"

bool HomeDestination::acceptCard(std::unique_ptr<Card> card) {
    if (storage_.size() == 0) {
        if (card->value == 1) {
            storage_.push_back(std::move(card));
            return true;
        } else {
            return false;
        }
    } else {
        if (card->color == top()->color && card->value == top()->value + 1) {
            storage_.push_back(std::move(card));
            return true;
        } else {
            return false;
        }
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


bool FreeCell::acceptCard(std::unique_ptr<Card> card) {
    if (cell_ == nullptr) {
        cell_ = std::move(card);
        return true;
    } else {
        return false;
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
