#include "card-storage.h"

bool operator< (const std::optional<Card> &lhs, const std::optional<Card> rhs) {
    if (lhs.has_value()) {
        if (rhs.has_value())
            return *lhs < *rhs;
        else
            return false;
    } else {
        return false;
    }
}

bool operator== (const std::optional<Card> &lhs, const std::optional<Card> rhs) {
    if (lhs.has_value() && rhs.has_value()) {
        return *lhs == *rhs;
    } else if (!lhs.has_value() && !rhs.has_value()) {
        return true;
    } else {
        return false;
    }
}

bool HomeDestination::canSitOn(const Card &base, const Card &candidate) {
	return candidate.color == base.color && candidate.value == base.value + 1;
}

bool HomeDestination::canAccept(const Card & card) const {
    if (storage_.size() == 0)
		return card.value == 1;
    else
		return canSitOn(*topCard(), card);
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

bool operator< (const HomeDestination &lhs, const HomeDestination &rhs) {
    return lhs.topCard() < rhs.topCard();
}

bool operator== (const HomeDestination &lhs, const HomeDestination &rhs) {
    return lhs.topCard() == rhs.topCard();
}

bool operator< (const WorkStack &lhs, const WorkStack &rhs) {
    return lhs.storage_ < rhs.storage_;
}

bool operator== (const WorkStack &lhs, const WorkStack &rhs) {
    return lhs.storage_ == rhs.storage_;
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

bool operator< (const FreeCell &lhs, const FreeCell &rhs) {
    return lhs.topCard() < rhs.topCard();
}

bool operator== (const FreeCell &lhs, const FreeCell &rhs) {
    return lhs.topCard() == rhs.topCard();
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

bool WorkStack::canSitOn(const Card &base, const Card &candidate) {
	bool oppposing_render_color = render_color_map.at(candidate.color) != render_color_map.at(base.color);
	bool one_less = candidate.value == base.value - 1;
	return oppposing_render_color && one_less;
}


bool WorkStack::canAccept(const Card & card) const {
    if (storage_.size() == 0)
        return true;
    else
		return canSitOn(*topCard(), card);
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
