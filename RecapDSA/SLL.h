#pragma once

#include <iostream>

using namespace std;
struct Node {
    int info;
    Node *next;
};

class SLL {
private:
    Node *head;
public:
    SLL() {
        head = nullptr;
    }

    void insert(int e) {
        Node *newNode = new Node;
        newNode->next = nullptr;
        newNode->info = e;
        if (head == nullptr) {
            head = newNode;
            return;
        }
        Node *current = head;
        Node *prev = nullptr;
        while (current != nullptr) {
            prev = current;
            current = current->next;
        }
        prev->next = newNode;
    }

    bool search(int e) {
        if (head == nullptr)
            return false;
        if (head->info == e)
            return true;
        Node *current = head->next;
        while (current != nullptr && current->info != e)
            current = current->next;
        if (current == nullptr)
            return false;
        return true;
    }

    bool remove(int e) {
        if (head == nullptr)
            return false;
        Node *previous = nullptr;
        Node *current = head;
        while (current != nullptr && current->info != e) {
            previous = current;
            current = current->next;
        }
        if (current == nullptr)
            return false;
        if (previous == nullptr) {
            head = head->next;
            delete current;
            return true;
        }
        previous->next = current->next;
        delete current;
        return true;
    }

    void printList() {
        Node *current = head;
        while (current != nullptr) {
            cout << current->info << " --> ";
            current = current->next;
        }
        cout << "NIL" << endl;
    }

    void rotate() {
        if (head != nullptr && head->next != nullptr) {
            Node* first = head;
            Node *current = head;
            Node *previous;
            while(current != nullptr){
                previous = current;
                current = current->next;
            }
            Node *newHead = first->next;
            previous->next = head;
            head->next = nullptr;
            head = newHead;
        }
    }
    void reverse(){
        Node *current = head;
        Node *previous = nullptr;
        Node *next = nullptr;
        while (current != nullptr) {
            next = current->next;
            current->next = previous;
            previous = current;
            current = next;
        }

        head = previous;
    }
    bool isEvenNodes() {
        Node* fast = head;
        Node* slow = head;

        while (fast != nullptr && fast->next != nullptr) {
            fast = fast->next->next;
            slow = slow->next;
        }

        return fast == nullptr;
    }








    ~SLL() {
        Node *current = head;
        Node *next = nullptr;
        while (current != nullptr) {
            next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }

};