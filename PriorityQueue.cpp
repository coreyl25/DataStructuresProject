#include "PriorityQueue.h"
using namespace std;

void PriorityQueue::enqueue(int value) {
    pq.push(value); 
}

void PriorityQueue::dequeue() {
    if (!pq.empty()) {
        pq.pop(); 
    } else {
        cout << "Priority queue is empty, nothing to dequeue!\n";
    }
}

int PriorityQueue::peek() const {
    if (!pq.empty()) {
        return pq.top(); 
    } else {
        throw runtime_error("Priority queue is empty, no top element!");
    }
}

bool PriorityQueue::isEmpty() const {
    return pq.empty(); 
}

void PriorityQueue::display() const {
    if (pq.empty()) {
        cout << "Priority queue is empty!\n";
        return;
    }

    // Create a copy of the priority queue to display elements non-destructively
    std::priority_queue<int> temp = pq;
    while (!temp.empty()) {
        cout << temp.top() << " ";
        temp.pop();
    }
    std::cout << "\n";
}

std::vector<int> PriorityQueue::getData() const {
    vector<int> result;
    priority_queue<int> temp = pq; // Copy the priority queue

    // Extract elements into a vector
    while (!temp.empty()) {
        result.push_back(temp.top());
        temp.pop();
    }

    return result;
}

