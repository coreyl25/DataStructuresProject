#include "Queue.h"
using namespace std;

void Queue::enqueue(int value) {
    data.push_back(value); // Add element to the back of the queue
}

void Queue::dequeue() {
    if (!data.empty()) {
        data.erase(data.begin()); // Remove first element
    } else {
        cout << "Queue is empty, nothing to dequeue!\n";
    }
}

int Queue::front() const {
    if (!data.empty()) {
        return data.front(); // Return first element
    } else {
        throw runtime_error("Queue is empty, no front element!");
    }
}

bool Queue::isEmpty() const {
    return data.empty(); 
}

void Queue::display() const {
    if (data.empty()) {
        cout << "Queue is empty!\n";
        return;
    }
    for (int val : data) {
        cout << val << " "; // Print each element
    }
    cout << "\n";
}

const vector<int>& Queue::getData() const {
    return data;
}
