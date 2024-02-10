#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>

using namespace std;

SMMIterator::SMMIterator(const SortedMultiMap &d) : map(d) {
    //TODO - Implementation
    /** Complexity: Best: Theta( n )
*              Average: Theta( n^3 )
*              Worst: Theta( n^3 ) **/
    currentElem = 0;
    currentValue = 0;
    capacity = map.capacity;
    sizeArray = 0;
    relation = map.relation;
    sortedMultiMap = new ArrayValue[capacity];
    for (int i = 0; i < capacity; i++) {
        sortedMultiMap[i].key = -1;
        sortedMultiMap[i].sizeValues = 0;
        sortedMultiMap[i].capacityValues = 20;
        sortedMultiMap[i].values = new TValue[sortedMultiMap[i].capacityValues];
    }
    for (int i = 0; i < map.capacity; i++)
        if (map.dynamicArray[i].key != -1) {
             insert(map.dynamicArray[i]);
        }

}


int SMMIterator::findPosition(TKey key) {
    /** Complexity: Best: Theta(1)
 *              Average: Theta( log(n) )
 *              Worst: Theta( log(n) ) **/
    int left = 0, right = sizeArray - 1;
    int mid =  left + (right - left) / 2;
    if (sortedMultiMap[mid].key == key)
        return mid;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (sortedMultiMap[mid].key == key) {
            left = mid;
            break;
        } else if (relation(sortedMultiMap[mid].key, key))
            left = mid + 1;
        else
            right = mid - 1;
    }

    return left;
}

void SMMIterator::insert(ArrayValue element) {
    /** Complexity: Best: Theta(n)
*              Average: Theta( n^2 )
*              Worst: Theta( n^2 ) **/
    int position;
    if (sizeArray == 0)
        position = 0;

    else {
        position = findPosition(element.key);

        for (int i = sizeArray - 1; i >= position; i--) {
            sortedMultiMap[i + 1].key = sortedMultiMap[i].key;
            sortedMultiMap[i + 1].sizeValues = sortedMultiMap[i].sizeValues;
            sortedMultiMap[i + 1].capacityValues = sortedMultiMap[i].capacityValues;
            delete[] sortedMultiMap[i + 1].values;
            sortedMultiMap[i + 1].values = new TValue[sortedMultiMap[i].capacityValues];
            for (int j = 0; j < sortedMultiMap[i].sizeValues; j++) {
                sortedMultiMap[i + 1].values[j] = sortedMultiMap[i].values[j];
            }
        }
    }
    sortedMultiMap[position].key = element.key;
    sortedMultiMap[position].sizeValues = element.sizeValues;
    sortedMultiMap[position].capacityValues = element.capacityValues;
    delete[] sortedMultiMap[position].values;
    sortedMultiMap[position].values = new TValue[element.capacityValues];
    for (int j = 0; j < element.sizeValues; j++) {
        sortedMultiMap[position].values[j] = element.values[j];
    }
    sizeArray++;

}

void SMMIterator::first() {
    /** Complexity: Best: Theta(1) **/
    currentElem = 0;
    currentValue = 0;
}

void SMMIterator::next() {
    /** Complexity: Best: Theta(1) **/
    if (!valid() || currentValue >= sortedMultiMap[currentElem].sizeValues)
        throw invalid_argument("");
    if (currentValue == sortedMultiMap[currentElem].sizeValues - 1) {
        currentElem++;
        currentValue = 0;
    } else {
        currentValue++;
    }

}

bool SMMIterator::valid() const {
    //TODO - Implementation
    /** Complexity: Best: Theta(1) **/
    if (map.isEmpty() || currentElem == sizeArray)
        return false;
    return true;
}

TElem SMMIterator::getCurrent() const {
    /** Complexity: Best: Theta(1) **/
    if (currentElem >= sizeArray || !valid())
        throw invalid_argument("");
    TElem pair1 = make_pair(sortedMultiMap[currentElem].key, sortedMultiMap[currentElem].values[currentValue]);
    return pair1;
}


