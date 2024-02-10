#include "Set.h"
#include <iostream>
#include <limits.h>

Set::Set() {
    currentSize = 0;
    capacity = 999999;
    dynamicArray = new dllaNode[capacity];
    head = -1;
    tail = -1;
    for (int i = 0; i < capacity; i++) {
        dynamicArray[i].previous = -1;
        dynamicArray[i].next = i + 1;
    }
    dynamicArray[capacity - 1].next = -1;
    firstEmpty = 0;

}

int Set::allocate() {
    int position;
    position = firstEmpty;
    if (position != -1) {
        firstEmpty = dynamicArray[firstEmpty].next;
        if (firstEmpty != -1) {
            dynamicArray[firstEmpty].previous = -1;
        }
        dynamicArray[position].next = -1;
        dynamicArray[position].previous = -1;
    }
    return position;
}

void Set::free(int position) {
    dynamicArray[position].next = firstEmpty;
    dynamicArray[position].previous = -1;
    if (firstEmpty != -1)
        dynamicArray[firstEmpty].previous = position;
    firstEmpty = position;
}

bool Set::add(TElem elem) {
    if (isEmpty()) {
        int newNode = allocate();
        dynamicArray[newNode].info = elem;
        head = newNode;
        tail = newNode;
        currentSize++;
        return true;
    }
    if (search(elem))
        return false;
    int newNode = allocate();
    dynamicArray[newNode].info = elem;
    dynamicArray[newNode].next = -1;
    dynamicArray[newNode].previous = tail;
    dynamicArray[tail].next = newNode;
    tail = newNode;
    currentSize++;
    return true;

}


bool Set::remove(TElem elem) {
    if (isEmpty())
        return false;
    if (!search(elem))
        return false;
    int current = head;
    while (current != -1 && dynamicArray[current].info != elem) {
        current = dynamicArray[current].next;
    }
    // pe pozitia current se afla elementul cautat

    int prevN = dynamicArray[current].previous;
    int nextN = dynamicArray[current].next;
    if(prevN == -1){
        if(nextN == -1)
        {
            head = -1;
            tail = -1;
        }
        else{
            head = nextN;
        }
    }
    if(nextN == -1){
        tail = -1;
    }
    else{
        dynamicArray[prevN].next = nextN;
        dynamicArray[nextN].previous = prevN;
    }
    currentSize--;
    free(current);
    return true;
}

bool Set::search(TElem elem) const {
    int current = head;
    while (current != -1) {
        if (dynamicArray[current].info == elem)
            return true;
        current = dynamicArray[current].next;
    }
    return false;
}


int Set::size() const {
    return currentSize;
}


bool Set::isEmpty() const {
    if (currentSize == 0)
        return true;
    return false;
}


Set::~Set() {
    delete[] dynamicArray;
}


