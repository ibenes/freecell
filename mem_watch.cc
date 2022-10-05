#include "mem_watch.h"

#include "memusage.h"

#include <iostream>
#include <thread>
#include <cmath>

// taken from https://en.cppreference.com/w/cpp/filesystem/file_size
struct HumanReadable {
    std::uintmax_t size{};
  private: friend
    std::ostream& operator<<(std::ostream& os, HumanReadable hr) {
        int i{};
        double mantissa = hr.size;
        for (; mantissa >= 1024.; mantissa /= 1024., ++i) { }
        mantissa = std::ceil(mantissa * 10.) / 10.;
        os << mantissa << "BKMGTPE"[i];
        return i == 0 ? os : os << "B (" << hr.size << ')';
    }
};

void MemWatcher::run() const {
    while (!stop_) {
        auto mem = getCurrentRSS();
        
        if (mem > mem_limit_) {
            std::cout << report_;
            std::cerr << "MEM: Already taken " << HumanReadable{mem} <<
                " which is " << HumanReadable{mem - mem_limit_} <<
                " over the limit of " << HumanReadable{mem_limit_} <<
                ". Aborting.\n";
            std::abort();
        }

        std::this_thread::sleep_for(period_);
    }
}

void MemWatcher::kill() {
    stop_ = true;
}
