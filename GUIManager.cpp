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

void GUIManager::display() {
    window.display();
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

void GUIManager::renderStack(const Stack& stack) {
    clear();
    
    // Add title
    sf::Text titleText;
    titleText.setFont(font);
    titleText.setString("Stack Visualization");
    titleText.setCharacterSize(24);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(50, 20);
    window.draw(titleText);

    // Add stack information
    sf::Text infoText;
    infoText.setFont(font);
    infoText.setString("Size: " + std::to_string(stack.getData().size()));
    infoText.setCharacterSize(18);
    infoText.setFillColor(sf::Color::White);
    infoText.setPosition(50, 50);
    window.draw(infoText);

    const auto& data = stack.getData();
    float startX = 400, startY = 500;
    float elementWidth = 80;
    float elementHeight = 40;
    float spacing = 10;  // Space between elements

    // Draw stack container
    if (!data.empty()) {
        sf::RectangleShape container;
        container.setSize(sf::Vector2f(elementWidth + 10, (elementHeight + spacing) * data.size() + 10));
        container.setPosition(startX - 5, startY - (elementHeight + spacing) * (data.size() - 1) - 5);
        container.setFillColor(sf::Color::Transparent);
        container.setOutlineColor(sf::Color(100, 100, 100));  // Gray outline
        container.setOutlineThickness(2);
        window.draw(container);
    }

    // Draw stack elements
    for (size_t i = 0; i < data.size(); ++i) {
        // Position from bottom to top
        float yPos = startY - i * (elementHeight + spacing);
        
        // Element rectangle
        sf::RectangleShape rect(sf::Vector2f(elementWidth, elementHeight));
        rect.setPosition(startX, yPos);
        
        // Gradient color from bottom (darker) to top (lighter)
        float colorIntensity = 155 + (100.0f * i / std::max(1.0f, (float)data.size()));
        rect.setFillColor(sf::Color(0, 0, colorIntensity));  // Blue gradient
        rect.setOutlineColor(sf::Color::White);
        rect.setOutlineThickness(2);

        // Value text
        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(data[data.size() - 1 - i]));
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);
        
        // Center text in rectangle
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setPosition(
            startX + (elementWidth - textBounds.width) / 2,
            yPos + (elementHeight - textBounds.height) / 2
        );

        // Element index
        sf::Text indexText;
        indexText.setFont(font);
        indexText.setString("[" + std::to_string(data.size() - 1 - i) + "]");
        indexText.setCharacterSize(16);
        indexText.setFillColor(sf::Color(200, 200, 200));  // Light gray
        indexText.setPosition(startX - 50, yPos + (elementHeight - textBounds.height) / 2);

        // Draw elements
        window.draw(rect);
        window.draw(text);
        window.draw(indexText);
    }

    // Show empty stack message if needed
    if (data.empty()) {
        sf::Text emptyText;
        emptyText.setFont(font);
        emptyText.setString("Stack is Empty");
        emptyText.setCharacterSize(24);
        emptyText.setFillColor(sf::Color(150, 150, 150));
        sf::FloatRect textBounds = emptyText.getLocalBounds();
        emptyText.setPosition(startX - textBounds.width/2, startY - 100);
        window.draw(emptyText);
    }

    window.display();
    handleWindowEvents();
}

