#include "Heap.h"
using namespace std;

void Heap::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (data[index] > data[parent]) {
            swap(data[index], data[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

void Heap::heapifyDown(int index) {
    int size = data.size();
    while (index < size) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if (left < size && data[left] > data[largest]) {
            largest = left;
        }
        if (right < size && data[right] > data[largest]) {
            largest = right;
        }
        if (largest != index) {
            swap(data[index], data[largest]);
            index = largest;
        } else {
            break;
        }
    }
}

void Heap::insert(int value) {
    data.push_back(value);
    heapifyUp(data.size() - 1);
}

void Heap::remove(int value) {
    auto it = find(data.begin(), data.end(), value);
    if (it != data.end()) {
        int index = it - data.begin();
        data[index] = data.back();
        data.pop_back();
        heapifyDown(index);
    }
}

bool Heap::search(int value) const {
    return find(data.begin(), data.end(), value) != data.end();
}

void Heap::display() const {
    for (int val : data) {
        std::cout << val << " ";
    }
    cout << std::endl;
}

const vector<int>& Heap::getData() const {
    return data;
}
