#include <iostream>
#include "GUIManager.h"
using namespace std;

int main() {
    // Initialize ADTs
    Stack stack;
    Queue queue;
    Heap heap;
    PriorityQueue priorityQueue;
    RedBlackTree rbTree;
    BTree bTree(3);
    AVL avlTree;
    BST bst;

    GUIManager gui;

    int choice = 0;
    while (true) {
        cout << "\n--- Data Structures Menu ---\n";
        cout << "1. Work with Stack\n";
        cout << "2. Work with Queue\n";
        cout << "3. Work with Heap\n";
        cout << "4. Work with Priority Queue\n";
        cout << "5. Work with Red-Black Tree\n";
        cout << "6. Work with B-Tree\n";
        cout << "7. Work with AVL Tree\n";
        cout << "8. Work with Binary Search Tree (BST)\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 9) break;

        int subChoice, value;

        switch (choice) {
            case 1: // Stack
                while (true) {
                    cout << "\n--- Stack Menu ---\n";
                    cout << "1. Push\n2. Pop\n3. Display\n4. Back\n";
                    cin >> subChoice;
                    if (subChoice == 4) break;

                    switch (subChoice) {
                        case 1:
                            cout << "Enter value to push: ";
                            cin >> value;
                            stack.push(value);
                            break;
                        case 2:
                            stack.pop();
                            break;
                        case 3:
                            gui.renderStack(stack);
                            break;
                    }
                }
                break;

            case 2: // Queue
                while (true) {
                    cout << "\n--- Queue Menu ---\n";
                    cout << "1. Enqueue\n2. Dequeue\n3. Display\n4. Back\n";
                    cin >> subChoice;
                    if (subChoice == 4) break;

                    switch (subChoice) {
                        case 1:
                            cout << "Enter value to enqueue: ";
                            cin >> value;
                            queue.enqueue(value);
                            break;
                        case 2:
                            queue.dequeue();
                            break;
                        case 3:
                            gui.renderQueue(queue);
                            break;
                    }
                }
                break;

            case 3: // Heap
                while (true) {
                    cout << "\n--- Heap Menu ---\n";
                    cout << "1. Insert\n2. Remove\n3. Search\n4. Display\n5. Back\n";
                    cin >> subChoice;
                    if (subChoice == 5) break;

                    switch (subChoice) {
                        case 1:
                            cout << "Enter value to insert: ";
                            cin >> value;
                            heap.insert(value);
                            break;
                        case 2:
                            cout << "Enter value to remove: ";
                            cin >> value;
                            heap.remove(value);
                            break;
                        case 3:
                            cout << "Enter value to search: ";
                            cin >> value;
                            cout << (heap.search(value) ? "Found\n" : "Not Found\n");
                            break;
                        case 4:
                            gui.clear();
                            break;
                    }
                }
                break;

            case 4: // Priority Queue
                while (true) {
                    cout << "\n--- Priority Queue Menu ---\n";
                    cout << "1. Enqueue\n2. Dequeue\n3. Peek\n4. Display\n5. Back\n";
                    cin >> subChoice;
                    if (subChoice == 5) break;

                    switch (subChoice) {
                        case 1:
                            cout << "Enter value to enqueue: ";
                            cin >> value;
                            priorityQueue.enqueue(value);
                            break;
                        case 2:
                            priorityQueue.dequeue();
                            break;
                        case 3:
                            try {
                                cout << "Top element: " << priorityQueue.peek() << "\n";
                            } catch (const runtime_error &e) {
                                cout << e.what() << "\n";
                            }
                            break;
                        case 4:
                            gui.clear();
                            break;
                    }
                }
                break;

            case 5: // Red-Black Tree
                while (true) {
                    cout << "\n--- Red-Black Tree Menu ---\n";
                    cout << "1. Insert\n2. Delete\n3. Search\n4. Display\n5. Back\n";
                    cin >> subChoice;
                    if (subChoice == 5) break;

                    switch (subChoice) {
                        case 1:
                            cout << "Enter value to insert: ";
                            cin >> value;
                            rbTree.insert(value);
                            break;
                        case 2:
                            cout << "Enter value to delete: ";
                            cin >> value;
                            rbTree.remove(value);
                            break;
                        case 3:
                            cout << "Enter value to search: ";
                            cin >> value;
                            cout << (rbTree.search(value) ? "Found\n" : "Not Found\n");
                            break;
                        case 4:
                            gui.clear();
                            break;
                    }
                }
                break;

            case 6: // B-Tree
                while (true) {
                    cout << "\n--- B-Tree Menu ---\n";
                    cout << "1. Insert\n2. Delete\n3. Search\n4. Display\n5. Back\n";
                    cin >> subChoice;
                    if (subChoice == 5) break;

                    switch (subChoice) {
                        case 1:
                            cout << "Enter value to insert: ";
                            cin >> value;
                            bTree.insert(value);
                            break;
                        case 2:
                            cout << "Enter value to delete: ";
                            cin >> value;
                            bTree.remove(value);
                            break;
                        case 3:
                            cout << "Enter value to search: ";
                            cin >> value;
                            cout << (bTree.search(value) ? "Found\n" : "Not Found\n");
                            break;
                        case 4:
                            gui.clear();
                            break;
                    }
                }
                break;

            case 7: // AVL Tree
                while (true) {
                    cout << "\n--- AVL Tree Menu ---\n";
                    cout << "1. Insert\n2. Delete\n3. Search\n4. Display\n5. Back\n";
                    cin >> subChoice;
                    if (subChoice == 5) break;

                    switch (subChoice) {
                        case 1:
                            cout << "Enter value to insert: ";
                            cin >> value;
                            avlTree.insert(value);
                            break;
                        case 2:
                            cout << "Enter value to delete: ";
                            cin >> value;
                            avlTree.remove(value);
                            break;
                        case 3:
                            cout << "Enter value to search: ";
                            cin >> value;
                            cout << (avlTree.search(value) ? "Found\n" : "Not Found\n");
                            break;
                        case 4:
                            gui.clear();
                            break;
                    }
                }
                break;

            case 8: // BST
                while (true) {
                    cout << "\n--- BST Menu ---\n";
                    cout << "1. Insert\n2. Remove\n3. Search\n4. Display\n5. Back\n";
                    cin >> subChoice;
                    if (subChoice == 5) break;

                    switch (subChoice) {
                        case 1:
                            cout << "Enter value to insert: ";
                            cin >> value;
                            bst.insert(value);
                            break;
                        case 2:
                            cout << "Enter value to remove: ";
                            cin >> value;
                            bst.remove(value);
                            break;
                        case 3:
                            cout << "Enter value to search: ";
                            cin >> value;
                            cout << (bst.search(value) ? "Found\n" : "Not Found\n");
                            break;
                        case 4:
                            gui.renderBST(bst);
                            break;
                    }
                }
                break;

            default:
                cout << "Invalid choice.\n";
        }
    }

    return 0;
}
