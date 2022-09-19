#include "move.h"
#include "game.h"
#include "search-interface.h"
#include "search-strategies.h"

#include <cassert>
#include <iostream>
#include <memory>


int main() {
    std::random_device dev;
    std::default_random_engine rng(1);

	std::unique_ptr<SearchStrategyItf> search_strategy = std::make_unique<DummySearch>();

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

	auto solution = search_strategy->solve(init_state);

	SearchState in_progress(init_state);
	for (const auto & action : solution) {
		std::cout << "Execution action " << action << "\n";
		in_progress = action.execute(in_progress);
		std::cout << in_progress;
		std::cout << "State finality: " << in_progress.isFinal() << "\n";
	}

	std::cout << "\nFor comparison, the initial state was:\n";
	std::cout << init_state;
	std::cout << "State finality: " << init_state.isFinal() << "\n";
}
