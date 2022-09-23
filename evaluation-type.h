#ifndef EVALUATION_TYPE_H
#define EVALUATION_TYPE_H

#include <chrono>
#include <iostream>

struct StrategyEvaluation {
	StrategyEvaluation() : nb_solved(0), nb_failed(0), total_solution_length(0), nb_states_expanded(0), time_taken(0) {}
    unsigned long nb_solved;
    unsigned long nb_failed;
    unsigned long total_solution_length;
    unsigned long long nb_states_expanded;
    std::chrono::microseconds time_taken;
};

std::ostream& operator<< (std::ostream& os, const StrategyEvaluation &report) ;

#endif
