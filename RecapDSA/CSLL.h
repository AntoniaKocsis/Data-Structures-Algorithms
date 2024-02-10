#pragma once

#include <iostream>

using namespace std;

struct csllNode {
    int info;
    csllNode *next;
};

class CSLL {
private:
    csllNode *head;
public:
    CSLL() {
        head = nullptr;
    }

    void add(int v) {
        csllNode *newNode = new csllNode;
        newNode->next = newNode;
        newNode->info = v;
        if (head == nullptr) {
            head = newNode;
            return;
        }
        csllNode *lastNode = head;
        while (lastNode->next != head) {
            lastNode = lastNode->next;
        }
        newNode->next = head;
        lastNode->next = newNode;
        head = newNode;

    }

};