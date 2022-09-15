#include "move.h"
#include "game.h"

#include <iostream>


int main() {
    GameState gs{};
    initializeGameState(&gs);
    std::cout << gs;

	std::vector<RawMove> safe_moves;
	while ((safe_moves = safeHomeMoves(gs)), safe_moves.size() > 0) {
		auto from = safe_moves[0].first;
		auto to = safe_moves[0].second;
		move(from, to);
		std::cout << gs;
	}
}
