#include "card.h"
#include "card-storage.h"

#include <iostream>


bool legalMove(CardStorage *from, CardStorage *to) {
    auto card_ref = from->topCard();
    if (card_ref == nullptr)
        return false;

    return to->canAccept(*card_ref);
}

void move(CardStorage *from, CardStorage *to) {
    if (!legalMove(from, to))
        return;

    to->acceptCard(std::move(from->getCard()));
}


int main() {
    HomeDestination home_heart;
    home_heart.acceptCard(std::make_unique<Card>(Color::Heart, 3));
    std::cout << home_heart << "\n";

    home_heart.acceptCard(std::make_unique<Card>(Color::Heart, 1));
    std::cout << home_heart << "\n";
    home_heart.acceptCard(std::make_unique<Card>(Color::Heart, 2));
    std::cout << home_heart << "\n";

    home_heart.acceptCard(std::make_unique<Card>(Color::Spade, 3));
    std::cout << home_heart << "\n";
    home_heart.acceptCard(std::make_unique<Card>(Color::Heart, 4));
    std::cout << home_heart << "\n";

    home_heart.acceptCard(std::make_unique<Card>(Color::Heart, 3));
    std::cout << home_heart << "\n";

    FreeCell free_cell;
    std::cout << "fc:" << free_cell << "\n";

    free_cell.acceptCard(std::make_unique<Card>(Color::Heart, 4));
    std::cout << "fc:" << free_cell << "\n";

    free_cell.acceptCard(std::make_unique<Card>(Color::Spade, 4));
    std::cout << "fc:" << free_cell << "\n";

    std::cout << "Moving from fc to hd!\n";
    move(&free_cell, &home_heart);
    std::cout << "fc:" << free_cell << "\n";
    std::cout << "hd:" << home_heart << "\n";

    std::cout << "Attempting illegal move\n";
    move(&free_cell, &home_heart);
    std::cout << "fc:" << free_cell << "\n";
    std::cout << "hd:" << home_heart << "\n";
}
