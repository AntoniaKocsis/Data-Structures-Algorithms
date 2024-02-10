#include "SortedSet.h"
#include <assert.h>
#include <exception>
#include "ExtendedTest.h"
#include <iostream>

using namespace std;

bool rGreater(TComp e1, TComp e2) {
    if (e1 > e2) {
        return true;
    }
    else {
        return false;
    }
}

bool rLessEqual(TComp e1, TComp e2) {
    if (e1 <= e2) {
        return true;
    }
    else {
        return false;
    }
}

void testCreate(Relation r) {
    cout << "Test create" << endl;
    SortedSet s(r);
    assert(s.size() == 0);
    assert(s.isEmpty() == true);

    for (int i = -10; i < 10; i++) {
        assert(s.search(i) == false);
    }
    for (int i = -10; i < 10; i++) {
        assert(s.remove(i) == false);
    }
}


void testAdd() {
    cout << "Test add" << endl;
    int vverif[10];
    int iverif;

    SortedSet s2(rGreater);
    for (int i = 0; i <= 3; i++) {
        s2.add(i);
    }
    for (int i = 5; i > 3; i--) {
        s2.add(i);
    }
    assert(s2.isEmpty() == false);
    assert(s2.size() == 6);

    SortedSet s(rLessEqual);
    for (int i = 0; i <= 3; i++) {
        s.add(i);
    }
    for (int i = 5; i > 3; i--) {
        s.add(i);
    }
    assert(s.isEmpty() == false);
    assert(s.size() == 6);

    for (int i = -10; i < 20; i++) {
        s.add(i);
    }
    assert(s.isEmpty() == false);
    assert(s.size() == 30);
    for (int i = 100; i > -100; i--) {
        s.add(i);
    }

    assert(s.isEmpty() == false);
    assert(s.size() == 200);
    for (int i = -200; i < 200; i++) {
        if (i <= -100) {
            assert(s.search(i) == false);
        }
        else if (i < 0) {
            assert(s.search(i) == true);
        }
        else if (i <= 100) {
            assert(s.search(i) == true);
        }
        else {
            assert(s.search(i) == false);
        }
    }
    for (int i = 10000; i > -10000; i--) {
        s.add(i);
    }
    assert(s.size() == 20000);
}


void testRemove(Relation r) {
    cout << "Test remove" << endl;
    SortedSet s(r);
    for (int i = -100; i < 100; i++) {
        assert(s.remove(i) == false);
    }
    assert(s.size() == 0);

    for (int i = -100; i < 100; i = i + 2) {
        s.add(i);
    }
    for (int i = -100; i < 100; i++) {
        if (i % 2 == 0) {
            assert(s.remove(i) == true);
        }
        else {
            assert(s.remove(i) == false);
        }
    }
    assert(s.size() == 0);

    for (int i = -100; i <= 100; i = i + 2) {
        s.add(i);
    }

    for (int i = 100; i > -100; i--) {
        if (i % 2 == 0) {
            assert(s.remove(i) == true);
        }
        else {
            assert(s.remove(i) == false);
        }
    }
    assert(s.size() == 1);

    s.remove(-100);
    assert(s.size() == 0);

    for (int i = -100; i < 100; i++) {
        s.add(i);
        s.add(i);
        s.add(i);
        s.add(i);
        s.add(i);
    }

    assert(s.size() == 200);
    for (int i = -200; i < 200; i++) {
        if (i < -100 || i >= 100) {
            assert(s.remove(i) == false);
        }
        else {
            assert(s.remove(i) == true);
            assert(s.remove(i) == false);
        }

    }
    assert(s.size() == 0);

}


void testQuantity(Relation r) {
    cout << "Test quantity" << endl;
    SortedSet s(r);
    for (int i = 10; i >= 1; i--) {
        for (int j = -3000; j < 3000; j = j + i) {
            s.add(j);
        }
    }
    assert(s.size() == 6000);
    for (int i = 0; i < 3; i++) {
        for (int j = 40000; j >= -40000; j--) {
            s.remove(j);
        }
    }
    assert(s.size() == 0);
}


void testAllExtended() {

    testCreate(rLessEqual);
    testAdd();
    testRemove(rLessEqual);
    testRemove(rGreater);
    testQuantity(rLessEqual);
    testQuantity(rGreater);

}

