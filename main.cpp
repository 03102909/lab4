#include "MyStruct.h"
#include "Generator.h"
#include "Timer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
#include <vector>

using namespace std;
using namespace chrono;

void processCommands(MyStruct& data, istringstream& stream) {
    string operation;

    while (stream >> operation) {
        if (operation == "read") {
            int index;
            stream >> index;
            data.read(index);
        }
        else if (operation == "write") {
            int index, value;
            stream >> index >> value;
            data.write(index, value);
        }
        else if (operation == "string") {
            data.toString();
        }
    }
}

template<typename Func>
double measureExecution(Func&& func) {
    Timer timer;
    func();
    return timer.elapsed_ms();
}

void runThreads(MyStruct& data, vector<istringstream>& streams) {
    vector<thread> threads;
    threads.reserve(streams.size());

    for (auto& stream : streams) {
        threads.emplace_back(processCommands, ref(data), ref(stream));
    }

    for (auto& t : threads) {
        t.join();
    }
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
    vector<string> patterns = {"matching", "equal", "custom"};

    cout << "\n--- 1 thread ---\n";
    for (const auto& pattern : patterns) {
        ifstream file("test_1thread_" + pattern + ".txt");
        string line, content;
        while (getline(file, line)) {
            content += line + "\n";
        }
        file.close();

        istringstream stream(content);
        double time = measureExecution([&]() {
            processCommands(data, stream);
        });
        cout << pattern << ": " << time << " ms\n";
    }

    cout << "\n--- 2 threads ---\n";
    for (const auto& pattern : patterns) {
        ifstream file("test_2threads_" + pattern + ".txt");
        string line, content;
        while (getline(file, line)) {
            content += line + "\n";
        }
        file.close();

        vector<istringstream> streams;
        streams.emplace_back(content);
        streams.emplace_back(content);

        double time = measureExecution([&]() {
            runThreads(data, streams);
        });
        cout << pattern << ": " << time << " ms\n";
    }

    cout << "\n--- 3 threads ---\n";
    for (const auto& pattern : patterns) {
        ifstream file("test_3threads_" + pattern + ".txt");
        string line, content;
        while (getline(file, line)) {
            content += line + "\n";
        }
        file.close();

        vector<istringstream> streams;
        streams.emplace_back(content);
        streams.emplace_back(content);
        streams.emplace_back(content);

        double time = measureExecution([&]() {
            runThreads(data, streams);
        });
        cout << pattern << ": " << time << " ms\n";
    }

    return 0;
}
