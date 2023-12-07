#pragma once

#include <chrono>
#include <iostream>


/**
 * Prints time between timer's construction and destruction.
 **/


using namespace std::chrono_literals;

struct Timer {
    typedef std::chrono::high_resolution_clock Clock;

    Timer() : begin_(Now()) {
    }

    static Clock::time_point Now() {
        return Clock::now();
    }

    template<class T = std::chrono::milliseconds>
    static auto ElapsedTime(Clock::time_point begin, Clock::time_point end = Now()) {
        return std::chrono::duration_cast<T>(end - begin).count();
    }

    void PrintElapsedTime() {
        auto sec = ElapsedTime<std::chrono::duration<double>>(begin_);
        std::cout << "Time: " << std::fixed << std::setprecision(3) << sec << "s" << std::endl;
    }

    ~Timer() {
        PrintElapsedTime();
    }

private:
    const Clock::time_point begin_;
};

