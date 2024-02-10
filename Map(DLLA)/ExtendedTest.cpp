#include "ExtendedTest.h"
#include "Map.h"

#include <assert.h>
#include <iostream>

using namespace std;

void testCreate() {
    cout << "Test create" << endl;
    Map m;
    assert(m.size() == 0);
    assert(m.isEmpty() == true);

    for (int i = -10; i < 10; i++) {
        assert(m.search(i) == NULL_TVALUE);
    }
    for (int i = -10; i < 10; i++) {
        assert(m.search(i) == NULL_TVALUE);
    }
}


void testAdd() {
    cout << "Test add" << endl;
    Map m;
    for (int i = 0; i < 10; i++) {
        assert(m.add(i, i) == NULL_TVALUE);
    }
    assert(m.isEmpty() == false);
    assert(m.size() == 10);
    for (int i = -10; i < 0; i++) {
        assert(m.add(i, i) == NULL_TVALUE);
    }
    for (int i = 0; i < 10; i++) {
        assert(m.add(i, i) == i);
    }
    for (int i = 10; i < 20; i++) {
        assert(m.add(i, i) == NULL_TVALUE);
    }
    assert(m.isEmpty() == false);
    assert(m.size() == 30);
    for (int i = -100; i < 100; i++) {
        m.add(i, i);
    }
    assert(m.isEmpty() == false);
    assert(m.size() == 200);
    for (int i = -200; i < 200; i++) {
        if (i < -100) {
            assert(m.search(i) == NULL_TVALUE);
        }
        else if (i < 0) {
            assert(m.search(i) == i);
        }
        else if (i < 100) {
            assert(m.search(i) == i);
        }
        else {
            assert(m.search(i) == NULL_TVALUE);
        }
    }
    for (int i = 10000; i > -10000; i--) {
        m.add(i, i);
    }
    assert(m.size() == 20000);
}


void testRemove() {
    cout << "Test remove" << endl;
    Map m;

    for (int i = -100; i < 100; i++) {
        assert(m.remove(i) == NULL_TVALUE);
    }
    assert(m.size() == 0);
    for (int i = -100; i < 100; i = i + 2) {
        assert(m.add(i, i) == NULL_TVALUE);
    }
    for (int i = -100; i < 100; i++) {
        if (i % 2 == 0) {
            assert(m.remove(i) == i);
        }
        else {
            assert(m.remove(i) == NULL_TVALUE);
        }
    }
    assert(m.size() == 0);

    for (int i = -100; i <= 100; i = i + 2) {
        assert(m.add(i, i) == NULL_TVALUE);
    }
    for (int i = 100; i > -100; i--) {
        if (i % 2 == 0) {
            assert(m.remove(i) == i);
        }
        else {
            assert(m.remove(i) == NULL_TVALUE);
        }
    }

    assert(m.size() == 1);

    m.remove(-100);
    assert(m.size() == 0);

    for (int i = -100; i < 100; i++) {
        assert(m.add(i, 0) == NULL_TVALUE);
        assert(m.add(i, 1) == 0);
        assert(m.add(i, 2) == 1);
        assert(m.add(i, 3) == 2);
        assert(m.add(i, 4) == 3);
    }
    assert(m.size() == 200);
    for (int i = -200; i < 200; i++) {
        if (i < -100 || i >= 100) {
            assert(m.remove(i) == NULL_TVALUE);
        }
        else {
            assert(m.remove(i) == 4);
            assert(m.remove(i) == NULL_TVALUE);
        }
    }
    assert(m.size() == 0);

}

void testQuantity() {
    Map m;
    cout << "Test quantity" << endl;
    for (int j = 0; j < 30000; j = j + 1) {
        assert(m.add(j, j) == NULL_TVALUE);
    }
    for (int i = 10; i >= 1; i--) {
        for (int j = 0; j < 30000; j = j + i) {
            assert(m.add(j, j) == j);
        }
    }
    assert(m.size() == 30000);

    for (int j = 30000 - 1; j >= 0; j--) {
        assert(m.remove(j) == j);
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 40000; j >= -4000; j--) {
            assert(m.remove(j) == NULL_TVALUE);
        }
    }
    assert(m.size() == 0);
}

void testAllExtended() {
    testCreate();
    testAdd();
    testRemove();
    testQuantity();
}




