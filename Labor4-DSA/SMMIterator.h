#pragma once

#include "SortedMultiMap.h"


class SMMIterator {
    friend class SortedMultiMap;

public:
    //DO NOT CHANGE THIS PART
    const SortedMultiMap &map;

    SMMIterator(const SortedMultiMap &map);
    int capacity;
    Relation relation;
    int currentElem;
    int currentValue;
    ArrayValue *sortedMultiMap;
    int sizeArray;
    int findPosition(TKey key);

    void insert(ArrayValue element);

    //TODO - Representation

public:
    void first();

    void next();

    bool valid() const;

    TElem getCurrent() const;
};

