#ifndef STACK_H
#define STACK_H

#include <vector>
#include <iostream>

class Stack {
private:
    std::vector<int> data;

public:
    void push(int value);
    void pop();
    int peek() const;
    bool isEmpty() const;
    void display() const;
    const std::vector<int>& getData() const;
};

#endif
