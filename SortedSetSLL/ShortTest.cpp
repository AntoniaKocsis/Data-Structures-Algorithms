#include "ShortTest.h"
#include "SortedSet.h"
#include <assert.h>

bool r2(TComp e1, TComp e2) {
    if (e1 <= e2) {
        return true;
    }
    else {
        return false;
    }
}


void testAll() {

    SortedSet s1(r2);
    assert(s1.add(5) == true);
    assert(s1.add(1) == true);
    assert(s1.add(10) == true);
    SortedSet s(r2);
    assert(s.isEmpty() == true);
    assert(s.size() == 0);
    assert(s.add(5) == true);
    assert(s.add(1) == true);
    assert(s.add(10) == true);
    assert(s.add(7) == true);
    assert(s.add(1) == false);
    assert(s.add(10) == false);
    assert(s.add(-3) == true);
    assert(s.size() == 5);
    assert(s.search(10) == true);
    assert(s.search(16) == false);
    assert(s.remove(1) == true);
    assert(s.remove(6) == false);
    assert(s.size() == 4);


}

