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

	std::optional<std::pair<CardStorage *, WorkStack * >> irr_move;
	while((irr_move = findIrreversibleMove(&gs, rng)), irr_move.has_value()) {
		forceMove(irr_move->first, irr_move->second);
		std::cout << gs;
		std::cout << "\n";
	}

	std::vector<RawMove> safe_moves;
	while ((safe_moves = safeHomeMoves(gs)), safe_moves.size() > 0) {
		auto from = safe_moves[0].first;
		auto to = safe_moves[0].second;
		move(const_cast<CardStorage *>(from), const_cast<CardStorage *>(to));
	}
	std::cout << gs;
}
