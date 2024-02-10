#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

ListIterator::ListIterator(const SortedIndexedList &list) : list(list) {
    //TODO - Implementation
    /** @Complexity θ(1) **/
    this->index = list.head;
}

void ListIterator::first() {
    //TODO - Implementation
    /** @Complexity θ(1) **/
    if (list.head != nullptr)
        index = list.head;
}

void ListIterator::next() {
    //TODO - Implementation
    /** @Complexity θ(1) **/
    if (index == nullptr)
        throw invalid_argument("");
    index = index->next;
}

void ListIterator::previous() {
    /** @Complexity
    * Best case Ω(1)
    * Average case θ(n)
    * Worst case O(n)
    * **/
    if (index == nullptr )
        throw invalid_argument("");
    if (index == list.head)
        throw invalid_argument("");
    Node *previous = nullptr;
    Node *current = list.head;
    while (current != nullptr && current != index) {
        previous = current;
        current = current->next;
    }
    index = previous;

}

bool ListIterator::valid() const {
    //TODO - Implementation
    /** @Complexity θ(1) **/
    if (index != nullptr)
        return true;
    return false;
}

TComp ListIterator::getCurrent() const {
    //TODO - Implementation
    /** @Complexity θ(1) **/
    if (index == nullptr)
        throw invalid_argument("");
    TComp e = index->value;
    return e;
}


