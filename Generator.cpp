#include "Generator.h"
#include <fstream>
#include <stdexcept>

using namespace std;

Generator::Generator() {
    rng.seed(random_device{}());

    read_freq = {1.0, 1.0, 1.0};
    write_freq = {40.0, 5.0, 5.0};
    string_freq = 47.0;
}

void Generator::generateMatchingFile(const string& filename, int operations_count) {
    ofstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Cannot open file: " + filename);
    }

    vector<Operation> ops;

    for (int i = 0; i < m; i++) {
        ops.push_back({"read", i, read_freq[i]});
        ops.push_back({"write", i, write_freq[i]});
    }
    ops.push_back({"string", -1, string_freq});

    vector<double> weights;
    for (const auto& op : ops) {
        weights.push_back(op.freq);
    }

    discrete_distribution<> dist(weights.begin(), weights.end());

    for (int i = 0; i < operations_count; i++) {
        int idx = dist(rng);
        const auto& op = ops[idx];

        if (op.type == "read") {
            file << "read " << op.field << "\n";
        } else if (op.type == "write") {
            file << "write " << op.field << " 1\n";
        } else {
            file << "string\n";
        }
    }

    file.close();
}

void Generator::generateEqualFile(const string& filename, int operations_count) {
    ofstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Cannot open file: " + filename);
    }

    int total_ops = m * 2 + 1;
    uniform_int_distribution<> dist(0, total_ops - 1);

    for (int i = 0; i < operations_count; i++) {
        int op_type = dist(rng);

        if (op_type < m) {
            file << "read " << op_type << "\n";
        } else if (op_type < m * 2) {
            file << "write " << (op_type - m) << " 1\n";
        } else {
            file << "string\n";
        }
    }

    file.close();
}

void Generator::generateCustomFile(const string& filename, int operations_count) {
    ofstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Cannot open file: " + filename);
    }

    vector<double> custom_weights = { 40.0, 1.0, 30.0, 1.0, 20.0, 1.0, 7.0 };

    discrete_distribution<> dist(custom_weights.begin(), custom_weights.end());

    for (int i = 0; i < operations_count; i++) {
        int idx = dist(rng);

        switch(idx) {
            case 0: file << "read 0\n"; break;
            case 1: file << "write 0 1\n"; break;
            case 2: file << "read 1\n"; break;
            case 3: file << "write 1 1\n"; break;
            case 4: file << "read 2\n"; break;
            case 5: file << "write 2 1\n"; break;
            case 6: file << "string\n"; break;
        }
    }

    file.close();
}

void Generator::generateAllFiles(int operations_per_file) {
    // 1 thread
    generateMatchingFile("test_1thread_matching.txt", operations_per_file);
    generateEqualFile("test_1thread_equal.txt", operations_per_file);
    generateCustomFile("test_1thread_custom.txt", operations_per_file);

    // 2 threads
    generateMatchingFile("test_2threads_t1_matching.txt", operations_per_file);
    generateMatchingFile("test_2threads_t2_matching.txt", operations_per_file);

    generateEqualFile("test_2threads_t1_equal.txt", operations_per_file);
    generateEqualFile("test_2threads_t2_equal.txt", operations_per_file);

    generateCustomFile("test_2threads_t1_custom.txt", operations_per_file);
    generateCustomFile("test_2threads_t2_custom.txt", operations_per_file);

    // 3 threads
    generateMatchingFile("test_3threads_t1_matching.txt", operations_per_file);
    generateMatchingFile("test_3threads_t2_matching.txt", operations_per_file);
    generateMatchingFile("test_3threads_t3_matching.txt", operations_per_file);

    generateEqualFile("test_3threads_t1_equal.txt", operations_per_file);
    generateEqualFile("test_3threads_t2_equal.txt", operations_per_file);
    generateEqualFile("test_3threads_t3_equal.txt", operations_per_file);

    generateCustomFile("test_3threads_t1_custom.txt", operations_per_file);
    generateCustomFile("test_3threads_t2_custom.txt", operations_per_file);
    generateCustomFile("test_3threads_t3_custom.txt", operations_per_file);
}