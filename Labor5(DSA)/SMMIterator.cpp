#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
    /**Complexity:
     * Best: θ(1)
     * Average: θ(log(n))
     * Worst: θ(n)**/
    currentElem = map.root;
    while (currentElem!= nullptr && currentElem->left != nullptr) {
        currentElem = currentElem->left;
    }
}

void SMMIterator::first(){
    /**Complexity:
    * Best: θ(1)
    * Average: θ(log(n))
    * Worst: θ(n)**/
    currentElem = map.root;
    while (currentElem != nullptr && currentElem->left != nullptr) {
        currentElem = currentElem->left;
    }
}

void SMMIterator::next(){
    /**Complexity:
    * Best: θ(log(n))
    * Average: θ(log(n))
    * Worst: θ(n)**/

    if (currentElem == nullptr)
        throw invalid_argument("");
    if (currentElem->right != nullptr) {
        currentElem = currentElem->right;
        while (currentElem->left != nullptr) {
            currentElem = currentElem->left;
        }
    } else {
        Node *previous = currentElem->parent;
        while (previous != nullptr && previous->left != currentElem) {
            currentElem = previous;
            previous = currentElem->parent;
        }
        currentElem = previous;
    }
}

bool SMMIterator::valid() const{
    /** Complexity: θ(1)**/
    if (currentElem != nullptr)
        return true;
	return false;
}
TElem SMMIterator::getCurrent() const{
    /** Complexity: θ(1)**/
    if (!valid())
        throw invalid_argument("");
    TElem elem;
    elem.first = currentElem->value.first;
    elem.second = currentElem->value.second;
    return elem;
}


