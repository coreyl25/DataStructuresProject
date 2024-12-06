#include "BTree.h"
#include <queue> // Include for std::queue

BTree::BTree(int minDegree) : t(minDegree), root(nullptr) {}

void BTree::insert(int key) {
    if (!root) {
        root = new Node(true);
        root->keys.push_back(key);
    } else {
        if (root->keys.size() == 2 * t - 1) {
            Node* newRoot = new Node(false);
            newRoot->children.push_back(root);
            splitChild(newRoot, 0, root);
            root = newRoot;
        }
        insertNonFull(root, key);
    }
}

void BTree::insertNonFull(Node* node, int key) {
    int i = node->keys.size() - 1;

    if (node->isLeaf) {
        node->keys.push_back(0);
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            --i;
        }
        node->keys[i + 1] = key;
    } else {
        while (i >= 0 && key < node->keys[i]) --i;
        ++i;

        if (node->children[i]->keys.size() == 2 * t - 1) {
            splitChild(node, i, node->children[i]);
            if (key > node->keys[i]) ++i;
        }
        insertNonFull(node->children[i], key);
    }
}

void BTree::splitChild(Node* parent, int i, Node* child) {
    Node* newChild = new Node(child->isLeaf);
    newChild->keys.assign(child->keys.begin() + t, child->keys.end());
    child->keys.resize(t - 1);

    if (!child->isLeaf) {
        newChild->children.assign(child->children.begin() + t, child->children.end());
        child->children.resize(t);
    }

    parent->children.insert(parent->children.begin() + i + 1, newChild);
    parent->keys.insert(parent->keys.begin() + i, child->keys[t - 1]);
}

void BTree::remove(int key) {
    if (!root) return;
    remove(root, key);

    if (root->keys.empty()) {
        Node* oldRoot = root;
        root = root->isLeaf ? nullptr : root->children[0];
        delete oldRoot;
    }
}

void BTree::remove(Node* node, int key) {
    int idx = 0;
    while (idx < node->keys.size() && key > node->keys[idx]) ++idx;

    if (idx < node->keys.size() && key == node->keys[idx]) {
        if (node->isLeaf) {
            removeFromLeaf(node, idx);
        } else {
            removeFromNonLeaf(node, idx);
        }
    } else if (!node->isLeaf) {
        bool isLastChild = (idx == node->keys.size());
        if (node->children[idx]->keys.size() < t) {
            merge(node, idx);
        }
        if (isLastChild && idx > node->keys.size()) {
            remove(node->children[idx - 1], key);
        } else {
            remove(node->children[idx], key);
        }
    }
}

void BTree::removeFromLeaf(Node* node, int idx) {
    node->keys.erase(node->keys.begin() + idx);
}

void BTree::removeFromNonLeaf(Node* node, int idx) {
    int key = node->keys[idx];
    if (node->children[idx]->keys.size() >= t) {
        int pred = getPredecessor(node, idx);
        node->keys[idx] = pred;
        remove(node->children[idx], pred);
    } else if (node->children[idx + 1]->keys.size() >= t) {
        int succ = getSuccessor(node, idx);
        node->keys[idx] = succ;
        remove(node->children[idx + 1], succ);
    } else {
        merge(node, idx);
        remove(node->children[idx], key);
    }
}

int BTree::getPredecessor(Node* node, int idx) {
    Node* current = node->children[idx];
    while (!current->isLeaf) current = current->children.back();
    return current->keys.back();
}

int BTree::getSuccessor(Node* node, int idx) {
    Node* current = node->children[idx + 1];
    while (!current->isLeaf) current = current->children[0];
    return current->keys[0];
}

void BTree::merge(Node* parent, int idx) {
    Node* child = parent->children[idx];
    Node* sibling = parent->children[idx + 1];

    child->keys.push_back(parent->keys[idx]);
    child->keys.insert(child->keys.end(), sibling->keys.begin(), sibling->keys.end());
    if (!child->isLeaf) {
        child->children.insert(child->children.end(), sibling->children.begin(), sibling->children.end());
    }

    parent->keys.erase(parent->keys.begin() + idx);
    parent->children.erase(parent->children.begin() + idx + 1);
    delete sibling;
}

bool BTree::search(int key) const {
    return search(root, key) != nullptr;
}

BTree::Node* BTree::search(Node* node, int key) const {
    if (!node) return nullptr;

    int i = 0;
    while (i < node->keys.size() && key > node->keys[i]) ++i;

    if (i < node->keys.size() && key == node->keys[i]) return node;

    return node->isLeaf ? nullptr : search(node->children[i], key);
}

void BTree::display() const {
    if (!root) {
        std::cout << "Tree is empty!" << std::endl;
        return;
    }

    std::queue<Node*> nodeQueue; // Use std::queue correctly
    nodeQueue.push(root);

    while (!nodeQueue.empty()) {
        Node* current = nodeQueue.front();
        nodeQueue.pop();

        for (int key : current->keys) {
            std::cout << key << " ";
        }
        std::cout << "| ";

        if (!current->isLeaf) {
            for (Node* child : current->children) {
                nodeQueue.push(child);
            }
        }
    }
    std::cout << std::endl;
}

BTree::Node* BTree::getRoot() const {
    return root;
}
