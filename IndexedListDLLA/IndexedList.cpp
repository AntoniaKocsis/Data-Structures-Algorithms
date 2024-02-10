#include <exception>

#include "IndexedList.h"
#include <iostream>

using namespace std;

IndexedList::IndexedList() {
    //TODO - Implementation
    currentSize = 0;
    capacity = 999999;
    dynamicArray = new Node[capacity];
    firstEmpty = 0;
    head = -1;
    tail = -1;
    for (int i = 0; i < capacity; i++) {
        dynamicArray[i].next = i + 1;
        dynamicArray[i].previous = -1;
    }
    dynamicArray[capacity - 1].next = -1;

}

int IndexedList::size() const {
    //TODO - Implementation
    return currentSize;
}


bool IndexedList::isEmpty() const {
    //TODO - Implementation
    if (currentSize == 0)
        return true;
    return false;
}

TElem IndexedList::getElement(int pos) const {
    //TODO - Implementation
    if (pos < 0 || isEmpty() || pos >= currentSize)
        throw invalid_argument("");
    int current = head;
    for (int i = 0; i < pos; i++)
        current = dynamicArray[current].next;
    return dynamicArray[current].info;

}

TElem IndexedList::setElement(int pos, TElem e) {
    //TODO - Implementation
    if (pos < 0 || pos >= currentSize)
        throw invalid_argument("");
    int current = head;
    for (int i = 0; i < pos; i++)
        current = dynamicArray[current].next;
    TElem value = dynamicArray[current].info;
    dynamicArray[current].info = e;
    return value;


}

int IndexedList::allocate() {
    int position = firstEmpty;
    if (position != -1) {
        firstEmpty = dynamicArray[firstEmpty].next;
        if (firstEmpty != -1)
            dynamicArray[firstEmpty].previous = -1;
        dynamicArray[position].next = -1;
        dynamicArray[position].previous = -1;
    }
    return position;
}

void IndexedList::addToEnd(TElem e) {
    //TODO - Implementation
    int newNode = allocate();
    dynamicArray[newNode].info = e;
    if (isEmpty()) {
        head = newNode;
        tail = newNode;
        currentSize++;
        return;
    }
    dynamicArray[tail].next = newNode;
    dynamicArray[newNode].previous = tail;
    tail = newNode;
    currentSize++;


}

void IndexedList::addToPosition(int pos, TElem e) {
    if (pos < 0 || pos >= currentSize)
        throw invalid_argument("");
    int newNode = allocate();
    dynamicArray[newNode].info = e;
    if (isEmpty()) {
        head = newNode;
        tail = newNode;
        currentSize++;
        return;
    }
    int index = 0;
    int current = head;
    while (current != -1) {
        if(index == pos){
            int prevN = dynamicArray[current].previous;
            int nextN = dynamicArray[current].next;
            if(prevN == -1){
                dynamicArray[newNode].next = head;
                dynamicArray[head].previous = newNode;
                head = newNode;
            }else if(nextN == -1){
                dynamicArray[newNode].previous = tail;
                dynamicArray[tail].next = newNode;
                tail = newNode;
            } else{
                dynamicArray[newNode].previous = prevN;
                dynamicArray[newNode].next = current;
                dynamicArray[prevN].next = newNode;
                dynamicArray[current].previous = newNode;
            }
            currentSize++;
            return;
        }
        current = dynamicArray[current].next;
        index++;
    }
}

TElem IndexedList::remove(int pos) {
    //TODO - Implementation
    if (pos < 0 || isEmpty() || pos >= currentSize)
        throw invalid_argument("");
    int index =0;
    int current = head;
    while(current != -1 && index!= pos){
        index++;
        current = dynamicArray[current].next;
    }
    TElem value;
    int prevN = dynamicArray[current].previous;
    int nextN = dynamicArray[current].next;
    if(prevN == -1){
        if(nextN == -1){
            head = -1;
            tail = -1;
        }
        head = nextN;
        dynamicArray[head].previous = -1;
    } else if(nextN == -1){
        tail = prevN;
        dynamicArray[tail].next = -1;
    } else{
        dynamicArray[prevN].next = nextN;
        dynamicArray[nextN].previous = prevN;
    }
    currentSize--;
    value = dynamicArray[current].info;
    dynamicArray[current].next = firstEmpty;
    firstEmpty = current;
    return value;

}

int IndexedList::search(TElem e) const {
    //TODO - Implementation
    if (isEmpty())
        return -1;
    int position = 0;
    int current = head;
    while (current != -1) {
        if (dynamicArray[current].info == e)
            return position;
        current = dynamicArray[current].next;
        position++;
    }
    return -1;

}


IndexedList::~IndexedList() {
    //TODO - Implementation
    delete[] dynamicArray;

}