#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>

using namespace std;

SortedMultiMap::SortedMultiMap(Relation r) {
    /** Complexity: θ(1)**/
    root = nullptr;
    relation = r;
    sizeTree = 0;
}

void SortedMultiMap::add(TKey c, TValue v) {
    /**Complexity:
     * Best: θ(1)
     * Average: θ(log(n))
     * Worst: θ(n)**/
    Node *newNode = new Node;
    newNode->parent = nullptr;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->value.first = c;
    newNode->value.second = v;

    if (isEmpty()) {
        root = newNode;
        sizeTree++;
        return;
    }
    if ((!relation(c, root->value.first) || c == root->value.first) && root->right == nullptr) {
        root->right = newNode;
        newNode->parent = root;
        sizeTree++;
        return;
    }

    if ((relation(c, root->value.first) && c != root->value.first) && root->left == nullptr) {
        root->left = newNode;
        newNode->parent = root;
        sizeTree++;
        return;
    }

    Node *current = root;
    if (relation(c, root->value.first) && c != root->value.first) {
        current = root->left;
    } else {
        current = root->right;
    }

    Node *previous = current;
    while (current != nullptr) {
        previous = current;
        if (relation(c, current->value.first) && c != current->value.first) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    newNode->parent = previous;
    if (relation(c, previous->value.first) && newNode->value.first != previous->value.first)
        previous->left = newNode;
    else
        previous->right = newNode;
    sizeTree++;


}

vector<TValue> SortedMultiMap::search(TKey c) const {
    /**Complexity:
     * Best: θ(1)
     * Average: θ(log(n))
     * Worst: θ(n)**/
    //TODO - Implementation
    if (isEmpty())
        return {};
    vector<TValue> values={};
    bool found = false;
    Node *current = root;
    while (current != nullptr) {
        if (current->value.first == c) {
            found = true;
            values.push_back(current->value.second);
            current = current->right;
        } else if (relation(current->value.first, c)) {
            current = current->right;
        } else {
            current = current->left;
        }
    }
    if (found)
        return values;

    return {};
}

bool SortedMultiMap::remove(TKey c, TValue v) {
    /**Complexity:
     * Best: θ(1)
     * Average: θ(log(n))
     * Worst: θ(n)**/
    //TODO - Implementation
    if (isEmpty())
        return false;

    Node* current = root;
    Node* previous = nullptr;
    Node* nodeToRemove = nullptr;
    bool found = false;

    while (current != nullptr) {
        if (current->value.first == c && current->value.second == v) {
            nodeToRemove = current;
            found = true;
            break;
        }
        previous = current;

        if (relation(c, current->value.first))
            current = current->left;
        else
            current = current->right;
    }

    if (!found)
        return false;

    // Case 1: Node to remove has no children
    if (nodeToRemove->left == nullptr && nodeToRemove->right == nullptr) {
        if (nodeToRemove == root) {
            // Removing the root node
            delete root;
            root = nullptr;
        } else {
            if (previous->left == nodeToRemove)
                previous->left = nullptr;
            else
                previous->right = nullptr;
            delete nodeToRemove;
        }
    }
        // Case 2: Node to remove has two children
    else if (nodeToRemove->left != nullptr && nodeToRemove->right != nullptr) {
        Node* successorParent = nodeToRemove;
        Node* successor = nodeToRemove->right;
        while (successor->left != nullptr) {
            successorParent = successor;
            successor = successor->left;
        }

        nodeToRemove->value = successor->value;
        if (successorParent->left == successor)
            successorParent->left = successor->right;
        else
            successorParent->right = successor->right;
        delete successor;
    }
        // Case 3: Node to remove has one child
    else {
        Node* child = (nodeToRemove->left != nullptr) ? nodeToRemove->left : nodeToRemove->right;
        if (nodeToRemove == root) {
            // Removing the root node
            root = child;
            child->parent = nullptr;
        } else {
            if (previous->left == nodeToRemove)
                previous->left = child;
            else
                previous->right = child;
            child->parent = previous;
        }
        delete nodeToRemove;
    }

    sizeTree--;
    return true;
}


int SortedMultiMap::size() const {
    /** Complexity: θ(1)**/
    return sizeTree;
}


bool SortedMultiMap::isEmpty() const {
    /** Complexity: θ(1)**/
    if(sizeTree == 0)
        return true;
    return false;
}

SMMIterator SortedMultiMap::iterator() const {
    return SMMIterator(*this);
}
void SortedMultiMap::destroy(Node *node) {
    if (node != nullptr) {
        free(node->left);
        free(node->right);
        delete node;
    }
}

SortedMultiMap::~SortedMultiMap() {
    /** Complexity: θ(n)**/
    //TODO - Implementation
    destroy(root);
}
