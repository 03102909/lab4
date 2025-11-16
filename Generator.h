#pragma once

#include <string>
#include <vector>
#include <random>

class Generator {
private:
    static const int m = 3;
    std::vector<double> read_freq;
    std::vector<double> write_freq;
    double string_freq;

    std::mt19937 rng;

    struct Operation {
        std::string type;
        int field;
        double freq;
    };

public:
    Generator();

    void generateMatchingFile(const std::string& filename, int operations_count = 10000);

    void generateEqualFile(const std::string& filename, int operations_count = 10000);

    void generateCustomFile(const std::string& filename, int operations_count = 10000);

    void generateAllFiles(int operations_per_file = 50000);
};