#include <assert.h>
#include <exception>

#include "ShortTest.h"
#include "IndexedList.h"
#include <iostream>
using namespace std;



void testAll() {
    IndexedList list = IndexedList();
    assert(list.isEmpty());
    list.addToEnd(1);
    assert(list.size() == 1);
    assert(list.search(1) == 0);
    list.addToPosition(0,2);
    assert(list.search(2) == 0);
    assert(list.size() == 2);
    assert(list.search(1) == 1);
    assert(list.search(2) == 0);
    assert(list.setElement(1,3) == 1);
    assert(list.getElement(1) == 3);
    assert(list.remove(0) == 2);
    assert(list.size() == 1);
}
