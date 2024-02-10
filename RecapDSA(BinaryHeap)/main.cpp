#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class MaxHeap {
private:
    int capacity;
    int size;
    int *array;
public:
    MaxHeap() {
        capacity = 20;
        array = new int[capacity];
        size = 0;
    }

    void insert(int value) {
        array[size] = value;
        size++;
        bubbleUp();
    }

    // parent:  i  => (i - 1)/2
    // child: i  => 2 * i +1, 2* i + 2
    void bubbleUp() {
        int currentIdx = size - 1;
        int parentIdx = (currentIdx - 1) / 2;
        while (array[currentIdx] > array[parentIdx]) {
            int aux = array[currentIdx];
            array[currentIdx] = array[parentIdx];
            array[parentIdx] = aux;
            currentIdx = parentIdx;
            parentIdx = (currentIdx - 1) / 2;
        }


    }

    void remove() {
        array[0] = array[size - 1];
        size--;
        bubbleDown();

    }

    void bubbleDown() {
        int currentIdx = 0;
        int leftIdx = (currentIdx * 2) + 1;
        int rightIdx = (currentIdx * 2) + 2;
        int childIdx;
        while (leftIdx < size) {
            if (rightIdx < size && array[rightIdx] > array[leftIdx])
                childIdx = rightIdx;
            else
                childIdx = leftIdx;
            if (array[childIdx] > array[currentIdx]) {
                swap(array[currentIdx], array[childIdx]);
                currentIdx = childIdx;
                leftIdx = (currentIdx * 2) + 1;
                rightIdx = (currentIdx * 2) + 2;
            } else {
                break;
            }
        }
    }

    void printHeap() {
        for (int i = 0; i < size; i++)
            cout << array[i] << " ";
        cout << endl;
    }
};

void heap() {
    MaxHeap heap;
    vector<int> list = {63, 55, 21, 11, 51, 9, 16, 4, 5, 7, 14};
    for (int i = 0; i < list.size(); i++)
        heap.insert(list[i]);
    heap.printHeap();
    heap.remove();
    heap.printHeap();
}

struct Node {
    int info;
    Node *parent;
    Node *firstChild;
    Node *rightBrother;
};

class BinomialTree {
private:
    Node *root;
    int numberOfNodes;
public:
    BinomialTree(vector<int> values) {

        numberOfNodes = values.size();
        if (!isPowerOfTwo(numberOfNodes))
            throw exception();
        sort(values.begin(), values.end());

        Node *current = nullptr;
        root = nullptr;

        for (int value: values) {
            Node *newNode = new Node;
            newNode->firstChild = nullptr;
            newNode->rightBrother = nullptr;
            newNode->parent = nullptr;
            newNode->info = value;
            if (root == nullptr) {
                root = newNode;
                current = root;
            } else {
                if (current->firstChild == nullptr) {
                    newNode->parent = current;
                    current->firstChild = newNode;

                } else if (current->firstChild != nullptr && current->firstChild->rightBrother == nullptr) {
                    newNode->parent = current;
                    current->firstChild->rightBrother = newNode;
                    current = current->firstChild;
                } else {
                    current = current->firstChild;
                }
            }
        }

    }

    bool isPowerOfTwo(int n) {
        // A number is a power of 2 if and only if the logarithm (base 2) of the number is an integer.

        if (n <= 0)
            return false;

        double logValue = log2(n);
        int intLog = static_cast<int>(logValue);

        return logValue == intLog;
    }

    void printTree() {
        Node *current = root;
        while (current != nullptr) {
            cout << current->info << " ";
            if (current->firstChild != nullptr) {
                cout << current->firstChild->info << " ";
                if (current->firstChild->rightBrother != nullptr)
                    cout << current->firstChild->rightBrother->info << " ";
            }
            current = current->firstChild;
        }
    }

};

int main() {

    vector<int> values = {8, 11, 13, 21};
    BinomialTree tree(values);
    tree.printTree();
    return 0;
}
