#pragma once
#include <vector>
#include <string>
#include <mutex>

class MyStruct {
public:
    MyStruct() : values(m, 0) {
    }

    int read(int index);

    void write(int index, int newValue);

    std::string toString();

private:
    static const int m = 3;
    std::vector<int> values;
    std::mutex mtx[m];
};
