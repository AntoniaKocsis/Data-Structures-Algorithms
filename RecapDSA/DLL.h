#pragma once

#include <iostream>

using namespace std;

struct DLLNode {
    int info;
    DLLNode *next;
    DLLNode *previous;
};

class DLL {
private:
    DLLNode *head;
    DLLNode *tail;
public:
    DLL() {
        head = nullptr;
        tail = nullptr;
    }

    void insert(int e) {
        DLLNode *newNode = new DLLNode;
        newNode->next = nullptr;
        newNode->previous = nullptr;
        newNode->info = e;
        if (head == nullptr) {
            head = newNode;
            head->previous = nullptr;
            tail = newNode;
            tail->next = nullptr;
            return;
        }
        newNode->previous = tail;
        tail->next = newNode;
        tail = newNode;
    }

    bool remove(int e) {
        if (head == nullptr)
            return false;
        DLLNode *current = head;
        while (current != nullptr && current->info != e) {
            current = current->next;
        }
        if (current == nullptr)
            return false;
        if (current->previous == nullptr) {
            if (current->next == nullptr) {
                head = nullptr;
                tail = nullptr;
            } else {
                head = head->next;
                head->previous = nullptr;
            }
            delete current;
            return true;
        }
        if(current->next == nullptr){
            current->previous->next = nullptr;
            tail = current->previous;
            delete current;
            return true;
        }
        current->previous->next = current->next;
        current->next->previous = current->previous;
        delete current;
        return true;
    }

    void printList() {
        DLLNode *current = head;
        while (current != nullptr) {
            cout << current->info << " --> ";
            current = current->next;
        }
        cout <<"NIL"<< endl;
    }

    ~DLL() {
        DLLNode *current = head;
        DLLNode *next = nullptr;
        while (current != nullptr) {
            next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
    }
};