#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;


MultiMap::MultiMap() {
    //TODO - Implementation
    /** @Complexity θ(1) **/
    head = nullptr;
    tail = nullptr;
    currentSize = 0;

}


void MultiMap::add(TKey c, TValue v) {
    //TODO - Implementation
    /** @Complexity θ(1) **/
    Node *newNode = new Node;
    newNode->next = nullptr;
    newNode->prev = tail;
    newNode->pair = make_pair(c, v);
    if (isEmpty()) {
        head = newNode;
        tail = newNode;
    } else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    currentSize++;

}


bool MultiMap::remove(TKey c, TValue v) {
    //TODO - Implementation
    /** @Complexity
    * Best case Ω(1)
    * Average case θ(n)
    * Worst case O(n)
    * **/
    if (isEmpty())
        return false;
    vector<TValue> values;
    values = search(c);
    bool found = false;
    for (int value: values)
        if (value == v) {
            found = true;
            currentSize--;
        }
    if (found) {
        Node *current = head;
        while (current != nullptr) {
            if (current->pair.first == c && current->pair.second == v) {
                if (current == head) {
                    head = current->next;
                    if (head != nullptr) {
                        head->prev = nullptr;
                    }
                } else if (current == tail) {
                    tail = current->prev;
                    if (tail != nullptr)
                        tail->next = nullptr;
                } else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;

                }
                delete current;
                return true;

            }
            current = current->next;
        }
    }


    return false;
}


vector<TValue> MultiMap::search(TKey c) const {
    //TODO - Implementation
    /** @Complexity
    * Best case Ω(1)
    * Average case θ(n)
    * Worst case O(n)
    * **/
    if (head == nullptr)
        return {};

    bool found;
    vector<TValue> values;
    Node *current = head;
    while (current != nullptr) {
        if (current->pair.first == c) {
            values.push_back(current->pair.second);
            found = true;
        }
        current = current->next;
    }
    if (found)
        return values;
    return {};

}


int MultiMap::size() const {
    //TODO - Implementation
    /** @Complexity θ(1) **/
    return currentSize;
}


bool MultiMap::isEmpty() const {
    //TODO - Implementation
    /** @Complexity θ(1) **/
    if (head == nullptr)
        return true;
    return false;
}

MultiMapIterator MultiMap::iterator() const {
    /** @Complexity θ(1) **/
    return MultiMapIterator(*this);
}


MultiMap::~MultiMap() {
    //TODO - Implementation
    /** @Complexity θ(n) **/
    while (head != nullptr) {
        Node *currentNode = head;
        head = head->next;
        delete currentNode;
    }
}

