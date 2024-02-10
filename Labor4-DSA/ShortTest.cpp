#include <assert.h>

#include "SortedMultiMap.h"
#include "SMMIterator.h"
#include <exception>
#include <vector>
#include <iostream>

using namespace std;

bool des(TKey c1, TKey c2) {
    if (c1 >= c2) {
        return true;
    } else {
        return false;
    }
}

bool relation1(TKey cheie1, TKey cheie2) {
    if (cheie1 <= cheie2) {
        return true;
    } else {
        return false;
    }
}

void testAll() {
    SortedMultiMap smm = SortedMultiMap(relation1);
    assert(smm.size() == 0);
    assert(smm.isEmpty());
    smm.add(1, 2);
    smm.add(1, 3);
    assert(smm.size() == 2);
    assert(!smm.isEmpty());
    vector<TValue> v = smm.search(1);
    assert(v.size() == 2);
    v = smm.search(3);
    assert(v.size() == 0);
    SMMIterator it = smm.iterator();
    it.first();
    assert(it.valid() == true);

    while (it.valid()) {
        TElem e = it.getCurrent();
        it.next();
    }
   assert(smm.remove(1, 2) == true);
    assert(smm.remove(1, 3) == true);
    assert(smm.remove(2, 1) == false);
    assert(smm.isEmpty());
    SortedMultiMap smm1(relation1);
    SortedMultiMap smm2(relation1);


}

