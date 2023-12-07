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
    static long long ElapsedTime(Clock::time_point begin, Clock::time_point end = Now()) {
        return std::chrono::duration_cast<T>(end - begin).count();
    }

    void PrintPrettyElapsedTime() {
        auto end = Now();

        long long time;
        if (AssignAndCheck<std::chrono::minutes>(end, time)) {
            PrintTime("min", time);
        } else if (AssignAndCheck<std::chrono::seconds>(end, time)) {
            PrintTime("sec", time);
        } else if (AssignAndCheck<std::chrono::milliseconds>(end, time)) {
            PrintTime("ms", time);
        } else {
            PrintTime("mcs", ElapsedTime<std::chrono::microseconds>(begin_, end));
        }
    }

    ~Timer() {
        PrintPrettyElapsedTime();
    }

private:
    template<class T>
    bool AssignAndCheck(const Clock::time_point end, long long &time) noexcept {

        time = ElapsedTime<T>(begin_, end);
        return time > cThreshold;
    }

    void PrintTime(const auto unit, const long long duration) {
        std::cout << "Time: " << duration << " " << unit << "." << std::endl;
    };

private:
    const Clock::time_point begin_;
    const long long cThreshold = 20;
};

