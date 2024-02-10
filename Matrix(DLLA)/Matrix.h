#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

struct Tuple {
    int row;
    int column;
    TElem value;

};
struct Node {
    Tuple info;
    int next;
    int previous;
};

class Matrix {

private:
    //TODO - Representation
    Node *matrix;
    int capacity;
    int nrRow;
    int nrCol;
    int size;
    int head;
    int tail;
    int firstEmpty;
public:
    //constructor
    Matrix(int nrLines, int nrCols);

    //returns the number of lines
    int nrLines() const;

    //returns the number of columns
    int nrColumns() const;
    int allocate();
    void free(int position);
    //returns the element from line i and column j (indexing starts from 0)
    //throws exception if (i,j) is not a valid position in the Matrix
    TElem element(int i, int j) const;

    //modifies the value from line i and column j
    //returns the previous value from the position
    //throws exception if (i,j) is not a valid position in the Matrix
    TElem modify(int i, int j, TElem e);

    // destructor
    ~Matrix();

};
