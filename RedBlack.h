#ifndef REDBLACK_H
#define REDBLACK_H
#include <iostream>

enum Color { RED, BLACK };

class RedBlackTree {
public:
    struct Node {
        int key;
        Color color;
        Node* left;
        Node* right;
        Node* parent;

        Node(int key = 0, Color color = BLACK, Node* left = nullptr, Node* right = nullptr, Node* parent = nullptr)
            : key(key), color(color), left(left), right(right), parent(parent) {}
    };

private:
    Node* root;
    Node* nil; // Node representing null leaves

    void leftRotate(Node* x);
    void rightRotate(Node* y);
    void insertFixup(Node* z);
    void deleteFixup(Node* x);
    void transplant(Node* u, Node* v);

    Node* minimum(Node* node) const;
    Node* search(Node* node, int key) const;

    void clear(Node* node);
    void inOrderTraversal(Node* node) const;

public:
    RedBlackTree();
    ~RedBlackTree();

    void insert(int key);
    void remove(int key);
    bool search(int key) const;

    Node* getRoot() const;
    Node* getNil() const; 

    void clear();
    void display() const;
};

#endif
