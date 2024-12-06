#ifndef HEAP_H
#define HEAP_H
#include <vector>
#include <iostream>
using namespace std;

class Heap {
private:
    vector<int> data;

    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    void insert(int value);
    void remove(int value);
    bool search(int value) const;
    void display() const;
    const vector<int>& getData() const;
};

#endif
