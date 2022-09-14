#include "card-storage.h"

#include <random>


struct GameState {
    std::array<HomeDestination, 4> homes;
    std::array<FreeCell, 4> free_cells;
    std::array<WorkStack, 8> stacks;

    std::vector<Card> topCards(void) const;
};

std::ostream& operator<< (std::ostream& os, const GameState & state) ;

void initializeGameState(GameState *gs) ;
std::vector<Card> topCards(const GameState &gs) ;
int moveCardsFromHomes(GameState *gs, int max_nb_cards, int nb_homes_available, std::default_random_engine rng) ;
