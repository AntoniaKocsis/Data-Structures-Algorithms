#include <exception>
#include <assert.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include "SortedMap.h"
#include "ExtendedTest.h"

using namespace std;

bool increasing(TKey c1, TKey c2) {
    if (c1 <= c2) {
        return true;
    } else {
        return false;
    }
}

bool decreasing(TKey c1, TKey c2) {
    if (c1 >= c2) {
        return true;
    } else {
        return false;
    }
}

void testCreate() {
    cout << "Test create" << endl;
    SortedMap sm(increasing);
    assert(sm.size() == 0);
    assert(sm.isEmpty());

    for (int i = 0; i < 10; i++) {
        assert(sm.search(i) == NULL_TVALUE);
    }

    for (int i = -10; i < 10; i++) {
        assert(sm.remove(i) == NULL_TVALUE);
    }
}

void testSearch(Relation r) {
    cout << "Test search" << endl;
    SortedMap sm(r);
    int cMin = 0;
    int cMax = 10;
    try {
        for (int i = cMin; i <= cMax; i++) {
            sm.add(i, i + 1);
        }
        assert(true);
    } catch (exception&) {
        assert(false);
    }
    int intervalDim = 10;
    for (int i = cMin; i <= cMax; i++) {
        assert(sm.search(i) == i + 1);
    }
    for (int i = cMin - intervalDim; i < cMin; i++) {
        assert(sm.search(i) == NULL_TVALUE);
    }
    for (int i = cMax + 1; i < cMax + intervalDim; i++) {
        assert(sm.search(i) == NULL_TVALUE);
    }
}

void testSearch() {
    testSearch(increasing);
    testSearch(decreasing);
}

vector<int> keysInRandomOrder(int cMin, int cMax) {
    vector<int> keys;
    for (int c = cMin; c <= cMax; c++) {
        keys.push_back(c);
    }
    int n = keys.size();
    for (int i = 0; i < n - 1; i++) {
        int j = i + rand() % (n - i);
        swap(keys[i], keys[j]);
    }
    return keys;
}

void populateSMEmpty(SortedMap& sm, int cMin, int cMax) {
    vector<int> keys = keysInRandomOrder(cMin, cMax);
    int n = keys.size();
    for (int i = 0; i < n; i++) {
        assert(sm.add(keys[i], keys[i]) == NULL_TVALUE);
    }
}

void rePopulateSMShift(SortedMap& sm, int cMin, int cMax, int shift) {
    vector<int> keys = keysInRandomOrder(cMin, cMax);
    int n = keys.size();
    for (int i = 0; i < n; i++) {
        assert(sm.add(keys[i], keys[i] - shift) == keys[i]);
    }
}

void populateSMShift(SortedMap& sm, int cMin, int cMax, int shift) {
    vector<int> keys = keysInRandomOrder(cMin, cMax);
    int n = keys.size();
    for (int i = 0; i < n; i++) {
        sm.add(keys[i], keys[i] - shift);
    }
}

void testAddAndSearch(Relation r) {
    cout << "Test add and search" << endl;
    SortedMap sm(r);
    int cMin = 100;
    int cMax = 200;

    populateSMEmpty(sm, cMin, cMax);
    for (int c = cMin; c <= cMax; c++) {
        assert(sm.search(c) == c);
    }
    assert(sm.size() == (cMax - cMin + 1));

    rePopulateSMShift(sm, cMin, cMax, 1);
    assert(sm.size() == (cMax - cMin + 1));
    populateSMShift(sm, 2 * cMax, 3 * cMax, 2 * cMax - cMin);
    for (int c = 2 * cMax; c <= 3 * cMax; c++) {
        assert(sm.search(c) == c - 2 * cMax + cMin);
    }
    assert(sm.size() == (cMax - cMin + 1) + (cMax + 1));

}

void testAdd() {
    testAddAndSearch(increasing);
    testAddAndSearch(decreasing);
}

void testRemoveAndSearch(Relation r) {
    cout << "Test remove and search" << endl;
    SortedMap sm(r);
    int cMin = 10;
    int cMax = 20;
    populateSMEmpty(sm, cMin, cMax);
    for (int c = cMax + 1; c <= 2 * cMax; c++) {
        assert(sm.remove(c) == NULL_TVALUE);
    }
    int dim = cMax - cMin + 1;
    assert(sm.size() == dim);
    for (int c = cMin; c <= cMax; c++) {
        assert(sm.remove(c) == c);
        assert(sm.search(c) == NULL_TVALUE);
        dim--;
        assert(sm.size() == dim);

    }

    for (int c = cMin; c <= cMax; c++) {
        assert(sm.remove(c) == NULL_TVALUE);
    }
    assert(sm.isEmpty());
    assert(sm.size() == 0);

}

void testRemove() {
    testRemoveAndSearch(increasing);
    testRemoveAndSearch(decreasing);
}

void testQuantity(){
    cout << "Test quantity" << endl;
    SortedMap sm(increasing);
    int cMin = -3000;
    int cMax = 3000;
    vector<int> keys  = keysInRandomOrder(cMin, cMax);
    populateSMEmpty(sm, cMin, cMax);
    for (int c = cMin; c <= cMax; c++){
        assert(sm.search(c) == c);
    }
    assert(sm.size() == cMax - cMin + 1);

    for (int c = cMin-100; c <= cMax+100; c++){
        sm.remove(c);
        assert(sm.search(c) == NULL_TVALUE);
    }
    assert(sm.size() == 0);
    assert(sm.isEmpty());
}


void testAllExtended() {
    testCreate();
    testAdd();
    testSearch();
    testRemove();
    testQuantity();
}
