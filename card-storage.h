#ifndef CARD_STORAGE_H
#define CARD_STORAGE_H

#include "card.h"

#include <string>
#include <memory>
#include <vector>


class CardStorage {
public:
	virtual bool canAccept(const Card & card) = 0;
    virtual bool acceptCard(std::unique_ptr<Card>) = 0;
	virtual ~CardStorage() = 0;
};


class HomeDestination : CardStorage {
public:
	bool canAccept(const Card & card) override;
    bool acceptCard(std::unique_ptr<Card>) override;
    Card const * top() const;
    friend std::ostream& operator<< (std::ostream& os, const HomeDestination & hd) ;

private:
    std::vector<std::unique_ptr<Card>> storage_;
};


class FreeCell : CardStorage {
public:
	bool canAccept(const Card & card) override;
    bool acceptCard(std::unique_ptr<Card>) override;
    Card const * card() const;

private:
    std::unique_ptr<Card> cell_;
};

std::ostream& operator<< (std::ostream& os, const FreeCell & fc) ;

#endif
