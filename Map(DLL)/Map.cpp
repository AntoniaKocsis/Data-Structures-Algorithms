#include "Map.h"

Map::Map() {
    //TODO - Implementation
    currentSize = 0;
    head = nullptr;
    tail = nullptr;

}

Map::~Map() {
    //TODO - Implementation
    Node *current = head;
    Node *next = nullptr;
    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;

    }
    head = nullptr;
    tail = nullptr;

}

TValue Map::add(TKey c, TValue v) {
    //TODO - Implementation
    Node *newNode = new Node;
    newNode->info = std::make_pair(c, v);
    newNode->next = nullptr;
    newNode->previous = nullptr;
    if (isEmpty()) {
        head = newNode;
        tail = newNode;
        currentSize++;
        return NULL_TVALUE;
    }
    TValue value;
    Node *current = head;
    while (current != nullptr) {
        if (current->info.first == c) {
            value = current->info.second;
            current->info.second = v;
            return value;
        }
        current = current->next;
    }
    tail->next = newNode;
    newNode->previous = tail;
    tail = newNode;
    currentSize++;
    return NULL_TVALUE;

}

TValue Map::search(TKey c) const {
    //TODO - Implementation
    if (isEmpty())
        return NULL_TVALUE;
    Node *current = head;
    while (current != nullptr) {
        if (current->info.first == c) {
            return current->info.second;
        }
        current = current->next;
    }
    return NULL_TVALUE;
}

TValue Map::remove(TKey c) {
    //TODO - Implementation
    if (isEmpty())
        return NULL_TVALUE;
    if (search(c) == NULL_TVALUE)
        return NULL_TVALUE;
    Node *current = head;
    TValue value;
    while (current != nullptr && current->info.first != c) {
        current = current->next;
    }
    if (current->previous == nullptr) {

        if (current->next == nullptr) {
            head = nullptr;
            tail = nullptr;
        } else{
            head = head->next;
            head->previous = nullptr;
        }

    } else if (current->next == nullptr) {

        tail = tail->previous;
        tail->next = nullptr;

    }
    else {
        current->previous->next = current->next;
        current->next->previous = current->previous;

    }
    value = current->info.second;
    delete current;
    currentSize--;
    return value;
}


int Map::size() const {
    //TODO - Implementation
    return currentSize;
}

bool Map::isEmpty() const {
    //TODO - Implementation
    if (currentSize == 0)
        return true;
    return false;
}




