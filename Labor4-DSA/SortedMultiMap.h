#pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>

typedef int TKey;
typedef int TValue;
typedef int TFunction;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111);
using namespace std;

class SMMIterator;

typedef bool(*Relation)(TKey, TKey);

struct ArrayValue {
    TKey key;
    TValue *values;
    int sizeValues;
    int capacityValues;
};

class SortedMultiMap {
    friend class SMMIterator;

public:
    //TODO - Representation

    Relation relation;
    int capacity;
    int sizeArray;
    int *next;
    ArrayValue *dynamicArray;
    int firstEmpty;
    TFunction h(TKey key) const;

public:

    // constructor
    SortedMultiMap(Relation r);

    void resizeUpValues(TKey key) const;

    void resizeDownValues(TKey key);

    static bool isPrim(int value);

    int findFirstPrim() const;
    int findLastPrim() const;
    void resizeUp();

    void resizeDown();

    void changeFirstEmpty();
    void removeValueFromKey(int positionKey,int positionValue) const;
    void freePosition(int position) const;
    //adds a new key value pair to the sorted multi map
    void add(TKey c, TValue v);

    //returns the values belonging to a given key
    vector<TValue> search(TKey c) const;

    //removes a key value pair from the sorted multimap
    //returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    bool remove(TKey c, TValue v);

    //returns the number of key-value pairs from the sorted multimap
    int size() const;

    //verifies if the sorted multi map is empty
    bool isEmpty() const;

    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)
    SMMIterator iterator() const;
    SortedMultiMap concat(SortedMultiMap sortedMultiMap);
    // destructor
    ~SortedMultiMap();

};
