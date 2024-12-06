#ifndef BST_H
#define BST_H

#include <iostream>
#include <vector>

class BST {
public:
    struct Node {
        int key;
        Node* left;
        Node* right;

        Node(int value) : key(value), left(nullptr), right(nullptr) {}
    };

private:
    Node* root;

    Node* insert(Node* node, int key);
    Node* remove(Node* node, int key);
    Node* findMin(Node* node);
    bool search(Node* node, int key) const;
    void inOrder(Node* node, std::vector<int>& elements) const;
    void clear(Node* node);

public:
    BST();
    ~BST();

    void insert(int key);
    void remove(int key);
    bool search(int key) const;
    std::vector<int> inOrderTraversal() const;
    void clear();

    Node* getRoot() const;
};

#endif
