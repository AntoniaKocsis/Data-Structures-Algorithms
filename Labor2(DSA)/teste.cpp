//#include <iostream>
//#include "SortedIndexedList.h"
//#include "ListIterator.h"
//#include <cassert>
//#include <vector>
//#include <assert.h>
//#include <exception>
//#include <cstdlib>
//using namespace std;
//bool asc(TComp c1, TComp c2) {
//    if (c1 <= c2) {
//        return true;
//    } else {
//        return false;
//    }
//}
//
////order relation - descending
//bool desc(TComp c1, TComp c2) {
//    if (c1 >= c2) {
//        return true;
//    } else {
//        return false;
//    }
//}
//
//void testIteratorSteps(SortedIndexedList& list, Relation r) {
//    int count = 0;
//    ListIterator li = list.iterator();
//    TComp prev = li.getCurrent();
//    if (li.valid()) {
//        count++;
//        li.next();
//    }
//    while (li.valid()) {
//        TComp current = li.getCurrent();
//        assert(r(prev, current));
//        count++;
//        li.next();
//        prev = current;
//    }
//    assert(count == list.size());
//}
//
//void testCreate() {
//    cout << "Test create" << endl;
//    SortedIndexedList list = SortedIndexedList(asc);
//    assert(list.size() == 0);
//    assert(list.isEmpty());
//
//    ListIterator it = list.iterator();
//    assert(!it.valid());
//    it.first();
//
//    for (int i = 0; i < 10; i++) {
//        assert(!it.valid());
//        assert(list.search(i) == -1);
//        try {
//            assert(list.getElement(i));
//            assert(false);
//        } catch (exception&) {
//            assert(true);
//        }
//        try {
//            assert(list.remove(i));
//            assert(false);
//        } catch (exception&) {
//            assert(true);
//        }
//        try {
//            it.next();
//            assert(false);
//        }
//        catch (exception&) {
//            assert(true);
//        }
//    }
//}
//
////generate a vector with values between cMin and cMax so that
////1) no value that is >=cMin and <=cMax which is a multiple of s is not included
////2) values v, v>=cMin and v<=cMax which are a multiple of m (but not of s) are included c/m + 1 times
////3) values >=cMin and <=cMax are in random order
//vector<int> random(int cMin, int cMax, int s, int m) {
//    vector<int> v;
//    for (int c = cMin; c <= cMax; c++) {
//        if (c % s != 0) {
//            v.push_back(c);
//            if (c % m == 0) {
//                for (int j = 0; j < c / m; j++) {
//                    v.push_back(c);
//                }
//            }
//        }
//    }
//    int n = v.size();
//    for (int i = 0; i < n - 1; i++) {
//        int j = i + rand() % (n - i);
//        swap(v[i], v[j]);
//    }
//    return v;
//}
//
////generate a vector containing values >=cMin and <=cMax, each included one time, in random order
//vector<int> random(int cMin, int cMax) {
//    vector<int> v;
//    for (int c = cMin; c <= cMax; c++) {
//        v.push_back(c);
//    }
//
//    int n = v.size();
//    for (int i = 0; i < n - 1; i++) {
//        int j = i + rand() % (n - i);
//        swap(v[i], v[j]);
//    }
//    return v;
//}
//
////populate the sorted list with values >=cMin and <=cMax a.i.:
////1) no value that is >=cMin and <=cMax which is a multiple of s is not included
////2) values v, v>=cMin and v<=cMax which are a multiple of m (but not of s) are included c/m + 1 times
////3) values >=cMin and <=cMax are in random order
//int populate(SortedIndexedList& list, int cMin, int cMax, int s, int m) {
//    vector<int> v = random(cMin, cMax, s, m);
//    int n = v.size();
//    for (int i = 0; i < n; i++) {
//        list.add(v[i]);
//    }
//    return n;
//}
//
////populate the sorted list with values >=cMin and <=cMax, each included one time, in random order
//void populate(SortedIndexedList& list, int cMin, int cMax) {
//    vector<int> v = random(cMin, cMax);
//    int n = v.size();
//    for (int i = 0; i < n; i++) {
//        list.add(v[i]);
//    }
//}
//
//void testAddAndSearch(Relation r) {
//    cout << "Test add and search" << endl;
//    SortedIndexedList list = SortedIndexedList(r);
//    int vMin = 10;
//    int vMax = 30;
//    int s = 5;
//    int m = 3;
//    int n = populate(list, vMin, vMax, s, m);
//    assert(!list.isEmpty());
//    assert(list.size() == n);
//
//    //we can't find values outside the interval or on invalid positions
//    int d = 30;
//    for (int i = 1; i <= d; i++) {
//        assert(list.search(vMin - i) == -1);
//        assert(list.search(vMax + i) == -1);
//        try{
//            list.getElement(n-1+i);
//            list.getElement(-d);
//            assert(false);
//        } catch (exception&) {
//            assert(true);
//        }
//    }
//
//    //check the relation order
//    ListIterator it = list.iterator();
//    it.first();
//    assert(it.valid());
//    TComp prev = it.getCurrent();
//    it.next();
//    while (it.valid()) {
//        TComp current = it.getCurrent();
//        assert(r(prev, current));
//        prev = current;
//        it.next();
//    }
//    testIteratorSteps(list, r);
//
//    //check if added values can be found
//    for (int v = vMin; v <= vMax; v++) {
//        int p = list.search(v);
//        //we can't find values which are a multiple of s
//        assert((p != -1) == (v % s != 0));
//        //values which are a multiple of m can be found exactly v/m+1 times
//        if (p != -1 && v%m == 0){
//            for (int i=0; i<=v/m; i++){
//                try{
//                    assert(list.remove(p) == v);
//                } catch (exception&) {
//                    assert(false);
//                }
//            }
//            assert(list.search(v) == -1);
//        }
//    }
//}
//int main(){
//    testCreate();
//    testAddAndSearch(asc);
//    testAddAndSearch(desc);
//    return 0;
//}