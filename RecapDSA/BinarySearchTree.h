#pragma once

#include <iostream>

using namespace std;
struct BSTNode {
    int info;
    BSTNode *left;
    BSTNode *right;
    BSTNode *parent;
};

class BinarySearchTree {
private:
    BSTNode *root;
public:
    BinarySearchTree() {
        root = nullptr;
    }

    void insert(int e) {
        BSTNode *newNode = new BSTNode;
        newNode->right = nullptr;
        newNode->left = nullptr;
        newNode->parent = nullptr;
        newNode->info = e;
        if (root == nullptr) {
            root = newNode;
            return;
        }
        if (root->info <= e && root->right == nullptr) {
            root->right = newNode;
            newNode->parent = root;
            return;
        }
        if (root->info > e && root->left == nullptr) {
            root->left = newNode;
            newNode->parent = root;
            return;
        }
        BSTNode *current = root;
        BSTNode *previous = nullptr;
        while (current != nullptr) {
            previous = current;
            if (current->info <= e) {
                current = current->right;
            } else {
                current = current->left;
            }

        }
        newNode->parent = previous;
        if (previous->info <= e) {
            previous->right = newNode;
        } else {
            previous->left = newNode;
        }

    }

    void levelOrder() {
        cout << "Level Order" << endl;
        queue<BSTNode *> nodes;
        if (root == nullptr)
            return;
        nodes.push(root);
        while (!nodes.empty()) {
            BSTNode *current = nodes.front();
            nodes.pop();
            cout << current->info << " ";
            if (current->left != nullptr)
                nodes.push(current->left);
            if (current->right != nullptr)
                nodes.push(current->right);
        }
        cout << endl;
    }

    BSTNode *findSuccessor(int v) {
        BSTNode *current = root;
        while (current != nullptr && current->info != v) {
            if (current->info < v)
                current = current->right;
            else
                current = current->left;
        }
        if (current == nullptr) {
            return nullptr;
        }
        if (current->right != nullptr) {
            current = current->right;
            BSTNode *previous;
            while (current != nullptr) {
                previous = current;
                current = current->left;
            }
            return previous;
        } else {
            BSTNode *p = current->parent;
            BSTNode *c = current;
            while (p != nullptr && p->left != c) {
                c = p;
                p = c->parent;
            }
            return p;

        }
    }

    void inOrder() {
        cout << "In Order" << endl;
        BSTNode *current = root;
        stack<BSTNode *> nodes;
        while (current != nullptr) {
            nodes.push(current);
            current = current->left;
        }
        while (!nodes.empty()) {
            current = nodes.top();
            nodes.pop();
            cout << current->info << " ";
            current = current->right;
            while (current != nullptr) {
                nodes.push(current);
                current = current->left;
            }
        }
        cout << endl;
    }

    void remove(int v) {
        if (root == nullptr)
            return;
        BSTNode *current = root;
        while (current != nullptr && current->info != v) {
            if (current->info < v) {
                current = current->right;
            } else
                current = current->left;
        }
        if (current == nullptr)
            return;
        BSTNode *previous = current->parent;
        if (current->left == nullptr && current->right == nullptr) {
            if (previous == nullptr) {
                root = nullptr;
                delete current;
                return;
            }
            if (previous->left == current) {
                previous->left = nullptr;
                delete current;
                return;
            }
            if (previous->right == current) {
                previous->right = nullptr;
                delete current;
                return;
            }
        }
        if (current->left != nullptr && current->right == nullptr) {
            BSTNode *child = current->left;
            if (previous == nullptr) {
                child->parent = nullptr;
                root = child;
                delete current;
                return;
            }
            if (previous->left == current) {
                previous->left = child;
                child->parent = previous;
                delete current;
                return;
            }
            if (previous->right == current) {
                previous->right = child;
                child->parent = previous;
                delete current;
                return;
            }

        }
        if (current->right != nullptr && current->left == nullptr) {
            BSTNode *child = current->right;
            if (previous == nullptr) {
                child->parent = nullptr;
                root = child;
                delete current;
                return;
            }
            if (previous->left == current) {
                previous->left = child;
                child->parent = previous;
                delete current;
                return;
            }
            if (previous->right == current) {
                previous->right = child;
                child->parent = previous;
                delete current;
                return;
            }

        }
        if (current->left != nullptr && current->right != nullptr) {
            BSTNode *successor = findSuccessor(current->info);
            current->info = successor->info;
            BSTNode *successorParent = successor->parent;

            if (successor == successorParent->left) {
                successorParent->left = successor->right;
            } else {
                successorParent->right = successor->right;
            }

            if (successor->right != nullptr) {
                successor->right->parent = successorParent;
            }

            delete successor;
        }
    }

    void destroy(BSTNode *node) {
        if (node != nullptr) {
            destroy(node->left);
            destroy(node->right);
        }
    }

    ~BinarySearchTree() {
        destroy(root);
    }
};