void GUIManager::renderQueue(const Queue& queue) {
    clear();
    
    sf::Text titleText;
    titleText.setFont(font);
    titleText.setString("Queue Visualization");
    titleText.setCharacterSize(24);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(50, 20);
    window.draw(titleText);

    // Queue info
    sf::Text infoText;
    infoText.setFont(font);
    infoText.setString("Size: " + std::to_string(queue.getData().size()));
    infoText.setCharacterSize(18);
    infoText.setFillColor(sf::Color::White);
    infoText.setPosition(50, 50);
    window.draw(infoText);

    const auto& data = queue.getData();
    float startX = 100, startY = 300;
    float elementWidth = 80;
    float elementHeight = 40;
    float spacing = 20; 

    // Queue container
    if (!data.empty()) {
        sf::RectangleShape container;
        container.setSize(sf::Vector2f((elementWidth + spacing) * data.size() - spacing + 10, elementHeight + 10));
        container.setPosition(startX - 5, startY - 5);
        container.setFillColor(sf::Color::Transparent);
        container.setOutlineColor(sf::Color(100, 100, 100)); 
        container.setOutlineThickness(2);
        window.draw(container);
    }

    // Draw queue elements
    for (size_t i = 0; i < data.size(); ++i) {
        float xPos = startX + i * (elementWidth + spacing);
        
        // Element rectangle
        sf::RectangleShape rect(sf::Vector2f(elementWidth, elementHeight));
        rect.setPosition(xPos, startY);
        
        // Color
        float colorIntensity = 255 - (100.0f * i / std::max(1.0f, (float)data.size()));
        rect.setFillColor(sf::Color(0, 0, colorIntensity));
        rect.setOutlineColor(sf::Color::White);
        rect.setOutlineThickness(2);

        // Value text
        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(data[i]));
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);
        
        // Center text in rectangle
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setPosition(
            xPos + (elementWidth - textBounds.width) / 2,
            startY + (elementHeight - textBounds.height) / 2
        );

        // Element index
        sf::Text indexText;
        indexText.setFont(font);
        indexText.setString("[" + std::to_string(i) + "]");
        indexText.setCharacterSize(16);
        indexText.setFillColor(sf::Color(200, 200, 200));  // Light gray
        indexText.setPosition(xPos + (elementWidth - textBounds.width) / 2, 
                            startY + elementHeight + 5);

        // Draw elements
        window.draw(rect);
        window.draw(text);
        window.draw(indexText);
    }

    // Empty queue message if needed
    if (data.empty()) {
        sf::Text emptyText;
        emptyText.setFont(font);
        emptyText.setString("Queue is Empty");
        emptyText.setCharacterSize(24);
        emptyText.setFillColor(sf::Color(150, 150, 150));
        sf::FloatRect textBounds = emptyText.getLocalBounds();
        emptyText.setPosition(400 - textBounds.width/2, startY);
        window.draw(emptyText);
    }

    window.display();
    handleWindowEvents();
}


void GUIManager::renderPriorityQueue(const PriorityQueue& priorityQueue) {
    clear();
    const auto& data = priorityQueue.getData();
    float startX = 100, startY = 300;
    
    // Draw title
    sf::Text titleText;
    titleText.setFont(font);
    titleText.setString("Priority Queue (Max Heap)");
    titleText.setCharacterSize(24);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(startX, startY - 50);
    window.draw(titleText);

    // Draw elements with priority indication
    for (size_t i = 0; i < data.size(); ++i) {
        // Main element rectangle
        sf::RectangleShape rect(sf::Vector2f(80, 40));
        rect.setPosition(startX + i * 100, startY);
        rect.setFillColor(sf::Color::Blue);
        rect.setOutlineColor(sf::Color::White);
        rect.setOutlineThickness(2);

        // Priority indicator
        float priority = 1.0f - (float)i / data.size();
        sf::RectangleShape priorityBar(sf::Vector2f(80, 5));
        priorityBar.setPosition(startX + i * 100, startY - 10);
        priorityBar.setFillColor(sf::Color(0, 0, 255, (unsigned char)(255 * priority)));

        // Value text
        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(data[i]));
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);
        text.setPosition(startX + i * 100 + 25, startY + 10);

        window.draw(rect);
        window.draw(priorityBar);
        window.draw(text);
    }

    window.display();
    handleWindowEvents();
}

void GUIManager::renderHeap(const Heap& heap) {
    clear();
    const auto& data = heap.getData();
    float startX = 400, startY = 100;
    float levelOffset = 80, nodeOffset = 80;
    size_t level = 0, index = 0;

    while (index < data.size()) {
        size_t nodesInLevel = 1 << level;
        float currentLevelWidth = (nodesInLevel - 1) * nodeOffset;
        float xOffset = startX - currentLevelWidth / 2;

        for (size_t i = 0; i < nodesInLevel && index < data.size(); ++i, ++index) {
            float currentX = xOffset + i * nodeOffset;
            float currentY = startY + level * levelOffset;

            // Draw connections to children
            if (2 * index + 1 < data.size()) { // Left child
                size_t nextLevel = level + 1;
                size_t nodesInNextLevel = 1 << nextLevel;
                float nextLevelWidth = (nodesInNextLevel - 1) * nodeOffset;
                float nextLevelStartX = startX - nextLevelWidth / 2;
                float childX = nextLevelStartX + (2 * i) * nodeOffset;
                float childY = startY + nextLevel * levelOffset;
                drawTreeConnections(currentX, currentY, childX, childY);
            }
            if (2 * index + 2 < data.size()) { // Right child
                size_t nextLevel = level + 1;
                size_t nodesInNextLevel = 1 << nextLevel;
                float nextLevelWidth = (nodesInNextLevel - 1) * nodeOffset;
                float nextLevelStartX = startX - nextLevelWidth / 2;
                float childX = nextLevelStartX + (2 * i + 1) * nodeOffset;
                float childY = startY + nextLevel * levelOffset;
                drawTreeConnections(currentX, currentY, childX, childY);
            }

            // Draw node
            sf::CircleShape nodeShape(20);
            nodeShape.setPosition(currentX - 20, currentY - 20);
            nodeShape.setFillColor(sf::Color::Blue);

            sf::Text text;
            text.setFont(font);
            text.setString(std::to_string(data[index]));
            text.setCharacterSize(15);
            text.setFillColor(sf::Color::White);
            text.setPosition(currentX - 10, currentY - 15);

            window.draw(nodeShape);
            window.draw(text);
        }
        ++level;
    }

    window.display();
    handleWindowEvents();
}

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

