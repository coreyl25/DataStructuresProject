#include "GUIManager.h"

GUIManager::GUIManager() : window(sf::VideoMode(800, 600), "Data Structures Visualization") {
    if (!font.loadFromFile("/System/Library/Fonts/Supplemental/Arial.ttf")) {
        throw std::runtime_error("Failed to load font!");
    }
}

GUIManager::~GUIManager() {
    if (window.isOpen()) {
        window.close();
    }
}

bool GUIManager::isOpen() const {
    return window.isOpen();
}

void GUIManager::clear() {
    window.clear(sf::Color::Black);
}

void GUIManager::handleWindowEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void GUIManager::drawTreeConnections(float x1, float y1, float x2, float y2) {
    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(x1, y1), sf::Color::White),
        sf::Vertex(sf::Vector2f(x2, y2), sf::Color::White)
    };
    window.draw(line, 2, sf::Lines);
}

// Stack visualization
void GUIManager::renderStack(const Stack& stack) {
    clear();
    const auto& data = stack.getData();
    float startX = 400, startY = 500;
    for (size_t i = 0; i < data.size(); ++i) {
        sf::RectangleShape rect(sf::Vector2f(50, 30));
        rect.setPosition(startX, startY - i * 40);
        rect.setFillColor(sf::Color::Blue);

        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(data[data.size() - 1 - i]));
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);
        text.setPosition(startX + 10, startY - i * 40 + 5);

        window.draw(rect);
        window.draw(text);
    }
    window.display();
    handleWindowEvents();
}

// Queue visualization
void GUIManager::renderQueue(const Queue& queue) {
    clear();
    const auto& data = queue.getData();
    float startX = 100, startY = 300;
    for (size_t i = 0; i < data.size(); ++i) {
        sf::RectangleShape rect(sf::Vector2f(50, 30));
        rect.setPosition(startX + i * 60, startY);
        rect.setFillColor(sf::Color::Blue);

        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(data[i]));
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);
        text.setPosition(startX + i * 60 + 10, startY + 5);

        window.draw(rect);
        window.draw(text);
    }
    window.display();
    handleWindowEvents();
}

// BST visualization
void GUIManager::renderBST(const BST& bst) {
    clear();
    visualizeBST(bst.getRoot(), 400, 50, 200, 100);
    window.display();
    handleWindowEvents();
}

void GUIManager::visualizeBST(BST::Node* node, float x, float y, float xOffset, float yOffset) {
    if (!node) return;

    sf::CircleShape nodeShape(20);
    nodeShape.setPosition(x - 20, y - 20);
    nodeShape.setFillColor(sf::Color::Blue);

    sf::Text text;
    text.setFont(font);
    text.setString(std::to_string(node->key));
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setPosition(x - 10, y - 15);

    window.draw(nodeShape);
    window.draw(text);

    if (node->left) {
        drawTreeConnections(x, y, x - xOffset, y + yOffset);
        visualizeBST(node->left, x - xOffset, y + yOffset, xOffset / 2, yOffset);
    }

    if (node->right) {
        drawTreeConnections(x, y, x + xOffset, y + yOffset);
        visualizeBST(node->right, x + xOffset, y + yOffset, xOffset / 2, yOffset);
    }
}

// Red-Black Tree visualization
void GUIManager::renderRedBlackTree(const RedBlackTree& rbTree) {
    clear();
    visualizeRedBlackTree(rbTree.getRoot(), 400, 50, 200, 100, rbTree.getNil());
    window.display();
    handleWindowEvents();
}

void GUIManager::visualizeRedBlackTree(RedBlackTree::Node* node, float x, float y, float xOffset, float yOffset, RedBlackTree::Node* nil) {
    if (!node || node == nil) return;

    sf::CircleShape nodeShape(20);
    nodeShape.setPosition(x - 20, y - 20);
    nodeShape.setFillColor(node->color == RED ? sf::Color::Red : sf::Color::Black);

    sf::Text text;
    text.setFont(font);
    text.setString(std::to_string(node->key));
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setPosition(x - 10, y - 15);

    window.draw(nodeShape);
    window.draw(text);

    if (node->left != nil) {
        drawTreeConnections(x, y, x - xOffset, y + yOffset);
        visualizeRedBlackTree(node->left, x - xOffset, y + yOffset, xOffset / 2, yOffset, nil);
    }

    if (node->right != nil) {
        drawTreeConnections(x, y, x + xOffset, y + yOffset);
        visualizeRedBlackTree(node->right, x + xOffset, y + yOffset, xOffset / 2, yOffset, nil);
    }
}

// AVL Tree visualization
void GUIManager::renderAVLTree(const AVL& avlTree) {
    clear();
    visualizeAVLTree(avlTree.getRoot(), 400, 50, 200, 100);
    window.display();
    handleWindowEvents();
}

void GUIManager::visualizeAVLTree(AVL::Node* node, float x, float y, float xOffset, float yOffset) {
    if (!node) return;

    sf::CircleShape nodeShape(20);
    nodeShape.setPosition(x - 20, y - 20);
    nodeShape.setFillColor(sf::Color::Blue);

    sf::Text text;
    text.setFont(font);
    text.setString(std::to_string(node->key));
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setPosition(x - 10, y - 15);

    window.draw(nodeShape);
    window.draw(text);

    if (node->left) {
        drawTreeConnections(x, y, x - xOffset, y + yOffset);
        visualizeAVLTree(node->left, x - xOffset, y + yOffset, xOffset / 2, yOffset);
    }

    if (node->right) {
        drawTreeConnections(x, y, x + xOffset, y + yOffset);
        visualizeAVLTree(node->right, x + xOffset, y + yOffset, xOffset / 2, yOffset);
    }
}

// B-Tree visualization
void GUIManager::renderBTree(const BTree& bTree) {
    clear();
    visualizeBTree(bTree.getRoot(), 400, 50, 200, 100);
    window.display();
    handleWindowEvents();
}

void GUIManager::visualizeBTree(BTree::Node* node, float x, float y, float xOffset, float yOffset) {
    if (!node) return;

    for (size_t i = 0; i < node->keys.size(); ++i) {
        sf::RectangleShape rect(sf::Vector2f(40, 30));
        rect.setPosition(x + i * 50, y);
        rect.setFillColor(sf::Color::Blue);

        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(node->keys[i]));
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);
        text.setPosition(x + i * 50 + 10, y + 5);

        window.draw(rect);
        window.draw(text);
    }

    if (!node->isLeaf) {
        for (size_t i = 0; i < node->children.size(); ++i) {
            float childX = x + i * xOffset;
            float childY = y + yOffset;

            drawTreeConnections(x + i * 50 + 20, y + 30, childX, childY);
            visualizeBTree(node->children[i], childX, childY, xOffset / 2, yOffset);
        }
    }
}
