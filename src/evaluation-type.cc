#include "evaluation-type.h"

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
