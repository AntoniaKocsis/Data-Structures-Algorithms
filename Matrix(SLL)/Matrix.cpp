#include "Matrix.h"
#include <exception>
#include <iostream>

using namespace std;

Matrix::Matrix(int nrLines, int nrCols) {

    //TODO - Implementation
    nrRow = nrLines;
    nrCol = nrCols;
    size = 0;
    head = nullptr;
}


int Matrix::nrLines() const {
    //TODO - Implementation
    return nrRow;
}


int Matrix::nrColumns() const {
    //TODO - Implementation
    return nrCol;
}


TElem Matrix::element(int i, int j) const {
    //TODO - Implementation
    if (i < 0 || j < 0 || i >= nrRow || j >= nrCol)
        throw invalid_argument("");
    Node *current = head;
    while (current != nullptr) {
        if (current->info.row == i && current->info.column == j)
            return current->info.value;
        current = current->next;
    }
    return NULL_TELEM;
}


TElem Matrix::modify(int i, int j, TElem e) {
    //TODO - Implementation
    if (i < 0 || j < 0 || i >= nrRow || j >= nrCol)
        throw invalid_argument("");
    Node *newNode = new Node;
    newNode->next = nullptr;
    newNode->info.row = i;
    newNode->info.column = j;
    newNode->info.value = e;

    if (size == 0 && e != 0) {
        head = newNode;
        size++;
        return NULL_TELEM;
    }
    Node *current = head;
    Node *previous = nullptr;
    while (current != nullptr) {
        if (current->info.row == i && current->info.column == j) {
            TElem elem = current->info.value;
            if (e == 0) {
                if (previous == nullptr) {
                    head = head->next;
                } else {
                    previous->next = current->next;
                }
                delete current;
                size--;
            } else {
                current->info.value = e;
            }
            return elem;
        }
        previous = current;
        current = current->next;
    }
    if(e == 0)
        return NULL_TELEM;
    current = head;
    previous = nullptr;
    while(current != nullptr && current->info.row<i){
        previous = current;
        current = current->next;
    }// current nu mai verifica prev nod current
    if(previous == nullptr){
        newNode->next = head;
        head = newNode;
    }else{
        previous->next = newNode;
        newNode->next = current;
    }
    size++;
    return NULL_TELEM;

}

Matrix::~Matrix() {
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


