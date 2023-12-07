#pragma once

#include <algorithm>
#include <chrono>
#include <limits>
#include <numeric>
#include <random>
#include <vector>


struct RandomGenerator {
    explicit RandomGenerator(size_t seed = std::chrono::system_clock::now().time_since_epoch().count()) : gen_(seed) {
    }

    template<class T = int>
    std::vector<T> GenIntegralVector(size_t n, T from = std::numeric_limits<T>::min(),
                                     T to = std::numeric_limits<T>::max()) {
        std::uniform_int_distribution<T> dist(from, to);
        std::vector<T> result(n);
        for (auto &cur: result) {
            cur = dist(gen_);
        }
        return result;
    }

    template<class T = int>
    std::vector<std::vector<T>> GenIntegralMatrix(size_t n, size_t m, T from = std::numeric_limits<T>::min(),
                                                  T to = std::numeric_limits<T>::max()) {
        std::uniform_int_distribution<T> dist(from, to);
        std::vector<std::vector<T>> result(n, std::vector<T>(m));
        for (auto &line: result) {
            for (auto &cur: line) {
                cur = dist(gen_);
            }
        }
        return result;
    }

    std::vector<double> GenRealVector(size_t n, double from = 0, double to = 1) {
        std::uniform_real_distribution<double> dist(from, to);
        std::vector<double> result(n);
        for (auto &cur: result) {
            cur = dist(gen_);
        }
        return result;
    }

    std::vector<std::vector<double>> GenRealMatrix(size_t n, size_t m, double from = 0, double to = 1) {
        std::uniform_real_distribution<double> dist(from, to);
        std::vector<std::vector<double>> result(n, std::vector<double>(m));
        for (auto &line: result) {
            for (auto &cur: line) {
                cur = dist(gen_);
            }
        }
        return result;
    }

    template<class T = int>
    std::vector<T> GenPermutation(size_t n) {
        std::vector<T> result(n);
        std::iota(result.begin(), result.end(), 0);
        std::shuffle(result.begin(), result.end(), gen_);
        return result;
    }

    template<class T = int>
    void Shuffle(std::vector<T> &vct) {
        std::shuffle(vct.begin(), vct.end(), gen_);
    }

    template<class T = int>
    std::vector<T> GetShuffled(const std::vector<T> &vct) {
        std::vector<T> result = vct;
        std::shuffle(result.begin(), result.end(), gen_);
        return result;
    }

    std::string GenString(size_t n, char from = 'a', char to = 'z') {
        std::uniform_int_distribution<int> dist(from, to);
        std::string result(n, from);
        for (char &x: result) {
            x = static_cast<char>(dist(gen_));
        }
        return result;
    }

    template<class T = int>
    T GenInt(T from = std::numeric_limits<T>::min(), T to = std::numeric_limits<T>::max()) {
        std::uniform_int_distribution<T> dist(from, to);
        return dist(gen_);
    }

private:
    std::mt19937_64 gen_;
};
