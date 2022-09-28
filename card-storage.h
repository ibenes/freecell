#ifndef CARD_STORAGE_H
#define CARD_STORAGE_H

#include "card.h"

#include <string>
#include <vector>
#include <optional>


class CardStorage {
public:
	virtual bool canAccept(const Card & card) const = 0;
    virtual bool acceptCard(const Card & card) = 0;
    virtual const std::optional<Card> topCard() const = 0;
    virtual std::optional<Card> getCard() = 0;
	virtual ~CardStorage() {};
};


class HomeDestination : public CardStorage {
public:
	static bool canSitOn(const Card &base, const Card &candidate);
	bool canAccept(const Card & card) const override;
    bool acceptCard(const Card & card) override;
    const std::optional<Card> topCard() const override;
    std::optional<Card> getCard() override;

    friend std::ostream& operator<< (std::ostream& os, const HomeDestination & hd) ;

private:
    std::vector<Card> storage_;
};

bool operator< (const HomeDestination &lhs, const HomeDestination &rhs) ;
bool operator== (const HomeDestination &lhs, const HomeDestination &rhs) ;


class WorkStack : public CardStorage {
public:
	static bool canSitOn(const Card &base, const Card &candidate);
	bool canAccept(const Card & card) const override;
    bool acceptCard(const Card & card) override;
    const std::optional<Card> topCard() const override;
    std::optional<Card> getCard() override;

	size_t nbCards() const;

	// avoid canAccept, simply places the card on top
	// useful for game setup
    void forceCard(const Card & card);

    friend std::ostream& operator<< (std::ostream& os, const WorkStack & stack) ;
    friend bool operator< (const WorkStack &lhs, const WorkStack &rhs) ;
    friend bool operator== (const WorkStack &lhs, const WorkStack &rhs) ;

private:
    std::vector<Card> storage_;

public:
    const decltype(storage_) &storage() const {return storage_;}
};

bool operator< (const WorkStack &lhs, const WorkStack &rhs) ;
bool operator== (const WorkStack &lhs, const WorkStack &rhs) ;


class FreeCell : public CardStorage {
public:
	FreeCell & operator=(FreeCell &other) ;

	bool canAccept(const Card & card) const override;
    bool acceptCard(const Card & card) override;
    const std::optional<Card> topCard() const override;
    std::optional<Card> getCard() override;

private:
    std::optional<Card> cell_;
};

bool operator< (const FreeCell &lhs, const FreeCell &rhs) ;
bool operator== (const FreeCell &lhs, const FreeCell &rhs) ;

std::ostream& operator<< (std::ostream& os, const FreeCell & fc) ;

#endif
