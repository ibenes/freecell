#include "game.h"

std::ostream& operator<< (std::ostream& os, const GameState & state) {
    os << "Homes: " <<
        state.homes_[0] << " " <<
        state.homes_[1] << " " <<
        state.homes_[2] << " " <<
        state.homes_[3] << "\n";

    os << "FreeCells: " <<
        state.free_cells_[0] << " " <<
        state.free_cells_[1] << " " <<
        state.free_cells_[2] << " " <<
        state.free_cells_[3] << "\n";

    for (auto stack : state.stacks_) {
        os << stack << "\n";
    }

    return os;
}

