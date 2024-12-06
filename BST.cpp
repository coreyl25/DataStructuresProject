#include "BST.h"

BST::BST() : root(nullptr) {}

BST::~BST() {
    clear();
}

void BST::clear() {
    clear(root);
    root = nullptr;
}

void BST::clear(Node* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

BST::Node* BST::insert(Node* node, int key) {
    if (!node) return new Node(key);

    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    }
    return node;
}

void BST::insert(int key) {
    root = insert(root, key);
}

BST::Node* BST::remove(Node* node, int key) {
    if (!node) return nullptr;

    if (key < node->key) {
        node->left = remove(node->left, key);
    } else if (key > node->key) {
        node->right = remove(node->right, key);
    } else {
        if (!node->left) {
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (!node->right) {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        Node* temp = findMin(node->right);
        node->key = temp->key;
        node->right = remove(node->right, temp->key);
    }
    return node;
}

void BST::remove(int key) {
    root = remove(root, key);
}

BST::Node* BST::findMin(Node* node) {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

bool BST::search(Node* node, int key) const {
    if (!node) return false;
    if (key == node->key) return true;
    return key < node->key ? search(node->left, key) : search(node->right, key);
}

bool BST::search(int key) const {
    return search(root, key);
}

void BST::inOrder(Node* node, std::vector<int>& elements) const {
    if (node) {
        inOrder(node->left, elements);
        elements.push_back(node->key);
        inOrder(node->right, elements);
    }
}

std::vector<int> BST::inOrderTraversal() const {
    std::vector<int> elements;
    inOrder(root, elements);
    return elements;
}

BST::Node* BST::getRoot() const {
    return root;
}
