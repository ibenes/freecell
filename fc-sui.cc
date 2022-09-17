#include "move.h"
#include "game.h"
#include "search-interface.h"

#include <cassert>
#include <iostream>


int main() {
    std::random_device dev;
    std::default_random_engine rng(1);

    GameState gs{};
    initializeGameState(&gs, rng);
    std::cout << gs;
	std::cout << "\n";

	std::optional<std::pair<CardStorage *, WorkStack * >> irr_move;
	while((irr_move = findIrreversibleMove(&gs, rng)), irr_move.has_value()) {
		forceMove(irr_move->first, irr_move->second);
		std::cout << gs;
		std::cout << "\n";
		break;
	}

	SearchState init_state(gs);
	std::cout << init_state;
	std::cout << "State finality: " << init_state.isFinal() << "\n";

	assert(init_state.execute({LocationClass::Stacks, 2}, {LocationClass::FreeCells, 0}));
	std::cout << init_state;
	std::cout << "State finality: " << init_state.isFinal() << "\n";

}
