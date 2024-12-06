#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include <queue>
#include <iostream>
#include <vector>
using namespace std;

class PriorityQueue {
private:
    //  Max-heap priority queue
    priority_queue<int> pq;

public:
    void enqueue(int value);
    void dequeue();
    int peek() const;
    bool isEmpty() const;
    void display() const;
    vector<int> getData() const;
};

#endif
