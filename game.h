#include "card-storage.h"
#include "move.h"

#include <random>

inline constexpr int nb_freecells = 4;
inline constexpr int nb_homes = 4;
inline constexpr int nb_stacks = 8;


struct GameState {
    GameState(void);

    std::array<HomeDestination, nb_homes> homes;
    std::array<FreeCell, nb_freecells> free_cells;
    std::array<WorkStack, nb_stacks> stacks;

    std::array<CardStorage *, nb_stacks+nb_freecells> non_homes;
};

std::ostream& operator<< (std::ostream& os, const GameState & state) ;

void initializeGameState(GameState *gs) ;
std::vector<Card> topCards(const GameState &gs) ;
bool cardIsHome(const GameState &gs, Card card) ;
bool cardCouldGoHome(const GameState &gs, Card card) ;
auto findHomeFor(GameState &gs, Card card) -> decltype(gs.homes)::iterator;

std::vector<RawMove> safeHomeMoves(GameState &gs) ;

int moveCardsFromHomes(GameState *gs, int max_nb_cards, int nb_homes_available, std::default_random_engine rng) ;
