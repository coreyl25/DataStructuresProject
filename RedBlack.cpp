#include "RedBlack.h"
#include <iostream>
#include <stdexcept>
using namespace std;

// Constructor
RedBlackTree::RedBlackTree() {
    nil = new Node();
    nil->color = BLACK;
    nil->left = nullptr;
    nil->right = nullptr;
    root = nil;
}

// Destructor
RedBlackTree::~RedBlackTree() {
    clear();
    delete nil;
}

// Left Rotate
void RedBlackTree::leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != nil) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nil) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

// Right Rotate
void RedBlackTree::rightRotate(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    if (x->right != nil) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == nil) {
        root = x;
    } else if (y == y->parent->right) {
        y->parent->right = x;
    } else {
        y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
}

// Insert a key
void RedBlackTree::insert(int key) {
    Node* z = new Node(key, RED, nil, nil, nil);
    Node* y = nil;
    Node* x = root;

    while (x != nil) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    z->parent = y;
    if (y == nil) {
        root = z; // Tree was empty
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }

    z->left = nil;
    z->right = nil;
    z->color = RED;

    insertFixup(z);
}

// Fix violations after insertion
void RedBlackTree::insertFixup(Node* z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        } else {
            Node* y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

// Transplant, replaces one subtree as a child of its parent with another subtree
void RedBlackTree::transplant(Node* u, Node* v) {
    if (u->parent == nil) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

// Delete key
void RedBlackTree::remove(int key) {
    Node* z = search(root, key);
    if (z == nil) {
        cerr << "Key not found.\n";
        return;
    }

    Node* y = z;
    Node* x;
    Color originalColor = y->color;

    if (z->left == nil) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == nil) {
        x = z->left;
        transplant(z, z->left);
    } else {
        y = minimum(z->right);
        originalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    delete z;

    if (originalColor == BLACK) {
        deleteFixup(x);
    }
}

// Fix violations after deletion
void RedBlackTree::deleteFixup(Node* x) {
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        } else {
            Node* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

// Search for a key
bool RedBlackTree::search(int key) const {
    return search(root, key) != nil;
}

RedBlackTree::Node* RedBlackTree::search(Node* node, int key) const {
    if (node == nil || key == node->key) {
        return node;
    }
    if (key < node->key) {
        return search(node->left, key);
    }
    return search(node->right, key);
}

// Find minimum node
RedBlackTree::Node* RedBlackTree::minimum(Node* node) const {
    while (node->left != nil) {
        node = node->left;
    }
    return node;
}

// Clear
void RedBlackTree::clear(Node* node) {
    if (node == nil) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

void RedBlackTree::clear() {
    clear(root);
    root = nil;
}

// Display tree
void RedBlackTree::display() const {
    inOrderTraversal(root);
    cout << endl;
}

void RedBlackTree::inOrderTraversal(Node* node) const {
    if (node == nil) return;
    inOrderTraversal(node->left);
    cout << node->key << " ";
    inOrderTraversal(node->right);
}

// Get root node
RedBlackTree::Node* RedBlackTree::getRoot() const {
    return root;
}

// Get nil node
RedBlackTree::Node* RedBlackTree::getNil() const {
    return nil;
}

