#include "SortedSet.h"

SortedSet::SortedSet(Relation r) {
    //TODO - Implementation
    head = nullptr;
    currentSize = 0;
    relation = r;

}


bool SortedSet::add(TComp elem) {
    //TODO - Implementation
    Node *newNode = new Node;
    newNode->info = elem;
    newNode->next = nullptr;
    if (isEmpty()) {
        head = newNode;
        currentSize++;
        return true;
    }
    if (search(elem))
        return false;
    Node *current = head;
    Node *previous = nullptr;
    while (current != nullptr && relation(current->info, elem)) {
        previous = current;
        current = current->next;
    }// current arata spre pozitia urmatoare,previous arata spre ultima poz care verifica
    if(previous == nullptr){
        newNode->next = head;
        head = newNode;
    }
    else{
        previous->next = newNode;
        newNode->next = current;
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
    Node *current = head;
    Node *prevN = nullptr;
    while (current != nullptr && current->info != elem) {
        prevN = current;
        current = current->next;
    }
    // current => elem
    if (prevN == nullptr) {
        head = head->next;
    } else {
        prevN->next = current->next;
    }
    delete current;
    currentSize--;
    return true;
}


bool SortedSet::search(TComp elem) const {
    //TODO - Implementation
    Node *current = head;
    while (current != nullptr && current->info != elem)
        current = current->next;
    if (current == nullptr)
        return false;
    return true;
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
    Node *current = head;
    Node *next = nullptr;
    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
}


