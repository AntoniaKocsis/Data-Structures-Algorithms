#include <exception>

#include "IndexedList.h"
#include <iostream>

using namespace std;

IndexedList::IndexedList() {
    //TODO - Implementation
    head = nullptr;
    tail = nullptr;
    currentSize = 0;
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
    TElem value;
    if (pos == 0) {
        value = head->info;
        return value;
    }
    if (pos == currentSize - 1)
        return tail->info;
    int index = 0;
    Node *current = head;
    while (current != nullptr && index != pos) {
        index++;
        current = current->next;
    }
    return current->info;

}

TElem IndexedList::setElement(int pos, TElem e) {
    //TODO - Implementation
    if (pos < 0 || isEmpty() || pos >= currentSize)
        throw invalid_argument("");
    TElem value;
    if (pos == 0) {
        value = head->info;
        head->info = e;
        return value;
    }
    if (pos == currentSize - 1) {
        value = tail->info;
        tail->info = e;
        return value;
    }
    int index = 0;
    Node *current = head;
    while (current != nullptr && index != pos) {
        index++;
        current = current->next;
    }
    value = current->info;
    current->info = e;
    return value;


}

void IndexedList::addToEnd(TElem e) {
    //TODO - Implementation
    Node *newNode = new Node;
    newNode->next = nullptr;
    newNode->previous = nullptr;
    newNode->info = e;
    if (isEmpty()) {
        head = newNode;
        tail = newNode;
        currentSize++;
        return;
    }
    newNode->previous = tail;
    tail->next = newNode;
    tail = newNode;
    currentSize++;

}

void IndexedList::addToPosition(int pos, TElem e) {
    //TODO - Implementation
    if (pos < 0 || pos >= currentSize)
        throw invalid_argument("");
    Node *newNode = new Node;
    newNode->next = nullptr;
    newNode->previous = nullptr;
    newNode->info = e;
    if (isEmpty()) {
        head = newNode;
        tail = newNode;
        currentSize++;
        return;
    }
    Node *current = head;
    int index = 0;
    while (current != nullptr && index != pos) {
        current = current->next;
        index++;
    }
    if (current->previous == nullptr) {
        head->previous = newNode;
        newNode->next = head;
        head = newNode;
    } else if (current->next == nullptr) {
        tail->next = newNode;
        newNode->previous = tail;
        tail = newNode;

    }else {
        newNode->previous = current->previous;
        newNode->next = current;
        current->previous->next = newNode;
        current->previous = newNode;
    }
    currentSize++;


}

TElem IndexedList::remove(int pos) {
    //TODO - Implementation
    if (pos < 0 || pos >= currentSize || isEmpty())
        throw invalid_argument("");

    Node *current = head;
    int index = 0;
    TElem value;
    while (current != nullptr) {
        if (index == pos) {
            value = current->info;
            if (current->previous == nullptr) {
                if (current->next == nullptr) {
                    tail = nullptr;
                    head = nullptr;
                } else {
                    head = head->next;
                    head->previous = nullptr;
                }
            } else if (current->next == nullptr) {
                tail = tail->previous;
                tail->next = nullptr;
            } else {
                current->next->previous = current->previous;
                current->previous->next = current->next;
            }
            delete current;
            currentSize--;
            return value;
        }
        current = current->next;
        index++;
    }
}

int IndexedList::search(TElem e) const {
    //TODO - Implementation
    if (isEmpty())
        return false;
    Node *current = head;
    int position = 0;
    while (current != nullptr && current->info != e) {
        position++;
        current = current->next;
    }
    if (current == nullptr)
        return -1;
    return position;

}


IndexedList::~IndexedList() {
    //TODO - Implementation
    Node *current = head;
    Node *next = nullptr;
    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
}