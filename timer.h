#pragma once

#include <chrono>
#include <iostream>


/**
 * Prints time between timer's construction and destruction.
 **/


class Timer {
public:
    typedef std::chrono::high_resolution_clock::time_point TimePoint;

    Timer() : begin_(Now()) {
    }

    static TimePoint Now() {
        return std::chrono::high_resolution_clock::now();
    }

    template<class T = std::chrono::duration<double>>
    static auto ElapsedTime(TimePoint begin, TimePoint end = Now()) {
        return std::chrono::duration_cast<T>(end - begin).count();
    }

    static void PrintElapsedTime(TimePoint begin, TimePoint end = Now()) {
        auto sec = ElapsedTime(begin, end);
        std::cout << "Time: " << std::fixed << std::setprecision(3) << sec << "s" << std::endl;
    }

    void PrintElapsedTime() {
        PrintElapsedTime(begin_);
    }

    ~Timer() {
        PrintElapsedTime();
    }

private:
    const TimePoint begin_;
};

