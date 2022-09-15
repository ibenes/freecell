#include "move.h"
#include "game.h"

#include <iostream>


int main() {
    std::random_device dev;
    std::default_random_engine rng(dev());

    GameState gs{};
    initializeGameState(&gs, rng);
    std::cout << gs;
	std::cout << "\n";

	irreversibleMove(&gs, rng);
    std::cout << gs;
	std::cout << "\n";

	std::vector<RawMove> safe_moves;
	while ((safe_moves = safeHomeMoves(gs)), safe_moves.size() > 0) {
		auto from = safe_moves[0].first;
		auto to = safe_moves[0].second;
		move(from, to);
	}
	std::cout << gs;
}
