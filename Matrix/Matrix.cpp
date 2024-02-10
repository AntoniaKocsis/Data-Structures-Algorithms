#include "Matrix.h"
#include <exception>
#include <stdexcept>
#include <iostream>

using namespace std;

Matrix::Matrix(int nrLines, int nrCols) {
    size= 0;
    sizeIndex = 0;
    capacity = 20;
    capacityIndex = 20;
    column = new int[capacity];
    values = new int[capacity];
    this->nrRows = nrLines;
}

int Matrix::nrLines() const {

}

int Matrix::nrColumns() const {

}

TElem Matrix::element(int i, int j) {
    if (i < 0 || j < 0 || i >= this->nrLines() || j >= this->nrColumns()) {
        throw std::out_of_range("Invalid Position for your element");
    }
}


TElem Matrix::modify(int i, int j, TElem e) {
    if (i < 0 || j < 0 || i > this->nrLines() || j > this->nrColumns()) {
        throw std::out_of_range("Invalid Position for your element");
    }
}

Matrix::~Matrix() {
}
