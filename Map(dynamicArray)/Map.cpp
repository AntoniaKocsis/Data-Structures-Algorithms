#include "Map.h"

Map::Map() {
    //TODO - Implementation
    capacity = 99999;
    currentSize = 0;
    dynamicArray = new TElem[capacity];
}

Map::~Map() {
    //TODO - Implementation
    delete[] dynamicArray;
}

TValue Map::add(TKey c, TValue v) {
    //TODO - Implementation
    if(search(c) == NULL_TVALUE) {
        TElem elem = std::make_pair(c,v);
        dynamicArray[currentSize] = elem;
        currentSize++;
        return NULL_TVALUE;
    }
    for(int i = 0;i<currentSize;i++)
        if(dynamicArray[i].first == c)
        {
            TValue value;
            value = dynamicArray[i].second;
            dynamicArray[i].second = v;
            return value;
        }
}

TValue Map::search(TKey c) const {
    //TODO - Implementation
    if (isEmpty())
        return NULL_TVALUE;
    for (int i = 0; i < currentSize; i++)
        if (dynamicArray[i].first == c)
            return dynamicArray[i].second;
    return NULL_TVALUE;
}

TValue Map::remove(TKey c) {
    //TODO - Implementation
    if (search(c) == NULL_TVALUE)
        return NULL_TVALUE;
    int position = -1;
    for (int i = 0; i < currentSize; i++)
        if (dynamicArray[i].first == c) {
            position = i;
            break;
        }
    TValue value;
    value = dynamicArray[position].second;
    for (int i = position; i < currentSize - 1; i++)
        dynamicArray[i] = dynamicArray[i + 1];
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




