#ifndef BTREE_H
#define BTREE_H

#include <vector>
#include <iostream>

class BTree {
public:
    struct Node {
        std::vector<int> keys;
        std::vector<Node*> children;
        bool isLeaf;

        Node(bool leaf) : isLeaf(leaf) {}
    };

private:
    int t; 
    Node* root;

    void insertNonFull(Node* node, int key);
    void splitChild(Node* parent, int i, Node* child);
    void remove(Node* node, int key);
    void merge(Node* parent, int idx);
    void removeFromLeaf(Node* node, int idx);
    void removeFromNonLeaf(Node* node, int idx);
    int getPredecessor(Node* node, int idx);
    int getSuccessor(Node* node, int idx);
    Node* search(Node* node, int key) const;

public:
    BTree(int minDegree);
    void insert(int key);
    void remove(int key);
    bool search(int key) const;
    void display() const;
    Node* getRoot() const;
};

#endif
