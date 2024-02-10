#include "Matrix.h"
#include <exception>
#include <iostream>

using namespace std;

Matrix::Matrix(int nrLines, int nrCols) {

    //TODO - Implementation
    nrRow = nrLines;
    nrCol = nrCols;
    size = 0;
    head = -1;
    tail = -1;
    capacity = 99999;
    matrix = new Node[capacity];

    for (int i = 0; i < capacity; i++) {
        matrix[i].previous = -1;
        matrix[i].next = i+1;
    }
    firstEmpty = 0;
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
    int current = head;
    while (current != -1){
        if(matrix[current].info.row == i && matrix[current].info.column == j)
            return matrix[current].info.value;
        current = matrix[current].next;
    }
    return NULL_TELEM;
}

int Matrix::allocate() {
    int position= firstEmpty;
    if(position != -1)
    {
        firstEmpty = matrix[firstEmpty].next;
        if(firstEmpty != -1){
            matrix[firstEmpty].previous = -1;
        }
        matrix[position].next = -1;
        matrix[position].previous = -1;
    }
    return position;

}
TElem Matrix::modify(int i, int j, TElem e) {
    //TODO - Implementation
    if (i < 0 || j < 0 || i >= nrRow || j >= nrCol)
        throw invalid_argument("");
    int newNode = allocate();
    matrix[newNode].info.row = i;
    matrix[newNode].info.column = j;
    matrix[newNode].info.value = e;
    if(size == 0 && e!= 0){

    }
    int current = head;

    if(e == 0)
        return NULL_TELEM;
    current = head;
    while(current != -1 && matrix[current].info.row<i){
        current = matrix[current].next;
    }// prev nod current
    if(current == -1){
        matrix[tail].next = newNode;
        matrix[newNode].previous = tail;
        tail = newNode;
        size++;
        return NULL_TELEM;
    }
    int prevN = matrix[current].previous;
    int nextN = matrix[current].next;
    if(prevN == -1){
        matrix[head].previous = newNode;
        matrix[newNode].next = head;
    }
    size++;
    return NULL_TELEM;

}

Matrix::~Matrix() {
    //TODO - Implementation
    delete[] matrix;
}


