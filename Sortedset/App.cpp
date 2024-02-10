//#include "ShortTest.h"
//#include "ExtendedTest.h"
#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <iostream>
#include <cassert>
using namespace std;

bool r2(TComp e1, TComp e2) {
    if (e1 <= e2) {
        return true;
    } else {
        return false;
    }
}

int main() {
//    testAll();
//    testAllExtended();
    SortedSet set(r2);
    set.add(2);
    set.add(5);
    set.add(7);
    SortedSet set2(r2);
    set2.add(6);
    set2.add(3);
    set.merge(set2);
    assert(set.findPosition(2) == 0);
    assert(set.findPosition(3) == 1);
    assert(set.findPosition(5) == 2);
//    cout << "Test end" << endl;
//    system("pause");
}