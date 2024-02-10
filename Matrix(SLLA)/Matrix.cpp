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
    capacity = 99999;
    matrix = new Tuple[capacity];
    next = new int[capacity];
    for (int i = 0; i < capacity; i++)
        next[i] = i + 1;
    next[capacity - 1] = -1;
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
    while (current != -1) {
        if (matrix[current].row == i && matrix[current].column == j)
            return matrix[current].value;
        current = next[current];
    }
    return NULL_TELEM;
}


TElem Matrix::modify(int i, int j, TElem e) {
    //TODO - Implementation
    if (i < 0 || j < 0 || i >= nrRow || j >= nrCol)
        throw invalid_argument("");

    int newNode = firstEmpty;
    firstEmpty = next[firstEmpty];
    matrix[newNode].row = i;
    matrix[newNode].column = j;
    matrix[newNode].value = e;
    next[newNode] = -1;
    if (size == 0 && e != 0) {
        head = newNode;
        size++;
        return NULL_TELEM;
    }
    int current = head;
    int previous = -1;
    while (current != -1) {
        if (matrix[current].row == i && matrix[current].column == j) {
            TElem elem = matrix[current].value;
            if (e == 0) {
                if (previous == -1) {
                    head = next[head];
                } else {
                    next[previous] = next[current];
                }
                next[current] = firstEmpty;
                firstEmpty = current;
            } else {
                matrix[current].value = e;
            }
            return elem;
        }
        previous = current;
        current = next[current];
    }
    if (e == 0)
        return NULL_TELEM;
    current = head;
    previous = -1;
    while (current != -1 && matrix[current].row < i) {
        previous = current;
        current = next[current];
    }// prev nod current
    if (current == -1) {
        next[previous] = newNode;
        next[newNode] = -1;
    } else if (previous == -1) {
        next[newNode] = head;
        head = newNode;
    } else {
        next[previous] = newNode;
        next[newNode] = current;
    }
    size++;
    return NULL_TELEM;

}

Matrix::~Matrix() {
    //TODO - Implementation
    delete[] next;
    delete[] matrix;
}


