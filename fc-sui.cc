#include "card.h"
#include "card-storage.h"
#include "move.h"
#include "game.h"

#include <iostream>


int main() {
    HomeDestination home_heart;
    home_heart.acceptCard({Color::Heart, 1});
    home_heart.acceptCard({Color::Heart, 2});
    home_heart.acceptCard({Color::Heart, 3});

    FreeCell free_cell;
    free_cell.acceptCard({Color::Heart, 4});

    std::cout << "Moving from fc to hd!\n";
    move(&free_cell, &home_heart);
    std::cout << "fc:" << free_cell << "\n";
    std::cout << "hd:" << home_heart << "\n";

    GameState gs{};
    std::cout << gs;
}
