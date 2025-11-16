#pragma once
#include <chrono>

class Timer {
    using clock = std::chrono::high_resolution_clock;

public:
    Timer() : start(clock::now()) {}

    long long elapsed_ms() {
        auto end = clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }

    void reset() {
        start = clock::now();
    }

private:
    clock::time_point start;

};
