#include "MyStruct.h"
#include "Generator.h"
#include "Timer.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

using namespace std;
using namespace chrono;

void processFile(MyStruct& data, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string operation;
    while (file >> operation) {
        if (operation == "read") {
            int index;
            file >> index;
            data.read(index);
        }
        else if (operation == "write") {
            int index, value;
            file >> index >> value;
            data.write(index, value);
        }
        else if (operation == "string") {
            data.toString();
        }
    }
    file.close();
}

int main() {
    Generator gen;

    try {
        gen.generateAllFiles(1000000);
    }
    catch (const exception& e) {
        cerr << "Generator error: " << e.what() << endl;
        return 0;
    }

    MyStruct data;
    Timer timer;

    cout << "\n--- 1 thread ---\n";

    timer.reset();
    processFile(data, "test_1thread_matching.txt");
    cout << "Matching: " << timer.elapsed_ms() << " ms\n";

    timer.reset();
    processFile(data, "test_1thread_equal.txt");
    cout << "Equal: " << timer.elapsed_ms() << " ms\n";

    timer.reset();
    processFile(data, "test_1thread_custom.txt");
    cout << "Custom: " << timer.elapsed_ms() << " ms\n";

    cout << "\n--- 2 threads ---\n";

    // matching
    timer.reset();
    thread t1_m(processFile, ref(data), "test_2threads_t1_matching.txt");
    thread t2_m(processFile, ref(data), "test_2threads_t2_matching.txt");
    t1_m.join();
    t2_m.join();
    cout << "Matching: " << timer.elapsed_ms() << " ms\n";

    // equal
    timer.reset();
    thread t1_e(processFile, ref(data), "test_2threads_t1_equal.txt");
    thread t2_e(processFile, ref(data), "test_2threads_t2_equal.txt");
    t1_e.join();
    t2_e.join();
    cout << "Equal: " << timer.elapsed_ms() << " ms\n";

    // custom
    timer.reset();
    thread t1_mis(processFile, ref(data), "test_2threads_t1_custom.txt");
    thread t2_mis(processFile, ref(data), "test_2threads_t2_custom.txt");
    t1_mis.join();
    t2_mis.join();
    cout << "Custom: " << timer.elapsed_ms() << " ms\n";

    cout << "\n--- 3 threads ---\n";

    // matching
    timer.reset();
    thread t1_3m(processFile, ref(data), "test_3threads_t1_matching.txt");
    thread t2_3m(processFile, ref(data), "test_3threads_t2_matching.txt");
    thread t3_3m(processFile, ref(data), "test_3threads_t3_matching.txt");
    t1_3m.join();
    t2_3m.join();
    t3_3m.join();
    cout << "Matching: " << timer.elapsed_ms() << " ms\n";

    // equal
    timer.reset();
    thread t1_3e(processFile, ref(data), "test_3threads_t1_equal.txt");
    thread t2_3e(processFile, ref(data), "test_3threads_t2_equal.txt");
    thread t3_3e(processFile, ref(data), "test_3threads_t3_equal.txt");
    t1_3e.join();
    t2_3e.join();
    t3_3e.join();
    cout << "Equal: " << timer.elapsed_ms() << " ms\n";

    // custom
    timer.reset();
    thread t1_3mis(processFile, ref(data), "test_3threads_t1_custom.txt");
    thread t2_3mis(processFile, ref(data), "test_3threads_t2_custom.txt");
    thread t3_3mis(processFile, ref(data), "test_3threads_t3_custom.txt");
    t1_3mis.join();
    t2_3mis.join();
    t3_3mis.join();
    cout << "Custom: " << timer.elapsed_ms() << " ms\n";

    return 0;
}