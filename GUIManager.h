#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <SFML/Graphics.hpp>
#include "Stack.h"
#include "Queue.h"
#include "Heap.h"
#include "PriorityQueue.h"
#include "RedBlack.h"
#include "BTree.h"
#include "AVL.h"
#include "BST.h"

class GUIManager {
private:
    sf::RenderWindow window;
    sf::Font font;

    // Visualization helpers for tree-based ADTs
    void visualizeBST(BST::Node* node, float x, float y, float xOffset, float yOffset);
    void visualizeRedBlackTree(RedBlackTree::Node* node, float x, float y, float xOffset, float yOffset, RedBlackTree::Node* nil);
    void visualizeAVLTree(AVL::Node* node, float x, float y, float xOffset, float yOffset);
    void visualizeBTree(BTree::Node* node, float x, float y, float xOffset, float yOffset);

    // Helper to draw tree connections
    void drawTreeConnections(float x1, float y1, float x2, float y2);

    // Event handling
    void handleWindowEvents();

public:
    GUIManager();
    ~GUIManager();

    bool isOpen() const;
    void clear();
    void display();

    // Rendering functions
    void renderStack(const Stack& stack);
    void renderQueue(const Queue& queue);
    void renderHeap(const Heap& heap);
    void renderPriorityQueue(const PriorityQueue& priorityQueue);
    void renderRedBlackTree(const RedBlackTree& rbTree);
    void renderBTree(const BTree& bTree);
    void renderAVLTree(const AVL& avlTree);
    void renderBST(const BST& bst);
};

#endif
