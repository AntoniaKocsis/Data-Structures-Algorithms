
#include <exception>
#include "ListIterator.h"
#include "IteratedList.h"

IteratedList::IteratedList() {
    head = nullptr;
}

int IteratedList::size() const {
    int count = 0;
    ListIterator it = first();

    while (it.valid()) {
        count++;
        it.next();
    }
    return count;
}

bool IteratedList::isEmpty() const {
    if (head == nullptr)
        return true;
    return false;
}

ListIterator IteratedList::first() const {
    ListIterator it(*this);
    it.first();
    return it;
}

TElem IteratedList::getElement(ListIterator pos) const {
    // throws an exception if the position is not valid
    if (!pos.valid())
        throw std::exception();
    return pos.getCurrent();
}

TElem IteratedList::remove(ListIterator &pos) {
    // throws exception if the position is not valid
    if (!pos.valid())
        throw std::exception();

}

ListIterator IteratedList::search(TElem e) const {
    ListIterator it = first();
    while (it.valid()) {
        if (it.getCurrent() == e)
            // returns an iterator that points to the element, if it appears in the list
            return it;
        it.next();
    }
    // returns an invalid iterator if the element is not in the list
    return it;
}

TElem IteratedList::setElement(ListIterator pos, TElem e) {
    // throws exception if the position is not valid
    if (!pos.valid())
        throw std::exception();
    TElem oldData = pos.getCurrent();
    pos.current->info = e;

    // returns the old value from the position
    return oldData;
}

void IteratedList::addToPosition(ListIterator &pos, TElem e) {
    // throws an exception if pos is not valid
    if (!pos.valid())
        throw std::exception();
    Node *newNode = new Node;
}

void IteratedList::addToEnd(TElem e) {
    Node *newNode = new Node{e, nullptr};

}

IteratedList::~IteratedList() {
    Node *current = head;
    while (current != nullptr) {
        Node *next = current->next;
        delete current;
        current = next;
    }
}

void IteratedList::addToBeginning(TElem e) {
    Node *newNode = new Node{e, head};
    if (isEmpty())
        tail = newNode;
    head = newNode;
}
