#pragma once

#include <chrono>
#include <iostream>
#include <iomanip>


/**
 * Prints time between timer's construction and destruction.
 **/


class Timer {
public:
    typedef std::chrono::high_resolution_clock::time_point TimePoint;

    Timer(bool print_time_at_destructor = true) : begin_(Now()), print_time_at_destructor_(print_time_at_destructor) {
    }

    static TimePoint Now() {
        return std::chrono::high_resolution_clock::now();
    }

    template<class T = std::chrono::duration<double>>
    static auto GetElapsedTime(TimePoint begin, TimePoint end = Now()) {
        return std::chrono::duration_cast<T>(end - begin).count();
    }

    static void PrintElapsedTime(TimePoint begin, TimePoint end = Now()) {
        auto sec = GetElapsedTime(begin, end);
        std::cout << "Time: " << std::fixed << std::setprecision(3) << sec << "s" << std::endl;
    }

    void PrintElapsedTime() {
        PrintElapsedTime(begin_);
    }

    ~Timer() {
        if (print_time_at_destructor_) {
            PrintElapsedTime();
        }
    }

private:
    const TimePoint begin_;
    bool print_time_at_destructor_;
};

