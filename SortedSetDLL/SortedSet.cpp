#include "SortedSet.h"

SortedSet::SortedSet(Relation r) {
    //TODO - Implementation
    head = nullptr;
    tail = nullptr;
    currentSize = 0;
    relation = r;

}


bool SortedSet::add(TComp elem) {
    //TODO - Implementation
    Node *newNode = new Node;
    newNode->info = elem;
    newNode->next = nullptr;
    newNode->previous = nullptr;
    if (isEmpty()) {
        head = newNode;
        tail = newNode;
        currentSize++;
        return true;
    }
    if (search(elem))
        return false;
    if (!relation(head->info, elem)) {
        head->previous = newNode;
        newNode->next = head;
        head = newNode;
        currentSize++;
        return true;
    } else if (!relation(elem, tail->info)) {
        tail->next = newNode;
        newNode->previous = tail;
        tail = newNode;
        currentSize++;
        return true;
    } else {
        Node *current = head;
        while (current != nullptr && relation(current->info, elem)) {
            current = current->next;
        }
        newNode->next = current;
        newNode->previous = current->previous;
        current->previous->next = newNode;
        current->previous = newNode;
        currentSize++;
        return true;
    }

}


bool SortedSet::remove(TComp elem) {
    //TODO - Implementation
    if (isEmpty())
        return false;
    if (!search(elem))
        return false;
    Node *current = head;
    while (current != nullptr) {
        if (current->info == elem) {
            if (current->previous == nullptr) {
                if(current->next == nullptr){
                    head = nullptr;
                    tail = nullptr;
                } else{
                    head = head->next;
                    head->previous = nullptr;
                }
            }else if(current->next == nullptr){
                tail = tail->previous;
                tail->next = nullptr;
            } else{
                current->next->previous = current->previous;
                current->previous->next = current->next;
            }
            delete current;
            currentSize--;
            return true;
        }

        current = current->next;
    }
    return false;
}


bool SortedSet::search(TComp elem) const {
    //TODO - Implementation
    Node *current = head;
    while (current != nullptr) {
        if (current->info == elem)
            return true;
        current = current->next;
    }
    return false;
}


int SortedSet::size() const {
    //TODO - Implementation
    return currentSize;
}


bool SortedSet::isEmpty() const {
    //TODO - Implementation
    if (head == nullptr)
        return true;
    return false;
}


SortedSet::~SortedSet() {
    //TODO - Implementation
    Node *current = head;
    Node *next = nullptr;
    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
}


