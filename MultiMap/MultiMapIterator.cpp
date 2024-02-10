#include "MultiMapIterator.h"
#include "MultiMap.h"
#include <exception>
#include <iostream>

MultiMapIterator::MultiMapIterator(const MultiMap &c) : col(c) {
    //TODO - Implementation
    /** @Complexity θ(1) **/
    iterator = col.head;

}

TElem MultiMapIterator::getCurrent() const {
    //TODO - Implementation
    /** @Complexity θ(1) **/
    if (!valid())
        throw invalid_argument("");
    TElem e = iterator->pair;
    return e;
}

bool MultiMapIterator::valid() const {
    //TODO - Implementation
    /** @Complexity θ(1) **/
    if (iterator != nullptr)
        return true;
    return false;
}

void MultiMapIterator::next() {
    //TODO - Implementation
    /** @Complexity θ(1) **/
    if (iterator == nullptr)
        throw invalid_argument("");
    iterator = iterator->next;
}

void MultiMapIterator::first() {
    //TODO - Implementation
    /** @Complexity θ(1) **/
    if (col.head != nullptr)
        iterator = col.head;
}

