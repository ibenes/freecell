#ifndef GAME_H
#define GAME_H

#include "card-storage.h"
#include "move.h"

#include <random>

inline constexpr int nb_freecells = 4;
inline constexpr int nb_homes = 4;
inline constexpr int nb_stacks = 8;


struct GameState {
    GameState(void);
    GameState(const GameState &other);
    GameState& operator=(GameState &&other);

    std::array<HomeDestination, nb_homes> homes;
    std::array<FreeCell, nb_freecells> free_cells;
    std::array<WorkStack, nb_stacks> stacks;

    std::array<CardStorage *, nb_stacks+nb_freecells> non_homes;
    std::array<CardStorage *, nb_stacks+nb_freecells+nb_homes> all_storage;

    void recalculatePointerArrays_(void) ;
};

enum class LocationClass {FreeCells, Homes, Stacks};
struct Location {
	LocationClass cl;
	long id;
};

bool operator== (const Location &lhs, const Location &rhs) ;
bool operator!= (const Location &lhs, const Location &rhs) ;

std::ostream& operator<< (std::ostream& os, const Location & state) ;

std::ostream& operator<< (std::ostream& os, const GameState & state) ;

void initializeGameState(GameState *gs, std::default_random_engine &rng) ;
std::optional<std::pair<CardStorage *, WorkStack *>> findIrreversibleMove(GameState *gs, std::default_random_engine &rng) ;

void forceMove(CardStorage *from, WorkStack *to) ;

std::vector<Card> topCards(const GameState &gs) ;
bool cardIsHome(const GameState &gs, Card card) ;
bool cardCouldGoHome(const GameState &gs, Card card) ;
auto findHomeFor(const GameState &gs, Card card) -> decltype(gs.homes)::const_iterator;

const CardStorage * ptrFromLoc(const GameState &gs, Location const& loc) ;
Location locFromPtr(const GameState &gs, const CardStorage *ptr) ;

std::vector<RawMove> safeHomeMoves(const GameState &gs) ;

#endif
