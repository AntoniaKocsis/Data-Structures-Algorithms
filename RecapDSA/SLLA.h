#pragma once

class SLLA {
private:
    int capacity;
    int size;
    int *array;
    int *next;
    int firstEmpty;
    int head;
public:
    SLLA() {
        capacity = 999999;
        size = 0;
        head = -1;
        array = new int[capacity];
        next = new int[capacity];
        firstEmpty = 0;
        for (int i = 0; i < capacity; i++) {
            next[i] = i + 1;
        }
        next[capacity - 1] = -1;
    }

    void insert(int v) {
        int newNode = firstEmpty;
        firstEmpty = next[firstEmpty];
        next[newNode] = -1;
        array[newNode] = v;
        if (size == 0) {
            head = newNode;
            size++;
            return;
        }
        int current = head;
        int previous = -1;
        while (current != -1) {
            previous = current;
            current = next[current];
        }
        next[previous] = newNode;
        size++;
    }

    bool search(int v) {
        if (head == -1)
            return false;
        int current = head;
        while (current != -1 && array[current] != v) {
            current = next[current];
        }
        if (current == -1)
            return false;
        return true;
    }

    void remove(int v) {
        if (head == -1)
            return;
        int current = head;
        int previous = -1;
        while (current != -1 && array[current] != v) {
            previous = current;
            current = next[current];
        }
        if (current == -1)
            return;
        if (previous == -1) {
            head = next[head];
        } else {
            next[previous] = next[current];
        }
        size--;
        next[current] = firstEmpty;
        firstEmpty = current;
    }

    ~SLLA() {
        delete[] next;
        delete[] array;
    }
};