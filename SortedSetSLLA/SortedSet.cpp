#include "SortedSet.h"

SortedSet::SortedSet(Relation r) {
    //TODO - Implementation

    currentSize = 0;
    relation = r;
    capacity = 99999;
    nodes = new TComp[capacity];
    next = new int[capacity];

    for (int i = 0; i < capacity; i++) {
        next[i] = i + 1;
    }
    head = -1;
    next[capacity - 1] = -1;
    firstEmpty = 0;

}


bool SortedSet::add(TComp elem) {
    //TODO - Implementation
    //if(firstEmpty == -1) resizeUp()
    int newNode = firstEmpty;
    firstEmpty = next[firstEmpty];
    nodes[newNode] = elem;
    next[newNode] = -1;
    if (isEmpty()) {
        head = newNode;
        currentSize++;
        return true;
    }
    if (search(elem))
        return false;
    int current = head;
    int previous = -1;
    while (current != -1 && relation(nodes[current], elem)) {
        previous = current;
        current = next[current];
    }// previous,el,current
    if(previous == -1){
        next[newNode] = head;
        head = newNode;
    } else{
        next[previous] = newNode;
        next[newNode] = current;
    }
    currentSize++;
    return true;

}


bool SortedSet::remove(TComp elem) {
    //TODO - Implementation
    if (isEmpty())
        return false;
    if (!search(elem))
        return false;
    int current = head;
    int prev = -1;
    while (current != -1 && nodes[current] != elem) {
        prev = current;
        current = next[current];
    }
    if(current == head){
        head = next[head];
    } else{
        next[prev] = next[current];
    }
    next[current] = firstEmpty;
    firstEmpty = current;
    currentSize--;
    return true;
}


bool SortedSet::search(TComp elem) const {
    //TODO - Implementation
    int current = head;
    while (current != -1) {
        if (nodes[current] == elem)
            return true;
        current = next[current];
    }
    return false;
}


int SortedSet::size() const {
    //TODO - Implementation
    return currentSize;
}


bool SortedSet::isEmpty() const {
    //TODO - Implementation
    if (currentSize == 0)
        return true;
    return false;
}


SortedSet::~SortedSet() {
    //TODO - Implementation
    delete[] next;
    delete[] nodes;

}


