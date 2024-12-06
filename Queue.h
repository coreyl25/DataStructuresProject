#ifndef QUEUE_H
#define QUEUE_H
#include <vector>
#include <iostream>
using namespace std;

class Queue {
private:
    vector<int> data; 

public:
    
    void enqueue(int value);
    void dequeue();
    int front() const;
    bool isEmpty() const;
    void display() const;
    const std::vector<int>& getData() const;
};

#endif
