#pragma once

#include <iostream>

using namespace std;
struct NodeDLLA {
    int info;
    int next;
    int previous;
};

class DLLA {
private:
    int capacity, size, firstEmpty;
    int head, tail;
    NodeDLLA *array;
public:
    DLLA() {
        capacity = 9999;
        size = 0;
        head = -1;
        tail = -1;
        firstEmpty = 0;
        array = new NodeDLLA[capacity];
        for (int i = 0; i < capacity; i++) {
            array[i].next = i + 1;
            array[i].previous = i - 1;
        }
        array[capacity - 1].next = -1;
    }

    int allocate() {
        int position;
        position = firstEmpty;
        if (position != -1) {
            firstEmpty = array[firstEmpty].next;
            if (firstEmpty != -1) {
                array[firstEmpty].previous = -1;
            }
            array[position].next = -1;
            array[position].previous = -1;
        }
        return position;
    }

    void add(int v) {
        int position = allocate();
        array[position].info = v;
        if (size == 0) {
            head = position;
            tail = position;
            size++;
            return;
        }
        array[tail].next = position;
        array[position].previous = tail;
        tail = position;
        size++;
    }

    void remove(int v) {
        if (head == -1)
            return;
        int current = head;
        while (current != -1 && array[current].info != v) {
            current = array[current].next;
        }
        if (current == -1)
            return;
        int previous = array[current].previous;
        int next = array[current].next;
        if (previous == -1) {
            if (next == -1) {
                head = -1;
                tail = -1;
            } else {
                head = next;
                array[head].previous = -1;
            }
        }else if(next == -1){
            tail = previous;
            array[tail].next = -1;
        } else{
            array[previous].next = next;
            array[next].previous = previous;
        }
        array[current].next = firstEmpty;
        firstEmpty = current;
        size--;
    }

};