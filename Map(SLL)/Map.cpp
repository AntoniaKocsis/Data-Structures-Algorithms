#include "Map.h"

Map::Map() {
    //TODO - Implementation
    currentSize = 0;
    head = nullptr;

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

}

TValue Map::add(TKey c, TValue v) {
    //TODO - Implementation
    Node *newNode = new Node;
    newNode->info = std::make_pair(c, v);
    newNode->next = nullptr;
    if (isEmpty()) {
        head = newNode;
        currentSize++;
        return NULL_TVALUE;
    }
    TValue value;
    Node *current = head;
    Node *previous = nullptr;
    while (current != nullptr) {
        if (current->info.first == c) {
            value = current->info.second;
            current->info.second = v;
            return value;
        }
        previous = current;
        current = current->next;
    }
    previous->next = newNode;
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
    Node *previous = nullptr;
    TValue value;
    while (current != nullptr && current->info.first != c) {
        previous = current;
        current = current->next;
    }
    if(previous == nullptr){
        head = head->next;
    } else{
        previous->next = current->next;
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




