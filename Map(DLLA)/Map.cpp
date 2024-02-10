#include "Map.h"

Map::Map() {
    //TODO - Implementation
    currentSize = 0;
    capacity = 999999;
    dynamicArray = new Node[capacity];
    firstEmpty = 0;
    head = -1;
    for (int i = 0; i < capacity; i++) {
        dynamicArray[i].next = i + 1;
        dynamicArray[i].previous = -1;
    }
    dynamicArray[capacity - 1].next = -1;

}

Map::~Map() {
    //TODO - Implementation
    delete[] dynamicArray;
}

int Map::allocate() {
    int position = firstEmpty;
    if (position != -1) {
        firstEmpty = dynamicArray[firstEmpty].next;
        if (firstEmpty != -1) {
            dynamicArray[firstEmpty].previous = -1;
        }
        dynamicArray[position].next = -1;
        dynamicArray[position].previous = -1;
    }
    return position;
}

TValue Map::add(TKey c, TValue v) {
    //TODO - Implementation
    int newNode = allocate();
    TElem elem = std::make_pair(c, v);
    dynamicArray[newNode].info = elem;
    if (isEmpty()) {
        head = newNode;
        tail = newNode;
        currentSize++;
        return NULL_TVALUE;
    }
    int current = head;
    while (current != -1) {
        if (dynamicArray[current].info.first == c) {
            TValue value;
            value = dynamicArray[current].info.second;
            dynamicArray[current].info.second = v;
            return value;
        }
        current = dynamicArray[current].next;
    }
    dynamicArray[newNode].previous = tail;
    dynamicArray[tail].next = newNode;
    tail = newNode;
    currentSize++;
    return NULL_TVALUE;


}

TValue Map::search(TKey c) const {
    //TODO - Implementation
    if (isEmpty())
        return NULL_TVALUE;
    int current = head;
    while (current != -1) {
        if (dynamicArray[current].info.first == c) {
            return dynamicArray[current].info.second;
        }
        current = dynamicArray[current].next;
    }
    return NULL_TVALUE;
}

TValue Map::remove(TKey c) {
    //TODO - Implementation

    if (isEmpty() || search(c) == NULL_TVALUE)
        return NULL_TVALUE;

    int current = head;
    while (current != -1 && dynamicArray[current].info.first != c) {
        current = dynamicArray[current].next;
    }
    int prevNode = dynamicArray[current].previous;
    int nextNode = dynamicArray[current].next;
    if (prevNode == -1) {
        if (nextNode == -1) {
            head = -1;
            tail = -1;
        } else {
            head = nextNode;
            dynamicArray[head].previous = -1;
        }
    } else if (nextNode == -1) {
        tail = prevNode;
        dynamicArray[tail].next = -1;
    } else {
        dynamicArray[prevNode].next = nextNode;
        dynamicArray[nextNode].previous = prevNode;
    }
    TValue value;
    value = dynamicArray[current].info.second;
    dynamicArray[current].next = firstEmpty;
    firstEmpty = current;
    dynamicArray[firstEmpty].previous = -1;
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




