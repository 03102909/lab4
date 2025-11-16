#include "MyStruct.h"
using namespace std;

int MyStruct::read(int index) {
    scoped_lock lock(mtx[index]);
    return values[index];
}

void MyStruct::write(int index, int newValue) {
    scoped_lock lock(mtx[index]);
    values[index] = newValue;
}

string MyStruct::toString() {
    scoped_lock lock(mtx[0], mtx[1], mtx[2]);
    return to_string(values[0]) + " " + to_string(values[1]) + " " + to_string(values[2]);
}