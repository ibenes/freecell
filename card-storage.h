#ifndef CARD_STORAGE_H
#define CARD_STORAGE_H

#include "card.h"

#include <string>
#include <memory>
#include <vector>


class HomeDestination {
public:
	bool canAccept(const Card & card);
    bool acceptCard(std::unique_ptr<Card>);
    Card const * top() const;
    friend std::ostream& operator<< (std::ostream& os, const HomeDestination & hd) ;

private:
    std::vector<std::unique_ptr<Card>> storage_;
};


class FreeCell {
public:
	bool canAccept(const Card & card);
    bool acceptCard(std::unique_ptr<Card>);
    Card const * card() const;

private:
    std::unique_ptr<Card> cell_;
};

std::ostream& operator<< (std::ostream& os, const FreeCell & fc) ;

#endif
