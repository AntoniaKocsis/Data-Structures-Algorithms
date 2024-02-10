#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

#include <exception>

SortedIndexedList::SortedIndexedList(Relation r) {
    /** @Complexity θ(1) **/
    //TODO - Implementation
    this->head = nullptr;
    this->relation = r;
}

int SortedIndexedList::size() const {
    //TODO - Implementation
    /** @Complexity
    * Best case Ω(1)
    * Average case θ(n)
    * Worst case O(n)
    * **/
    int size = 0;
    Node *current = head;
    while (current != nullptr) {
        size++;
        current = current->next;
    }
    return size;
}

bool SortedIndexedList::isEmpty() const {
    //TODO - Implementation
    /** @Complexity θ(1) **/
    if (head == nullptr)
        return true;
    return false;
}

TComp SortedIndexedList::getElement(int i) const {
    //TODO - Implementation
    /** @Complexity
    * Best case Ω(1)
    * Average case θ(n)
    * Worst case O(n)
    * **/
    if (i < 0 || i >= size())
        throw invalid_argument("");
    int index = 0;
    Node *current = head;
    while (current != nullptr && index < i) {
        index++;
        current = current->next;

    }
    return current->value;

}

TComp SortedIndexedList::remove(int i) {
    //TODO - Implementation
    /** @Complexity
    * Best case Ω(1)
    * Average case θ(n)
    * Worst case O(n)
    * **/
    if (head == nullptr || i >= size() || i < 0)
        throw invalid_argument("");
    TComp e;
    Node *current = head;
    Node *previous = nullptr;
    if(i == 0){
        TComp value = head->value;
        head = head->next;
        delete current;
        return value;

    }
    int index = 0;

    while (current != nullptr && index != i) {
        previous = current;
        current = current->next;
        index++;
    }
    e = current->value;
    previous->next = current->next;
    delete current;
    return e;
}

int SortedIndexedList::search(TComp e) const {
    //TODO - Implementation
    /** @Complexity
    * Best case Ω(1)
    * Average case θ(n)
    * Worst case O(n)
    * **/
    int index = 0;
    Node *current = head;
    while (current != nullptr && current->value != e) {
        current = current->next;
        index++;
    }
    if (current == nullptr)
        return -1;
    return index;
}

void SortedIndexedList::add(TComp e) {
    //TODO - Implementation
    /** @Complexity
    * Best case Ω(1)
    * Average case θ(n)
    * Worst case O(n)
    * **/
    Node *newNode = new Node;
    newNode->value = e;
    newNode->next = nullptr;
    if (head == nullptr)
        head = newNode;
    else if (!relation(head->value, e)) {
        newNode->next = head;
        head = newNode;

    } else {
        Node *current = head;
        Node *previous = nullptr;
        while (current != nullptr && relation(current->value, newNode->value)) {
            previous = current;
            current = current->next;
        }
        newNode->next = current;
        previous->next = newNode;
    }
}

ListIterator SortedIndexedList::iterator() {
    /** @Complexity θ(1) **/
    return ListIterator(*this);
}

//destructor
SortedIndexedList::~SortedIndexedList() {
    //TODO - Implementation
    /** @Complexity
    * Best case Ω(1)
    * Average case θ(n)
    * Worst case O(n)
    * **/
    Node *current = head;
    Node *next = nullptr;
    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
}
