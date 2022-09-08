#include "card-storage.h"


class GameState {
public:
    friend std::ostream& operator<< (std::ostream& os, const GameState & state) ;
private:
    std::array<HomeDestination, 4> homes_;
    std::array<FreeCell, 4> free_cells_;
    std::array<WorkStack, 8> stacks_;
};
