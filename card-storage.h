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
    virtual const Card * topCard() const = 0;
    virtual std::unique_ptr<Card> getCard() = 0;
	virtual ~CardStorage() {};
};


class HomeDestination : public CardStorage {
public:
	bool canAccept(const Card & card) override;
    bool acceptCard(std::unique_ptr<Card>) override;
    const Card * topCard() const override;
    std::unique_ptr<Card> getCard() override;

    friend std::ostream& operator<< (std::ostream& os, const HomeDestination & hd) ;

private:
    std::vector<std::unique_ptr<Card>> storage_;
};


class FreeCell : public CardStorage {
public:
	bool canAccept(const Card & card) override;
    bool acceptCard(std::unique_ptr<Card>) override;
    const Card * topCard() const override;
    std::unique_ptr<Card> getCard() override;

    Card const * card() const;

private:
    std::unique_ptr<Card> cell_;
};

std::ostream& operator<< (std::ostream& os, const FreeCell & fc) ;

#endif
