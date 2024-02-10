#include "Map.h"

Map::Map() {
    //TODO - Implementation
    currentSize = 0;
    capacity = 999999;
    dynamicArray = new TElem[capacity];
    next = new int[capacity];
    firstEmpty = 0;
    head = -1;
    for (int i = 0; i < capacity; i++)
        next[i] = i + 1;
    next[capacity - 1] = -1;

}

Map::~Map() {
    //TODO - Implementation
    delete[] dynamicArray;
    delete[] next;
}

TValue Map::add(TKey c, TValue v) {
    //TODO - Implementation
    int newNode = firstEmpty;
    firstEmpty = next[firstEmpty];
    next[newNode] = -1;
    TElem elem = std::make_pair(c, v);
    dynamicArray[newNode] = elem;
    if (isEmpty()) {
        head = newNode;
        currentSize++;
        return NULL_TVALUE;
    }
    int current = head;
    int previous = -1;
    while (current != -1) {
        if (dynamicArray[current].first == c) {
            TValue value = dynamicArray[current].second;
            dynamicArray[current].second = v;
            return value;
        }
        previous = current;
        current = next[current];
    }
    next[previous] = newNode;
    currentSize++;
    return NULL_TVALUE;


}

TValue Map::search(TKey c) const {
    //TODO - Implementation
    if (isEmpty())
        return NULL_TVALUE;
    int current = head;
    while(current != -1){
        if(dynamicArray[current].first == c){
            return dynamicArray[current].second;
        }
        current = next[current];
    }
    return NULL_TVALUE;
}

TValue Map::remove(TKey c) {
    //TODO - Implementation

    if(isEmpty() || search(c) == NULL_TVALUE)
        return NULL_TVALUE;
    TValue value;
    int current = head;
    int previous = -1;
    while(current != -1 && dynamicArray[current].first != c){
        previous = current;
        current = next[current];
    }// current => se sterge
    if(previous == -1){
        head = next[head];
    } else{
        next[previous] = next[current];
    }
    value = dynamicArray[current].second;
    currentSize--;
    next[current] = firstEmpty;
    firstEmpty = current;
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




