#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

class Matrix {

private:
    int nrRows;
    int nrCol;
    int *column;
    int *values;
    int *index;
    int size;
    int capacity;
    int sizeIndex;
    int capacityIndex;


public:
    //constructor
    Matrix(int nrLines, int nrCols);

    void print();

    //returns the number of lines
    [[nodiscard]] int nrLines() const;

    //returns the number of columns
    [[nodiscard]] int nrColumns() const;

    //returns the element from line i and column j (indexing starts from 0)
    //throws exception if (i,j) is not a valid position in the Matrix
    TElem element(int i, int j);

    //modifies the value from line i and column j
    //returns the previous value from the position
    //throws exception if (i,j) is not a valid position in the Matrix
    TElem modify(int i, int j, TElem e);

    // destructor
    ~Matrix();
};
