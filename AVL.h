#ifndef AVL_H
#define AVL_H
#include <iostream>

class AVL {
public:
    struct Node { 
        int key;
        Node* left;
        Node* right;
        int height;

        Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
    };

private:
    Node* root;

    int getHeight(Node* node) const;
    int getBalanceFactor(Node* node) const;
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    Node* insert(Node* node, int key);
    Node* minValueNode(Node* node);
    Node* remove(Node* node, int key);
    void inOrder(Node* node) const;

public:
    AVL();
    ~AVL();
    void insert(int key);
    void remove(int key);
    bool search(int key) const;
    void display() const;
    Node* getRoot() const;

private:
    void clear(Node* node);
};

#endif
