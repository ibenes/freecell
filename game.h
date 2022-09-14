#include "card-storage.h"
#include "move.h"

#include <random>


struct GameState {
    GameState(void);

    std::array<HomeDestination, 4> homes;
    std::array<FreeCell, 4> free_cells;
    std::array<WorkStack, 8> stacks;

    std::array<CardStorage *, 12> non_homes;
};

std::ostream& operator<< (std::ostream& os, const GameState & state) ;

void initializeGameState(GameState *gs) ;
std::vector<Card> topCards(const GameState &gs) ;
bool cardIsHome(const GameState &gs, Card card) ;
auto findHomeFor(GameState &gs, Card card) -> decltype(gs.homes)::iterator;

std::vector<RawMove> safeHomeMoves(GameState &gs) ;

int moveCardsFromHomes(GameState *gs, int max_nb_cards, int nb_homes_available, std::default_random_engine rng) ;
