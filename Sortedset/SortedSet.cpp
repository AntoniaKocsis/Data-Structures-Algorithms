#include "SortedSet.h"
#include "SortedSetIterator.h"

SortedSet::SortedSet(Relation r) {
    // Complexity 0(1) - for each case
    //TODO - Implementation
    this->capacity = 20;
    this->dynamicArray = new TElem[capacity];
    this->currentSize = 0;
    this->relation = r;

}

void SortedSet::resizeUp() {

    // Complexity: Best case Ω(n), Average case θ(n), Worst case O(n)
    int newSize = 2 * this->capacity;
    TElem *newDynamicArray = new TElem[newSize];
    for (int i = 0; i < this->capacity; i++) {
        newDynamicArray[i] = this->dynamicArray[i];
    }
    delete[] dynamicArray;
    this->dynamicArray = newDynamicArray;
    this->capacity = newSize;

}

void SortedSet::resizeDown() {

    // Complexity: Best case Ω(n), Average case θ(n), Worst case O(n)
    int newSize = currentSize + 6;
    TElem *newDynamicArray = new TElem[newSize];
    for (int i = 0; i < this->currentSize; i++) {
        newDynamicArray[i] = this->dynamicArray[i];
    }
    delete[] dynamicArray;
    this->dynamicArray = newDynamicArray;
    this->capacity = newSize;

}

int SortedSet::binarySearch(TComp element, int left, int right) const {
    // Complexity: Best case Ω(1), Average case θ(log n), Worst case O(log n)
    // Returns the position of the element in the container
    // The element is not in the container
    if (left > right)
        return -1;
    if (dynamicArray[right] == element)
        return right;
    if (dynamicArray[left] == element)
        return left;
    int mid = (left + right) / 2;
    if (dynamicArray[mid] == element)
        return mid;
    if (relation(dynamicArray[mid], element))
        return binarySearch(element, mid + 1, right);
    else
        return binarySearch(element, left, mid - 1);

}

int SortedSet::findPosition(TComp elem) {
    // Find the position where the element should be inserted
    // ?? Complexity: Best case Ω(1), Average case θ(log n), Worst case O(log n)
    int left = 0, right = currentSize - 1;
    int mid;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (dynamicArray[mid] == elem) {
            left = mid;
            break;
        } else if (relation(dynamicArray[mid], elem))
            left = mid + 1;
        else
            right = mid - 1;
    }
    // Needed position is saved in left
    return left;
}

bool SortedSet::add(TComp elem) {
    // Complexity: Best case Ω(1), Average case θ(log n), Worst case O(n)
    //TODO - Implementation
    // Check is container is empty
    if (isEmpty()) {
        dynamicArray[0] = elem;
        currentSize++;
        return true;
    }
    // If the element is in the container it won't be added again
    if (search(elem))
        return false;
    // If the capacity is too small => resize
    if (currentSize == capacity)
        resizeUp();
    // Find the position where the element should be inserted

    int position = findPosition(elem);
    for (int i = currentSize; i > position; i--) {
        dynamicArray[i] = dynamicArray[i - 1];
    }

    dynamicArray[position] = elem;
    currentSize++;
    return true;


}


bool SortedSet::remove(TComp elem) {
    //Complexity: Best case Ω(1), Average case θ(log n), Worst case O(n)
    //TODO - Implementation
    //Check if container is empty
    if (isEmpty()) return false;
    //Check if element is in the container
    if (!search(elem))
        return false;
    //  Find the position of the element
    int position = binarySearch(elem, 0, currentSize - 1);

    // Remove element
    for (int i = position; i < currentSize - 1; i++)
        dynamicArray[i] = dynamicArray[i + 1];
    // Decrement size
    currentSize--;
    // Check if there is too much unused space saved
    if (currentSize == capacity / 4)
        resizeDown();
    return true;
}


bool SortedSet::search(TComp elem) const {
    /* Complexity: Best case Ω(1), Average case θ(log n), Worst case O(log n)
* */
    //TODO - Implementation
    // Check if container is empty
    if (isEmpty())
        return false;
    // Do a binary search
    if (binarySearch(elem, 0, currentSize - 1) != -1)
        return true;
    return false;
}


int SortedSet::size() const {
    //TODO - Implementation
    //Complexity 0(1)
    return currentSize;
}


bool SortedSet::isEmpty() const {
    //Complexity 0(1)
    //TODO - Implementation
    if (currentSize == 0)
        return true;
    return false;
}

SortedSetIterator SortedSet::iterator() const {
    //Complexity 0(1)
    return SortedSetIterator(*this);
}


SortedSet::~SortedSet() {
    //TODO - Implementation
    //Complexity 0(1)
    delete[] dynamicArray;
}

void SortedSet::merge(SortedSet set) {

    int size = set.currentSize;
    int new_capacity = set.capacity + capacity;
    TElem *newset = new TElem[new_capacity];
    int i = 0, j = 0, k = 0;

    while (i < currentSize && j < set.currentSize) {
        if (relation(dynamicArray[i], set.dynamicArray[j])) {
            newset[k] = dynamicArray[i];
            i++;
        } else {
            newset[k] = set.dynamicArray[j];
            j++;
        }
        k++;
    }

    while (i < currentSize) {
        newset[k] = dynamicArray[i];
        i++;
        k++;
    }

    while (j < set.currentSize) {
        newset[k] = set.dynamicArray[j];
        j++;
        k++;
    }
    delete[] dynamicArray;
    this->dynamicArray = newset;
    this->capacity = new_capacity;
    this->currentSize = k;
}

