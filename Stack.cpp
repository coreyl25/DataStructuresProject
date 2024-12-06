#include "Stack.h"
using namespace std;

void Stack::push(int value) {
    data.push_back(value);
}

void Stack::pop() {
    if (!data.empty()) {
        data.pop_back();
    } else {
        cout << "Stack is empty, nothing to pop!\n";
    }
}

int Stack::peek() const {
    if (!data.empty()) {
        return data.back();
    } else {
        throw runtime_error("Stack is empty, no top element!");
    }
}

bool Stack::isEmpty() const {
    return data.empty();
}

void Stack::display() const {
    if (data.empty()) {
        cout << "Stack is empty!\n";
        return;
    }
    for (int i = data.size() - 1; i >= 0; --i) {
        cout << data[i] << " ";
    }
    cout << "\n";
}

const vector<int>& Stack::getData() const {
    return data;
}
