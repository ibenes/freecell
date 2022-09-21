#include "move.h"
#include "game.h"
#include "search-interface.h"
#include "search-strategies.h"

#include "argparse.h"

#include <cassert>
#include <chrono>
#include <iostream>
#include <memory>


struct StrategyEvaluation {
    unsigned long nb_solved;
    unsigned long nb_failed;
    unsigned long total_solution_length;
    unsigned long long nb_states_expanded;
    std::chrono::microseconds time_taken;
};

std::ostream& operator<< (std::ostream& os, const StrategyEvaluation &report) {
    if (report.nb_solved > 0) {
        os << "Solved " << report.nb_solved << " / " << report.nb_solved + report.nb_failed <<
            " [ " << 100.0*report.nb_solved / (report.nb_solved + report.nb_failed) << " % ]. " <<
            "Avg solution length " << 1.0 * report.total_solution_length / report.nb_solved << " steps, "
            "Avg time taken: " << (report.time_taken / report.nb_solved).count() << " us " <<
            "Total #states expaned: " << report.nb_states_expanded << 
            "\n";
    } else {
        os << "Solved " << report.nb_solved << " / " << report.nb_solved + report.nb_failed <<
            " [ 0 % ]. " <<
            "Avg solution length NA steps, " <<
            "Avg time taken: NA us " <<
            "Total #states expaned: " << report.nb_states_expanded << 
            "\n";
    }

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
    report->nb_states_expanded = SearchState::nbExpanded();
}


int main(int argc, const char *argv[]) {
    argparse::ArgumentParser parser("FreeCell@SUI");
    parser.add_argument("nb_games").scan<'d', int>();
    parser.add_argument("seed").scan<'d', int>();

    try {
        parser.parse_args(argc, argv);
    } catch (const std::runtime_error &err) {
        std::cerr << err.what() << "\n";
        std::cerr << parser;
        std::exit(2);
    }

    std::random_device dev;
    std::default_random_engine rng(parser.get<int>("seed"));

	std::unique_ptr<SearchStrategyItf> search_strategy = std::make_unique<DummySearch>(500, 5, rng);
    StrategyEvaluation evaluation_record{};

    auto nb_games = parser.get<int>("nb_games");
    for (int i = 0; i < nb_games; ++i) {
        GameState gs{};
        initializeFullRandom(&gs, rng);
        SearchState init_state(gs);

        eval_strategy(search_strategy, init_state, &evaluation_record);
    }

    std::cout << evaluation_record;
}
