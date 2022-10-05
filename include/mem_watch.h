#ifndef MEM_WATCH_H
#define MEM_WATCH_H

#include "evaluation-type.h"

#include <chrono>
#include <atomic>

class MemWatcher {
public:
    MemWatcher(size_t limit, std::chrono::milliseconds period, const StrategyEvaluation &report) :
        mem_limit_(limit), period_(period), stop_(false), report_(report) {}

    void run() const;
    void kill();

private:
    size_t mem_limit_;
    std::chrono::milliseconds period_;
    std::atomic<bool> stop_;
    const StrategyEvaluation &report_;
};

#endif
