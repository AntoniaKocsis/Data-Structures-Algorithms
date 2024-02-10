#include "ListIterator.h"
#include "IteratedList.h"
#include <exception>
#include <iostream>
using namespace std;
ListIterator::ListIterator(const IteratedList& list) : list(list) {
	//TODO - Implementation
    current = list.head;
}

void ListIterator::first() {
	//TODO - Implementation
    current = list.head;
}

void ListIterator::next() {
	//TODO - Implementation
    if(!valid())
        throw invalid_argument("");
    current = current->next;

}

bool ListIterator::valid() const {
	//TODO - Implementation
    if(current != nullptr)
        return true;
    return false;

}

TElem ListIterator::getCurrent() const {
	//TODO - Implementation
    return current->info;

}



