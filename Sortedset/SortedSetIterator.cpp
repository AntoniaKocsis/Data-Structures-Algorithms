#include "SortedSetIterator.h"
#include <stdexcept>

using namespace std;

SortedSetIterator::SortedSetIterator(const SortedSet &m) : multime(m) {
    //TODO - Implementation
    // Complexity: Best case Ω(1) , Average case θ(1), Worst case O(1)
    if (!m.isEmpty()) {
        iterator = 0;
    }
}


void SortedSetIterator::first() {
    // Complexity: Best case Ω(1) , Average case θ(1), Worst case O(1)
    //TODO - Implementation
    if (!multime.isEmpty())
        iterator = 0;
}


void SortedSetIterator::next() {
    // Complexity: Best case Ω(1) , Average case θ(1), Worst case O(1)
    //TODO - Implementation
    if (valid())
        iterator++;
    else {
        throw std::invalid_argument("");
    }
}


TElem SortedSetIterator::getCurrent() {
    // Complexity: Best case Ω(1) , Average case θ(1), Worst case O(1)
    //TODO - Implementation
    if (multime.isEmpty() || iterator >= multime.currentSize)
        throw std::invalid_argument("");

    return multime.dynamicArray[iterator];
}

bool SortedSetIterator::valid() const {
    // Complexity: Best case Ω(1) , Average case θ(1), Worst case O(1)
    //TODO - Implementation
    if (!multime.isEmpty() && iterator < multime.currentSize)
        return true;
    return false;
}

