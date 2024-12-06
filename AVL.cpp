#include "AVL.h"

// Constructor
AVL::AVL() : root(nullptr) {}

// Destructor
AVL::~AVL() {
    clear(root);
}

// Clear the tree
void AVL::clear(Node* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

// Height of the node
int AVL::getHeight(Node* node) const {
    return node ? node->height : 0;
}

// Balance factor 
int AVL::getBalanceFactor(Node* node) const {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// Right rotation
AVL::Node* AVL::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

// Left rotation
AVL::Node* AVL::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

// Insert key into AVL tree
AVL::Node* AVL::insert(Node* node, int key) {
    if (!node) {
        return new Node(key);
    }

    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        return node;
    }

    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    int balance = getBalanceFactor(node);

    // Left Left Case
    if (balance > 1 && key < node->left->key) {
        return rotateRight(node);
    }

    // Right Right Case
    if (balance < -1 && key > node->right->key) {
        return rotateLeft(node);
    }

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Remove key from AVL tree
AVL::Node* AVL::remove(Node* node, int key) {
    if (!node) {
        return node;
    }

    if (key < node->key) {
        node->left = remove(node->left, key);
    } else if (key > node->key) {
        node->right = remove(node->right, key);
    } else {
        if (!node->left || !node->right) {
            Node* temp = node->left ? node->left : node->right;
            if (!temp) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp;
            }
            delete temp;
        } else {
            Node* temp = minValueNode(node->right);
            node->key = temp->key;
            node->right = remove(node->right, temp->key);
        }
    }

    if (!node) {
        return node;
    }

    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    int balance = getBalanceFactor(node);

    // Left Left Case
    if (balance > 1 && getBalanceFactor(node->left) >= 0) {
        return rotateRight(node);
    }

    // Left Right Case
    if (balance > 1 && getBalanceFactor(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Right Case
    if (balance < -1 && getBalanceFactor(node->right) <= 0) {
        return rotateLeft(node);
    }

    // Right Left Case
    if (balance < -1 && getBalanceFactor(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Find the node with the smallest key
AVL::Node* AVL::minValueNode(Node* node) {
    Node* current = node;
    while (current->left) {
        current = current->left;
    }
    return current;
}

// Insert key 
void AVL::insert(int key) {
    root = insert(root, key);
}

// Remove key 
void AVL::remove(int key) {
    root = remove(root, key);
}

// Search for a key in the tree
bool AVL::search(int key) const {
    Node* current = root;
    while (current) {
        if (current->key == key) {
            return true;
        }
        current = (key < current->key) ? current->left : current->right;
    }
    return false;
}

// In-order traversal for display
void AVL::inOrder(Node* node) const {
    if (node) {
        inOrder(node->left);
        std::cout << node->key << " ";
        inOrder(node->right);
    }
}

// Display the AVL tree
void AVL::display() const {
    if (!root) {
        std::cout << "Tree is empty!\n";
    } else {
        inOrder(root);
        std::cout << "\n";
    }
}

// Get the root node
AVL::Node* AVL::getRoot() const {
    return root;
}
