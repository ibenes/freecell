#include "move.h"
#include "game.h"
#include "search-interface.h"
#include "search-strategies.h"

#include "evaluation-type.h"
#include "argparse.h"
#include "mem_watch.h"

#include <cassert>
#include <chrono>
#include <iostream>
#include <memory>

#include <thread>
#include <atomic>


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

std::unique_ptr<InitialStateProducerItf> getProducer(const argparse::ArgumentParser &parser) {
    auto difficulty = parser.get<int>("--easy-mode");
    auto seed = parser.get<int>("seed");

    if (difficulty < 0) {
        return std::make_unique<RandomProducer>(seed);
    } else {
        return std::make_unique<EasyProducer>(seed, difficulty);
    }
}

std::unique_ptr<AStarHeuristicItf> getHeuristic(const argparse::ArgumentParser &parser) {
    auto heuristic_name = parser.get<std::string>("--heuristic");

    if (heuristic_name == "nb_not_home") {
        return std::make_unique<OufOfHome_Pseudo>();
    } else if (heuristic_name == "student") {
	    return std::make_unique<StudentHeuristic>();
    } else {
        std::cerr << "Unknown heuristic name '" << heuristic_name << "'\n";
        std::cerr << "Supported are: nb_not_home, student\n";
        std::exit(2);
    }
}

std::unique_ptr<SearchStrategyItf> getSolver(const argparse::ArgumentParser &parser) {
    auto solver_name = parser.get<std::string>("--solver");

    if (solver_name == "dummy") {
        return std::make_unique<DummySearch>(500, 5);
    } else if (solver_name == "bfs") {
	    return std::make_unique<BreadthFirstSearch>(parser.get<size_t>("--mem-limit"));
    } else if (solver_name == "dfs") {
        return std::make_unique<DepthFirstSearch>(parser.get<int>("--dls-limit"), parser.get<size_t>("--mem-limit"));
    } else if (solver_name == "a_star") {
        return std::make_unique<AStarSearch>(getHeuristic(parser), parser.get<size_t>("--mem-limit"));
    } else {
        std::cerr << "Unknown solver name '" << solver_name << "'\n";
        std::cerr << "Supported are: dummy, bfs, a_star, dfs\n";
        std::exit(2);
    }
}


int main(int argc, const char *argv[]) {
    argparse::ArgumentParser parser("FreeCell@SUI");
    parser.add_argument("nb_games").scan<'d', int>();
    parser.add_argument("seed").scan<'d', int>();

    parser.add_argument("--easy-mode").default_value(-1).scan<'d', int>();
    parser.add_argument("--solver").default_value(std::string("dummy"));
    parser.add_argument("--heuristic").default_value(std::string("nb_not_home"));
    parser.add_argument("--dls-limit").default_value(1'000'000).scan<'d', int>();
    parser.add_argument("--mem-limit").default_value(std::size_t{2'147'483'648}).scan<'u', size_t>();

    try {
        parser.parse_args(argc, argv);
    } catch (const std::runtime_error &err) {
        std::cerr << err.what() << "\n";
        std::cerr << parser;
        std::exit(2);
    }

    StrategyEvaluation evaluation_record;

    MemWatcher mem_watcher(
        parser.get<size_t>("--mem-limit"),
        std::chrono::milliseconds(1000),
        evaluation_record
    );
    std::thread thread_mem_watch(&MemWatcher::run, &mem_watcher);

    std::unique_ptr<InitialStateProducerItf> producer = getProducer(parser);
    std::unique_ptr<SearchStrategyItf> search_strategy = getSolver(parser);

    auto nb_games = parser.get<int>("nb_games");
    for (int i = 0; i < nb_games; ++i) {
        GameState gs = producer->produce();
        SearchState init_state(gs);
        eval_strategy(search_strategy, init_state, &evaluation_record);
    }

    mem_watcher.kill();
    thread_mem_watch.join();

    std::cout << evaluation_record;
}
