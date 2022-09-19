#include "card-storage.h"

bool HomeDestination::canAccept(const Card & card) const {
    if (storage_.size() == 0) {
		return card.value == 1;
    } else {
		bool matching_color = card.color == topCard()->color;
		bool one_higher = card.value == topCard()->value + 1;
		return matching_color && one_higher;
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


bool FreeCell::canAccept([[maybe_unused]] const Card & card) const {
	return !cell_.has_value();
}

bool FreeCell::acceptCard(const Card & card) {
	auto move_ok = canAccept(card);
    if (move_ok)
        cell_.emplace(card);

    return move_ok;
}

FreeCell & FreeCell::operator=(FreeCell &other) {
	if (other.cell_.has_value())
		cell_.emplace(*other.cell_);
	else
		cell_ = std::nullopt;

	return *this;
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


bool WorkStack::canAccept(const Card & card) const {
    if (storage_.size() == 0) {
        return true;
    } else {
		bool oppposing_render_color = render_color_map.at(card.color) != render_color_map.at(topCard()->color);
		bool one_less = card.value == topCard()->value - 1;
		return oppposing_render_color && one_less;
    }
}

bool WorkStack::acceptCard(const Card & card) {
	auto move_ok = canAccept(card);
	if (move_ok) 
		storage_.push_back(card);

	return move_ok;
}

const std::optional<Card> WorkStack::topCard() const {
	if (storage_.size() > 0)
		return storage_.back();
	else
		return std::nullopt;
}


std::optional<Card> WorkStack::getCard() {
	if (storage_.size() > 0) {
        auto card = storage_.back();
        storage_.pop_back();
		return card;
	} else {
		return std::nullopt;
    }
}

void WorkStack::forceCard(const Card & card) {
	storage_.push_back(card);
}

std::ostream& operator<< (std::ostream& os, const WorkStack & stack) {
	if (stack.storage_.size() == 0) {
        os << "_"; 
    } else {
        os << stack.storage_[0];
        for (auto card_it = stack.storage_.begin() + 1; card_it != stack.storage_.end(); ++card_it) {
            os << " " << *card_it;
        }
    }

    return os;
}

size_t WorkStack::nbCards() const {
	return storage_.size();
}
