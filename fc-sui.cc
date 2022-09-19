#include "move.h"
#include "game.h"
#include "search-interface.h"
#include "search-strategies.h"

#include <cassert>
#include <chrono>
#include <iostream>
#include <memory>


struct StrategyEvaluation {
    unsigned long nb_solved;
    unsigned long nb_failed;
    unsigned long total_solution_length;
    std::chrono::microseconds time_taken;
};

std::ostream& operator<< (std::ostream& os, const StrategyEvaluation &report) {
    os << "Solved " << report.nb_solved << " / " << report.nb_solved + report.nb_failed <<
        " [ " << 100.0*report.nb_solved / (report.nb_solved + report.nb_failed) << " % ]. " <<
        "Avg solution length " << 1.0 * report.total_solution_length / report.nb_solved << " steps, "
        "Avg time taken: " << (report.time_taken / report.nb_solved).count() << " us \n";

    return os;
}


void eval_strategy(
        std::unique_ptr<SearchStrategyItf> &search_strategy,
        const SearchState &init_state,
        StrategyEvaluation *report
    ) {

    auto t0 = std::chrono::steady_clock::now();
	auto solution = search_strategy->solve(init_state);
    auto t1 = std::chrono::steady_clock::now();


	SearchState in_progress(init_state);
	for (const auto & action : solution)
		in_progress = action.execute(in_progress);

    if (in_progress.isFinal()) {
        report->nb_solved++;
        report->total_solution_length += solution.size();
        report->time_taken += std::chrono::duration_cast<decltype(report->time_taken)>(t1 - t0);
    } else {
        report->nb_failed++;
    }
}


int main() {
    std::random_device dev;
    std::default_random_engine rng(1);

	std::unique_ptr<SearchStrategyItf> search_strategy = std::make_unique<DummySearch>();
    StrategyEvaluation evaluation_record{};

    for (int i = 0; i < 42; ++i) {
        GameState gs{};
        initializeGameState(&gs, rng);

        std::optional<std::pair<CardStorage *, WorkStack * >> irr_move;
        while((irr_move = findIrreversibleMove(&gs, rng)), irr_move.has_value()) {
            forceMove(irr_move->first, irr_move->second);
            break;
        }
        SearchState init_state(gs);

        eval_strategy(search_strategy, init_state, &evaluation_record);
    }

    std::cout << evaluation_record;
}