void GUIManager::renderRedBlackTree(const RedBlackTree& rbTree) {
    clear();
    
    // Add title
    sf::Text titleText;
    titleText.setFont(font);
    titleText.setString("Red-Black Tree");
    titleText.setCharacterSize(24);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(50, 20);
    window.draw(titleText);
    
    visualizeRedBlackTree(rbTree.getRoot(), 400, 80, 200, 80, rbTree.getNil());
    window.display();
    handleWindowEvents();
}

void GUIManager::visualizeRedBlackTree(RedBlackTree::Node* node, float x, float y, float xOffset, float yOffset, RedBlackTree::Node* nil) {
    if (node == nil) return;

    // Draw connections to children
    if (node->left != nil) {
        drawTreeConnections(x, y, x - xOffset, y + yOffset);
        visualizeRedBlackTree(node->left, x - xOffset, y + yOffset, xOffset * 0.6f, yOffset, nil);
    }
    
    if (node->right != nil) {
        drawTreeConnections(x, y, x + xOffset, y + yOffset);
        visualizeRedBlackTree(node->right, x + xOffset, y + yOffset, xOffset * 0.6f, yOffset, nil);
    }

    // Draw node 
    sf::CircleShape nodeShape(25);
    nodeShape.setPosition(x - 25, y - 25);
    
    // Set color RED or BLACK
    if (node->color == RED) {
        nodeShape.setFillColor(sf::Color::Red);
        nodeShape.setOutlineColor(sf::Color::White);
    } else {
        nodeShape.setFillColor(sf::Color::Black);
        nodeShape.setOutlineColor(sf::Color::White);
    }
    nodeShape.setOutlineThickness(2);

    // Draw key text
    sf::Text text;
    text.setFont(font);
    text.setString(std::to_string(node->key));
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    
    // Center text in node
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(x - textBounds.width/2, y - textBounds.height/2);

    // Draw to window
    window.draw(nodeShape);
    window.draw(text);
}

void GUIManager::renderBTree(const BTree& bTree) {
    clear();
    
    // Add title
    sf::Text titleText;
    titleText.setFont(font);
    titleText.setString("B-Tree");
    titleText.setCharacterSize(24);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(50, 20);
    window.draw(titleText);
    
    if (bTree.getRoot()) {
        visualizeBTree(bTree.getRoot(), 400, 80, 350, 80);
    }
    
    window.display();
    handleWindowEvents();
}

