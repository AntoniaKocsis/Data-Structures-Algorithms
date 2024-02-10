#include "SortedMap.h"
#include <exception>

using namespace std;

SortedMap::SortedMap(Relation r) {
    //TODO - Implementation
    relation = r;
    capacity = 999999;
    currentSize = 0;
    dynamicArray = new TElem[capacity];

}

int SortedMap::findPosition(TKey key) {
    int left = 0, right = currentSize - 1;
    int mid;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (dynamicArray[mid].first == key) {
            left = mid;
            break;
        } else if (relation(dynamicArray[mid].first, key))
            left = mid + 1;
        else
            right = mid - 1;
    }
    // Needed position is saved in left
    return left;
}

TValue SortedMap::add(TKey k, TValue v) {
    //TODO - Implementation
    TElem elem = std::make_pair(k, v);
    if (isEmpty()) {
        dynamicArray[currentSize] = elem;
        currentSize++;
        return NULL_TVALUE;
    }
    int index = binarySearch(0, currentSize - 1, k);
    if (index != -1) {
        TValue value = dynamicArray[index].second;
        dynamicArray[index].second = v;
        return value;
    }
    int position = findPosition(k);
    for (int i = currentSize; i > position; i--) {
        dynamicArray[i] = dynamicArray[i - 1];
    }
    dynamicArray[position] = elem;
    currentSize++;
    return NULL_TVALUE;
}

int SortedMap::binarySearch(int left, int right, TKey key) const {
    if (left > right)
        return -1;
    if (dynamicArray[left].first == key)
        return left;
    if (dynamicArray[right].first == key)
        return right;
    int mid = (left + right) / 2;
    if (dynamicArray[mid].first == key)
        return mid;
    if (relation(dynamicArray[mid].first, key))
        return binarySearch(mid + 1, right, key);
    else {
        return binarySearch(left, mid - 1, key);
    }

}

TValue SortedMap::search(TKey k) const {
    //TODO - Implementation
    if (isEmpty())
        return NULL_TVALUE;
    if (binarySearch(0, currentSize - 1, k) == -1)
        return NULL_TVALUE;
    int position = binarySearch(0, currentSize - 1, k);
    return dynamicArray[position].second;
}

TValue SortedMap::remove(TKey k) {
    //TODO - Implementation
    if (isEmpty())
        return NULL_TVALUE;
    int position = binarySearch(0, currentSize - 1, k);
    if (position == -1)
        return NULL_TVALUE;
    TValue value;
    value = dynamicArray[position].second;
    for (int i = position; i < currentSize - 1; i++)
        dynamicArray[i] = dynamicArray[i + 1];
    currentSize--;
    return value;
}

int SortedMap::size() const {
    //TODO - Implementation
    return currentSize;
}

bool SortedMap::isEmpty() const {
    //TODO - Implementation
    if (currentSize == 0)
        return true;
    return false;
}

SortedMap::~SortedMap() {
    //TODO - Implementation
    delete[] dynamicArray;
}
