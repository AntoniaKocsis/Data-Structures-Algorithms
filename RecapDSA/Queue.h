#pragma once

#include <iostream>

using namespace std;

class Queue {
private:
    int capacity;
    int *queue;
    int front;
    int rear;
public:
    Queue() {
        this->capacity = 25;
        this->front = -1;
        this->rear = -1;
        this->queue = new int[this->capacity];
    }

    void push(int e) {
        if (front == -1) {
            front = 0;
            rear = 0;
            queue[front] = e;
            return;
        }
        if ((front == 0 && rear == capacity - 1) || (rear == front - 1)) {
            resize_push();
        }
        if (rear != capacity - 1) {
            queue[rear+1] = e;
            rear++;
            return;
        }
        queue[0] = e;
        rear++;


    }

    //returns the element from the front of the queue
    //throws exception if the queue is empty
    int top() const;

    //removes and returns the element from the front of the queue
    //throws exception if the queue is empty
    int pop();

    int print_helper();

    //checks if the queue is empty
    bool isEmpty() const;

    //resize the array when it's full
    void resize_push();

    //resize the array when there are too few elements
    void resize_pop();

    //print the elements of the queue
    void print_queue();

    // destructor
    ~Queue();
};