void GUIManager::visualizeBTree(BTree::Node* node, float x, float y, float xOffset, float yOffset) {
    if (!node) return;

    float nodeWidth = 50.0f * (node->keys.size() + 1);
    float nodeHeight = 40.0f;
    
    // Draw connections to children
    if (!node->isLeaf) {
        float childrenTotalWidth = xOffset * (node->children.size() - 1);
        float startX = x - childrenTotalWidth/2;
        
        for (size_t i = 0; i < node->children.size(); i++) {
            float childX = startX + i * xOffset;
            drawTreeConnections(x, y + nodeHeight/2, childX, y + yOffset);
            visualizeBTree(node->children[i], childX, y + yOffset, xOffset * 0.8f, yOffset);
        }
    }

    // Draw node rectangle
    sf::RectangleShape nodeRect(sf::Vector2f(nodeWidth, nodeHeight));
    nodeRect.setPosition(x - nodeWidth/2, y);
    nodeRect.setFillColor(sf::Color(50, 50, 200));
    nodeRect.setOutlineColor(sf::Color::White);
    nodeRect.setOutlineThickness(2);
    window.draw(nodeRect);

    // Draw vertical separators
    for (size_t i = 1; i < node->keys.size(); i++) {
        float sepX = x - nodeWidth/2 + i * (nodeWidth/(node->keys.size()));
        sf::RectangleShape separator(sf::Vector2f(2, nodeHeight));
        separator.setPosition(sepX, y);
        separator.setFillColor(sf::Color::White);
        window.draw(separator);
    }

    // Draw keys
    for (size_t i = 0; i < node->keys.size(); i++) {
        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(node->keys[i]));
        text.setCharacterSize(18);
        text.setFillColor(sf::Color::White);
        
        // Center each key
        float sectionWidth = nodeWidth/node->keys.size();
        float textX = x - nodeWidth/2 + i * sectionWidth;
        
        // Text bounds for centering
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setPosition(textX + (sectionWidth - textBounds.width)/2, 
                        y + (nodeHeight - textBounds.height)/2);
        
        window.draw(text);
    }
}

void GUIManager::renderAVLTree(const AVL& avlTree) {
    clear();
    
    // Add title/legend
    sf::Text titleText;
    titleText.setFont(font);
    titleText.setString("AVL Tree");
    titleText.setCharacterSize(24);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(50, 20);
    window.draw(titleText);
    
    // Balance factor
    sf::Text legendText;
    legendText.setFont(font);
    legendText.setString("Balance Factor: (height of left subtree - height of right subtree)");
    legendText.setCharacterSize(16);
    legendText.setFillColor(sf::Color::White);
    legendText.setPosition(50, 50);
    window.draw(legendText);
    
    if (avlTree.getRoot()) {
        visualizeAVLTree(avlTree.getRoot(), 400, 100, 200, 80);
    }
    
    window.display();
    handleWindowEvents();
}

void GUIManager::visualizeAVLTree(AVL::Node* node, float x, float y, float xOffset, float yOffset) {
    if (!node) return;

    // Draw connections to children
    if (node->left) {
        drawTreeConnections(x, y, x - xOffset, y + yOffset);
        visualizeAVLTree(node->left, x - xOffset, y + yOffset, xOffset * 0.6f, yOffset);
    }
    
    if (node->right) {
        drawTreeConnections(x, y, x + xOffset, y + yOffset);
        visualizeAVLTree(node->right, x + xOffset, y + yOffset, xOffset * 0.6f, yOffset);
    }

    // Balance factor
    int balanceFactor = (node->left ? node->left->height : 0) - (node->right ? node->right->height : 0);

    // Draw node circle
    sf::CircleShape nodeShape(25);
    nodeShape.setPosition(x - 25, y - 25);
    
    // Color based on balance factor
    if (balanceFactor > 1 || balanceFactor < -1) {
        nodeShape.setFillColor(sf::Color::Red);  // Unbalanced
    } else if (balanceFactor == 1 || balanceFactor == -1) {
        nodeShape.setFillColor(sf::Color(255, 165, 0));  // Orange - borderline
    } else {
        nodeShape.setFillColor(sf::Color(0, 155, 0));  // Green - balanced
    }
    
    nodeShape.setOutlineColor(sf::Color::White);
    nodeShape.setOutlineThickness(2);
    window.draw(nodeShape);

    // Draw key value
    sf::Text keyText;
    keyText.setFont(font);
    keyText.setString(std::to_string(node->key));
    keyText.setCharacterSize(18);
    keyText.setFillColor(sf::Color::White);
    
    // Center key text
    sf::FloatRect keyBounds = keyText.getLocalBounds();
    keyText.setPosition(x - keyBounds.width/2, y - keyBounds.height/2);
    window.draw(keyText);

    // Draw balance factor and height
    sf::Text balanceText;
    balanceText.setFont(font);
    balanceText.setString("BF:" + std::to_string(balanceFactor) + " H:" + std::to_string(node->height));
    balanceText.setCharacterSize(14);
    balanceText.setFillColor(sf::Color::White);
    
    // Position balance factor text below node
    sf::FloatRect balanceBounds = balanceText.getLocalBounds();
    balanceText.setPosition(x - balanceBounds.width/2, y + 30);
    window.draw(balanceText);
}
