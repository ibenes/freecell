#include "card.h"
#include "card-storage.h"
#include "move.h"
#include "game.h"

#include <iostream>


int main() {
    GameState gs{};
    initializeGameState(&gs);
    std::cout << gs;
}
