#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>

using namespace std;

/**
 * array-ul de next se initializeaza cu -1
 * fiecare cheie din array se initializeaza cu -1
 * pentru fiecare cheie se initializeaza: size,capacity, array-ul de valori
 * firstEmpty ara spre prima pozitie = 0
 * **/
SortedMultiMap::SortedMultiMap(Relation r) {
    /** Complexity: Theta(n)  **/
    relation = r;
    capacity = 29;
    sizeArray = 0;
    dynamicArray = new ArrayValue[capacity];
    next = new int[capacity];
    for (int i = 0; i < capacity; i++) {
        dynamicArray[i].key = -1;
        dynamicArray[i].sizeValues = 0;
        dynamicArray[i].capacityValues = 20;
        dynamicArray[i].values = new TValue[20];
        next[i] = -1;
    }

    firstEmpty = 0;
}


TFunction SortedMultiMap::h(TKey key) const {
    /** Complexity: Theta(1) **/
    return abs(key) % capacity;
}

/**
 * Functie de resize pentru array-ul de valori
 * parametru: cheie
 * 1. Se determina pozitia corespunzatoare cheii
 * 2. Se cauta pozitia pe care se afla cheia in momentul actual
 * 3. In cazul in care cheia nu a fost gasita nu are loc resize-ul**/

void SortedMultiMap::resizeUpValues(TKey key) const {
    /** Complexity: Theta(n) **/
    int position = h(key);
    while (position != -1 && dynamicArray[position].key != key) {
        position = next[position];
    }
    if (position == -1)
        return;
    int newCapacity = 2 * dynamicArray[position].capacityValues;
    auto *newValues = new TValue[newCapacity];
    for (int i = 0; i < dynamicArray[position].capacityValues; i++)
        newValues[i] = dynamicArray[position].values[i];
    delete[] dynamicArray[position].values;
    this->dynamicArray[position].values = newValues;
    this->dynamicArray[position].capacityValues = newCapacity;

}

void SortedMultiMap::resizeDownValues(TKey key) {
    /** Complexity: Theta(n) **/
    int position = h(key);
    while (position != -1 && dynamicArray[position].key != key) {
        position = next[position];
    }
    int newCapacity = dynamicArray[position].capacityValues / 2;
    TValue *newValues = new TValue[newCapacity];
    for (int i = 0; i < dynamicArray[position].capacityValues; i++)
        newValues[i] = dynamicArray[position].values[i];
    delete[]dynamicArray[position].values;
    this->dynamicArray[position].values = newValues;
    this->capacity = newCapacity;
}

bool SortedMultiMap::isPrim(int value) {
    /** Complexity: Best: Theta(1)
     *              Average: Theta(n)
     *              Worst: Theta(n) **/
    if (value < 2)
        return false;
    if (value % 2 == 0)
        return false;
    for (int d = 3; d * d <= value; d++)
        if (value % d == 0)
            return false;
    return true;

}

/**
 * Functie ajutatoare pentru a determina capacitatea care ar duce la cat mai putine coliziuni(un numar prim)**/
int SortedMultiMap::findFirstPrim() const {
    /** Complexity: Best: Theta(1)
 *              Average: Theta(n)
 *              Worst: Theta(n) **/
    int newCapacity = 2 * capacity + 1;
    if (isPrim(newCapacity))
        return newCapacity;
    while (true) {
        if (isPrim(newCapacity)) {
            break;
        }
        newCapacity++;
    }
    return newCapacity;
}

int SortedMultiMap::findLastPrim() const {
    /** Complexity: Theta(n) **/
    int newCapacity = capacity / 2;
    while (true) {
        if (isPrim(newCapacity)) {
            break;
        }
        newCapacity++;
    }
    return newCapacity;
}

void SortedMultiMap::resizeUp() {
    /** Complexity:  Theta(n^2) **/
    int newCapacity = findFirstPrim();
    auto *newArray = new ArrayValue[newCapacity];
    int *newNext = new int[newCapacity];
    int newFirstEmpty = 0;


    for (int i = 0; i < newCapacity; i++) {
        newArray[i].key = -1;
        newArray[i].sizeValues = 0;
        newArray[i].capacityValues = 20;
        newArray[i].values = new TValue[newArray[i].capacityValues];
        newNext[i] = -1;
    }


    for (int i = 0; i < capacity; i++) {
        if (dynamicArray[i].key != -1) {
            int key = dynamicArray[i].key;
            int position = abs(key) % newCapacity;

            if (newArray[position].key == -1) {

                newArray[position].key = key;
                newArray[position].sizeValues = dynamicArray[i].sizeValues;
                delete[] newArray[position].values;
                newArray[position].values = new TValue[dynamicArray[i].capacityValues];
                newArray[position].capacityValues = dynamicArray[i].capacityValues;
                for (int j = 0; j < dynamicArray[i].sizeValues; j++)
                    newArray[position].values[j] = dynamicArray[i].values[j];

                if (position == newFirstEmpty) {
                    for (int j = 0; j < newCapacity; j++)
                        if (newArray[j].key == -1) {
                            newFirstEmpty = j;
                            newNext[newFirstEmpty] = -1;
                            break;
                        }
                }

            } else {

                int current = position;
                while (newNext[current] != -1) {
                    current = newNext[current];
                }


                newArray[newFirstEmpty].key = key;
                newArray[newFirstEmpty].sizeValues = dynamicArray[i].sizeValues;
                delete[] newArray[newFirstEmpty].values;
                newArray[newFirstEmpty].values = new TValue[dynamicArray[i].capacityValues];
                newArray[newFirstEmpty].capacityValues = dynamicArray[i].capacityValues;
                for (int j = 0; j < dynamicArray[i].sizeValues; j++)
                    newArray[newFirstEmpty].values[j] = dynamicArray[i].values[j];

                newNext[newFirstEmpty] = -1;
                newNext[current] = newFirstEmpty;

                for (int j = 0; j < newCapacity; j++)
                    if (newArray[j].key == -1) {
                        newFirstEmpty = j;
                        newNext[newFirstEmpty] = -1;
                        break;
                    }

            }
        }
    }


    for (int i = 0; i < capacity; i++)
        delete[] dynamicArray[i].values;
    delete[] dynamicArray;
    delete[] next;
    next = newNext;
    capacity = newCapacity;
    firstEmpty = newFirstEmpty;
    dynamicArray = newArray;
}

void SortedMultiMap::resizeDown() {
    /** Complexity: Theta(n^2) **/
    int newCapacity = findLastPrim();
    auto *newArray = new ArrayValue[newCapacity];
    int *newNext = new int[newCapacity];
    int newFirstEmpty = 0;


    for (int i = 0; i < newCapacity; i++) {
        newArray[i].key = -1;
        newArray[i].sizeValues = 0;
        newArray[i].capacityValues = 20;
        newArray[i].values = new TValue[newArray[i].capacityValues];
        newNext[i] = -1;
    }


    for (int i = 0; i < capacity; i++) {
        if (dynamicArray[i].key != -1) {
            int key = dynamicArray[i].key;
            int position = abs(key) % newCapacity; // Use the new capacity for rehashing

            if (newArray[position].key == -1) {
                newArray[position].key = key;
                newArray[position].sizeValues = dynamicArray[i].sizeValues;
                delete[] newArray[position].values;
                newArray[position].values = new TValue[dynamicArray[i].capacityValues];
                newArray[position].capacityValues = dynamicArray[i].capacityValues;
                for (int j = 0; j < dynamicArray[i].sizeValues; j++)
                    newArray[position].values[j] = dynamicArray[i].values[j];

                if (position == newFirstEmpty) {
                    for (int j = 0; j < newCapacity; j++)
                        if (newArray[j].key == -1) {
                            newFirstEmpty = j;
                            newNext[newFirstEmpty] = -1;
                            break;
                        }
                }

            } else {
                // Find the next available position for collision resolution
                int current = position;
                while (newNext[current] != -1) {
                    current = newNext[current];
                }

                // Insert the key-value pair at the new available position
                newArray[newFirstEmpty].key = key;
                newArray[newFirstEmpty].sizeValues = dynamicArray[i].sizeValues;
                delete[] newArray[newFirstEmpty].values;
                newArray[newFirstEmpty].values = new TValue[dynamicArray[i].capacityValues];
                newArray[newFirstEmpty].capacityValues = dynamicArray[i].capacityValues;
                for (int j = 0; j < dynamicArray[i].sizeValues; j++)
                    newArray[newFirstEmpty].values[j] = dynamicArray[i].values[j];

                newNext[newFirstEmpty] = -1;
                newNext[current] = newFirstEmpty;

                for (int j = 0; j < newCapacity; j++)
                    if (newArray[j].key == -1) {
                        newFirstEmpty = j;
                        newNext[newFirstEmpty] = -1;
                        break;
                    }


            }
        }
    }


    for (int i = 0; i < capacity; i++)
        delete[] dynamicArray[i].values;
    delete[] dynamicArray;
    delete[] next;
    next = newNext;
    capacity = newCapacity;
    firstEmpty = newFirstEmpty;
    dynamicArray = newArray;
}

void SortedMultiMap::changeFirstEmpty() {
    /** Complexity: Best: Theta(1)
*              Average: Theta(n)
*              Worst: Theta(n) **/
    if (dynamicArray[0].key == -1) {
        firstEmpty = 0;
        next[firstEmpty] = -1;
        return;
    }
    for (int i = 1; i < capacity; i++)
        if (dynamicArray[i].key == -1) {
            firstEmpty = i;
            next[firstEmpty] = -1;
            break;
        }
}

void SortedMultiMap::add(TKey c, TValue v) {
    //TODO - Implementation
    /** Complexity: Best: Theta(1)
*              Average: Theta(n)
*              Worst: Theta(n^2) **/
    int position = h(c);
    if (firstEmpty == capacity || sizeArray == capacity)
        resizeUp();
    /** Se verifica daca pozitia corespunzatoare este goala sau nu
     * In cazul in care este goala => se adauga direct elementul**/
    if (dynamicArray[position].key == -1) {
        dynamicArray[position].key = c;
        dynamicArray[position].values[dynamicArray[position].sizeValues] = v;
        dynamicArray[position].sizeValues++;
        sizeArray++;
        if (firstEmpty == position)
            changeFirstEmpty();
        return;
    }
    /** Se verifica daca pozitia corespunzatoare contine sau nu cheia pe care dorim sa o inseram
 * In cazul in care da => se adauga v in lista de valori a cheii c**/

    if (dynamicArray[position].key == c) {
        if (dynamicArray[position].sizeValues == dynamicArray[position].capacityValues)
            resizeUpValues(c);
        dynamicArray[position].values[dynamicArray[position].sizeValues] = v;
        dynamicArray[position].sizeValues++;
        sizeArray++;
        return;
    }


    int current = position;
    while (next[current] != -1) {
        if (dynamicArray[current].key == c) {
            if (dynamicArray[current].sizeValues == dynamicArray[current].capacityValues)
                resizeUpValues(c);
            dynamicArray[current].values[dynamicArray[current].sizeValues] = v;
            dynamicArray[current].sizeValues++;
            sizeArray++;
            return;
        }
        current = next[current];
    }
    if (dynamicArray[current].key == c) {
        if (dynamicArray[current].sizeValues == dynamicArray[current].capacityValues)
            resizeUpValues(c);
        dynamicArray[current].values[dynamicArray[current].sizeValues] = v;
        dynamicArray[current].sizeValues++;
        sizeArray++;
        return;
    }

    dynamicArray[firstEmpty].key = c;
    dynamicArray[firstEmpty].values[dynamicArray[firstEmpty].sizeValues] = v;
    dynamicArray[firstEmpty].sizeValues++;
    next[firstEmpty] = -1;
    next[current] = firstEmpty;
    changeFirstEmpty();
    sizeArray++;

}

vector<TValue> SortedMultiMap::search(TKey c) const {
    //TODO - Implementation
    /** Complexity: Best: Theta(1)
*              Average: Theta(n)
*              Worst: Theta(n) **/
    if (isEmpty())
        return {};
    int position = h(c);
    while (position != -1 && dynamicArray[position].key != c) {
        position = next[position];
    }
    if (position == -1)
        return {};
    vector<TValue> vector1;
    for (int i = 0; i < dynamicArray[position].sizeValues; i++)
        vector1.push_back(dynamicArray[position].values[i]);
    return vector1;

}

void SortedMultiMap::removeValueFromKey(int positionKey, int positionValue) const {
    /** Complexity: Theta(n) **/
    for (int i = positionValue; i < dynamicArray[positionKey].sizeValues - 1; i++) {
        dynamicArray[positionKey].values[i] = dynamicArray[positionKey].values[i + 1];
    }
    dynamicArray[positionKey].sizeValues--;
}

void SortedMultiMap::freePosition(int position) const {
    /** Complexity: Theta(1) **/
    dynamicArray[position].key = -1;
}

bool SortedMultiMap::remove(TKey c, TValue v) {
    /** Complexity: Best: Theta(1)
*              Average: Theta(n)
*              Worst: Theta(n^2) **/
    if (isEmpty())
        return false;

    int position = h(c);
    int previous = -1;
    while (position != -1 && dynamicArray[position].key != c) {
        previous = position;
        position = next[position];
    }
    /** Daca position == -1, inseamna ca nu a fost gasita cheia**/
    if (position == -1)
        return false;
    int sizeValues = dynamicArray[position].sizeValues;
    int valuePosition = -1;
    for (int i = 0; i < sizeValues; i++)
        if (dynamicArray[position].values[i] == v) {
            valuePosition = i;
            break;
        }
    if (valuePosition == -1)
        return false;
    removeValueFromKey(position, valuePosition);
    if (dynamicArray[position].sizeValues == dynamicArray[position].capacityValues / 4)
        resizeDownValues(dynamicArray[position].key);
    if (dynamicArray[position].sizeValues == 0) {
        int i = position;
        int j = previous;
        bool over = false;
        int p, pp;
        while (!over) {
            p = next[i];
            pp = i;
            while (p != -1 && h(dynamicArray[p].key) != i) {
                pp = p;
                p = next[p];
            }
            if (p == -1) {
                over = true;
            } else {
                dynamicArray[i].key = dynamicArray[p].key;
                dynamicArray[i].sizeValues = dynamicArray[p].sizeValues;
                dynamicArray[i].capacityValues = dynamicArray[p].capacityValues;
                delete[] dynamicArray[i].values;
                dynamicArray[i].values = new TValue[dynamicArray[i].capacityValues];
                for (int k = 0; k < capacity; k++)
                    dynamicArray[i].values[k] = dynamicArray[p].values[k];

                j = pp;
                i = p;
            }

        }
        if (j != -1) {
            next[j] = next[i];
        }
        freePosition(i);
        next[i] = -1;

        if (firstEmpty > i)
            firstEmpty = i;

    }
    sizeArray--;
    if (sizeArray == capacity / 4)
        resizeDown();
    return true;
}


int SortedMultiMap::size() const {
    /** Complexity: Theta(1) **/
    return sizeArray;
}

bool SortedMultiMap::isEmpty() const {
    /** Complexity: Theta(1) **/
    if (sizeArray == 0)
        return true;
    return false;
}

SMMIterator SortedMultiMap::iterator() const {
    return SMMIterator(*this);
}

SortedMultiMap::~SortedMultiMap() {
    /** Complexity: Theta(n) **/
    for (int i = 0; i < capacity; i++)
        delete[] dynamicArray[i].values;
    delete[] dynamicArray;
    delete[] next;

}

SortedMultiMap SortedMultiMap::concat(SortedMultiMap sortedMultiMap) {
    SortedMultiMap newSmm(relation);
    int i = 0, j = 0;
    newSmm.capacity = capacity + sortedMultiMap.capacity;
    newSmm.sizeArray = 0;
    while (i < capacity && j < sortedMultiMap.capacity) {

        if (relation(dynamicArray[i].key, sortedMultiMap.dynamicArray[j].key)) {
            int position = abs(dynamicArray[i].key) % newSmm.capacity;
            if (newSmm.dynamicArray[position].key == -1) {
                newSmm.dynamicArray[position].key = dynamicArray[i].key;
                newSmm.dynamicArray[position].sizeValues = dynamicArray[i].sizeValues;
                newSmm.dynamicArray[position].capacityValues = dynamicArray[i].capacityValues;
                for (int index = 0; index < newSmm.dynamicArray[position].sizeValues; index++)
                    newSmm.dynamicArray[position].values[index] = dynamicArray[i].values[index];
            } else if (newSmm.dynamicArray[position].key == dynamicArray[i].key) {
                if (newSmm.dynamicArray[position].sizeValues + dynamicArray[i].sizeValues >=
                    newSmm.dynamicArray[position].capacityValues)
                    newSmm.resizeUpValues(dynamicArray[position].key);
                for (int index = 0; index < newSmm.dynamicArray[position].sizeValues; index++) {
                    newSmm.dynamicArray[position].values[newSmm.dynamicArray[position].sizeValues] = dynamicArray[i].values[index];
                    newSmm.dynamicArray[position].sizeValues++;
                }
                newSmm.dynamicArray[position].sizeValues += dynamicArray[i].sizeValues;
                newSmm.dynamicArray[position].capacityValues += dynamicArray[i].capacityValues;
            } else {
                int current = position;
                while (newSmm.next[current] != -1) {
                    if (newSmm.dynamicArray[current].key == dynamicArray[i].key) {
                        if (newSmm.dynamicArray[current].sizeValues + dynamicArray[i].sizeValues >=
                            newSmm.dynamicArray[current].capacityValues)
                            newSmm.resizeUpValues(dynamicArray[current].key);
                        for (int index = 0; index < dynamicArray[i].sizeValues; index++) {
                            newSmm.dynamicArray[current].values[newSmm.dynamicArray[current].sizeValues] = dynamicArray[i].values[index];
                            newSmm.dynamicArray[current].sizeValues++;
                        }
                        newSmm.dynamicArray[current].capacityValues += dynamicArray[i].capacityValues;
                        break;
                    }
                    current = newSmm.next[current];
                }
                if (newSmm.dynamicArray[current].key == dynamicArray[i].key) {
                    if (newSmm.dynamicArray[current].sizeValues + dynamicArray[i].sizeValues >=
                        newSmm.dynamicArray[current].capacityValues)
                        newSmm.resizeUpValues(newSmm.dynamicArray[current].key);
                    for (int index = 0; index < dynamicArray[i].sizeValues; index++) {
                        newSmm.dynamicArray[current].values[newSmm.dynamicArray[current].sizeValues] = dynamicArray[i].values[index];
                        newSmm.dynamicArray[current].sizeValues++;
                    }
                    newSmm.dynamicArray[current].capacityValues += dynamicArray[i].capacityValues;
                }else{
                    newSmm.dynamicArray[newSmm.firstEmpty].key = dynamicArray[i].key;
                    newSmm.dynamicArray[newSmm.firstEmpty].sizeValues = dynamicArray[i].sizeValues;
                    newSmm.dynamicArray[newSmm.firstEmpty].capacityValues = dynamicArray[i].capacityValues;
                    for (int index = 0; index < dynamicArray[i].sizeValues; index++)
                        newSmm.dynamicArray[position].values[index] = dynamicArray[i].values[index];
                    newSmm.next[newSmm.firstEmpty] = -1;
                    newSmm.next[current] = newSmm.firstEmpty;
                    newSmm.changeFirstEmpty();
                }
            }
            i++;
            newSmm.sizeArray++;
        } else {
            int position = abs(sortedMultiMap.dynamicArray[j].key) % newSmm.capacity;
            if (newSmm.dynamicArray[position].key == -1) {
                newSmm.dynamicArray[position].key = sortedMultiMap.dynamicArray[j].key;
                newSmm.dynamicArray[position].sizeValues = sortedMultiMap.dynamicArray[j].sizeValues;
                newSmm.dynamicArray[position].capacityValues = sortedMultiMap.dynamicArray[j].capacityValues;
                for (int index = 0; index < newSmm.dynamicArray[position].sizeValues; index++)
                    newSmm.dynamicArray[position].values[index] = sortedMultiMap.dynamicArray[j].values[index];
            } else if (newSmm.dynamicArray[position].key == sortedMultiMap.dynamicArray[j].key) {
                if (newSmm.dynamicArray[position].sizeValues + sortedMultiMap.dynamicArray[j].sizeValues >=
                    newSmm.dynamicArray[position].capacityValues)
                    newSmm.resizeUpValues(newSmm.dynamicArray[position].key);
                for (int index = 0; index < newSmm.dynamicArray[position].sizeValues; index++) {
                    newSmm.dynamicArray[position].values[newSmm.dynamicArray[position].sizeValues] = sortedMultiMap.dynamicArray[j].values[index];
                    newSmm.dynamicArray[position].sizeValues++;
                }
                newSmm.dynamicArray[position].sizeValues += sortedMultiMap.dynamicArray[j].sizeValues;
                newSmm.dynamicArray[position].capacityValues += sortedMultiMap.dynamicArray[j].capacityValues;
            } else {
                int current = position;
                while (newSmm.next[current] != -1) {
                    if (newSmm.dynamicArray[current].key == sortedMultiMap.dynamicArray[j].key) {
                        if (newSmm.dynamicArray[current].sizeValues + sortedMultiMap.dynamicArray[j].sizeValues >=
                            newSmm.dynamicArray[current].capacityValues)
                            newSmm.resizeUpValues(newSmm.dynamicArray[current].key);
                        for (int index = 0; index < sortedMultiMap.dynamicArray[j].sizeValues; index++) {
                            newSmm.dynamicArray[current].values[newSmm.dynamicArray[current].sizeValues] = sortedMultiMap.dynamicArray[j].values[index];
                            newSmm.dynamicArray[current].sizeValues++;
                        }
                        newSmm.dynamicArray[current].capacityValues += sortedMultiMap.dynamicArray[j].capacityValues;
                        break;
                    }
                    current = newSmm.next[current];
                }
                if (newSmm.dynamicArray[current].key == sortedMultiMap.dynamicArray[j].key) {
                    if (newSmm.dynamicArray[current].sizeValues + sortedMultiMap.dynamicArray[j].sizeValues >=
                        newSmm.dynamicArray[current].capacityValues)
                        newSmm.resizeUpValues(newSmm.dynamicArray[current].key);
                    for (int index = 0; index < sortedMultiMap.dynamicArray[j].sizeValues; index++) {
                        newSmm.dynamicArray[current].values[newSmm.dynamicArray[current].sizeValues] = sortedMultiMap.dynamicArray[j].values[index];
                        newSmm.dynamicArray[current].sizeValues++;
                    }
                    newSmm.dynamicArray[current].capacityValues += sortedMultiMap.dynamicArray[j].capacityValues;
                }else{
                    newSmm.dynamicArray[newSmm.firstEmpty].key = sortedMultiMap.dynamicArray[j].key;
                    newSmm.dynamicArray[newSmm.firstEmpty].sizeValues = sortedMultiMap.dynamicArray[j].sizeValues;
                    newSmm.dynamicArray[newSmm.firstEmpty].capacityValues = sortedMultiMap.dynamicArray[j].capacityValues;
                    for (int index = 0; index < sortedMultiMap.dynamicArray[i].sizeValues; index++)
                        newSmm.dynamicArray[newSmm.firstEmpty].values[index] = sortedMultiMap.dynamicArray[j].values[index];
                    newSmm.next[newSmm.firstEmpty] = -1;
                    newSmm.next[current] = newSmm.firstEmpty;
                    newSmm.changeFirstEmpty();
                }
            }
            j++;
            newSmm.sizeArray++;
        }

    }

    while (i < capacity) {
        int position = abs(dynamicArray[i].key) % newSmm.capacity;
        if (newSmm.dynamicArray[position].key == -1) {
            newSmm.dynamicArray[position].key = dynamicArray[i].key;
            newSmm.dynamicArray[position].sizeValues = dynamicArray[i].sizeValues;
            newSmm.dynamicArray[position].capacityValues = dynamicArray[i].capacityValues;
            for (int index = 0; index < newSmm.dynamicArray[position].sizeValues; index++)
                newSmm.dynamicArray[position].values[index] = dynamicArray[i].values[index];
        } else if (newSmm.dynamicArray[position].key == dynamicArray[i].key) {
            if (newSmm.dynamicArray[position].sizeValues + dynamicArray[i].sizeValues >=
                newSmm.dynamicArray[position].capacityValues)
                newSmm.resizeUpValues(dynamicArray[position].key);
            for (int index = 0; index < newSmm.dynamicArray[position].sizeValues; index++) {
                newSmm.dynamicArray[position].values[newSmm.dynamicArray[position].sizeValues] = dynamicArray[i].values[index];
                newSmm.dynamicArray[position].sizeValues++;
            }
            newSmm.dynamicArray[position].sizeValues += dynamicArray[i].sizeValues;
            newSmm.dynamicArray[position].capacityValues += dynamicArray[i].capacityValues;
        } else {
            int current = position;
            while (newSmm.next[current] != -1) {
                if (newSmm.dynamicArray[current].key == dynamicArray[i].key) {
                    if (newSmm.dynamicArray[current].sizeValues + dynamicArray[i].sizeValues >=
                        newSmm.dynamicArray[current].capacityValues)
                        newSmm.resizeUpValues(dynamicArray[current].key);
                    for (int index = 0; index < dynamicArray[current].sizeValues; index++) {
                        newSmm.dynamicArray[current].values[newSmm.dynamicArray[current].sizeValues] = dynamicArray[i].values[index];
                        newSmm.dynamicArray[current].sizeValues++;
                    }
                    newSmm.dynamicArray[position].capacityValues += dynamicArray[i].capacityValues;
                }
                current = newSmm.next[current];
            }
            if (newSmm.dynamicArray[position].key == dynamicArray[i].key) {
                if (newSmm.dynamicArray[position].sizeValues + dynamicArray[i].sizeValues >=
                    newSmm.dynamicArray[position].capacityValues)
                    newSmm.resizeUpValues(dynamicArray[position].key);
                for (int index = 0; index < dynamicArray[position].sizeValues; index++) {
                    newSmm.dynamicArray[position].values[newSmm.dynamicArray[position].sizeValues] = dynamicArray[i].values[index];
                    newSmm.dynamicArray[position].sizeValues++;
                }
                newSmm.dynamicArray[position].capacityValues += dynamicArray[i].capacityValues;
            }

            newSmm.dynamicArray[newSmm.firstEmpty].key = dynamicArray[i].key;
            newSmm.dynamicArray[newSmm.firstEmpty].sizeValues = dynamicArray[i].sizeValues;
            newSmm.dynamicArray[newSmm.firstEmpty].capacityValues = dynamicArray[i].capacityValues;
            for (int index = 0; index < dynamicArray[i].sizeValues; index++)
                newSmm.dynamicArray[position].values[index] = dynamicArray[i].values[index];
            newSmm.next[newSmm.firstEmpty] = -1;
            newSmm.next[current] = newSmm.firstEmpty;
            newSmm.changeFirstEmpty();
        }
        newSmm.sizeArray++;
        i++;
    }

    while (j < sortedMultiMap.capacity) {
        int position = abs(sortedMultiMap.dynamicArray[j].key) % newSmm.capacity;
        if (newSmm.dynamicArray[position].key == -1) {
            newSmm.dynamicArray[position].key = sortedMultiMap.dynamicArray[j].key;
            newSmm.dynamicArray[position].sizeValues = sortedMultiMap.dynamicArray[j].sizeValues;
            newSmm.dynamicArray[position].capacityValues = sortedMultiMap.dynamicArray[j].capacityValues;
            for (int index = 0; index < newSmm.dynamicArray[position].sizeValues; index++)
                newSmm.dynamicArray[position].values[index] = sortedMultiMap.dynamicArray[j].values[index];
        } else if (newSmm.dynamicArray[position].key == sortedMultiMap.dynamicArray[j].key) {
            if (newSmm.dynamicArray[position].sizeValues + sortedMultiMap.dynamicArray[j].sizeValues >=
                newSmm.dynamicArray[position].capacityValues)
                newSmm.resizeUpValues(newSmm.dynamicArray[position].key);
            for (int index = 0; index < newSmm.dynamicArray[position].sizeValues; index++) {
                newSmm.dynamicArray[position].values[newSmm.dynamicArray[position].sizeValues] = sortedMultiMap.dynamicArray[j].values[index];
                newSmm.dynamicArray[position].sizeValues++;
            }
            newSmm.dynamicArray[position].sizeValues += sortedMultiMap.dynamicArray[j].sizeValues;
            newSmm.dynamicArray[position].capacityValues += sortedMultiMap.dynamicArray[j].capacityValues;
        } else {
            int current = position;
            while (newSmm.next[current] != -1) {
                if (newSmm.dynamicArray[current].key == sortedMultiMap.dynamicArray[j].key) {
                    if (newSmm.dynamicArray[current].sizeValues + sortedMultiMap.dynamicArray[j].sizeValues >=
                        newSmm.dynamicArray[current].capacityValues)
                        newSmm.resizeUpValues(newSmm.dynamicArray[current].key);
                    for (int index = 0; index < sortedMultiMap.dynamicArray[j].sizeValues; index++) {
                        newSmm.dynamicArray[current].values[newSmm.dynamicArray[current].sizeValues] = sortedMultiMap.dynamicArray[j].values[index];
                        newSmm.dynamicArray[current].sizeValues++;
                    }
                    newSmm.dynamicArray[current].capacityValues += sortedMultiMap.dynamicArray[j].capacityValues;
                    break;
                }
                current = newSmm.next[current];
            }
            if (newSmm.dynamicArray[current].key == sortedMultiMap.dynamicArray[j].key) {
                if (newSmm.dynamicArray[current].sizeValues + sortedMultiMap.dynamicArray[j].sizeValues >=
                    newSmm.dynamicArray[current].capacityValues)
                    newSmm.resizeUpValues(newSmm.dynamicArray[current].key);
                for (int index = 0; index < sortedMultiMap.dynamicArray[j].sizeValues; index++) {
                    newSmm.dynamicArray[current].values[newSmm.dynamicArray[current].sizeValues] = sortedMultiMap.dynamicArray[j].values[index];
                    newSmm.dynamicArray[current].sizeValues++;
                }
                newSmm.dynamicArray[current].capacityValues += sortedMultiMap.dynamicArray[j].capacityValues;
            }else{
                newSmm.dynamicArray[newSmm.firstEmpty].key = sortedMultiMap.dynamicArray[j].key;
                newSmm.dynamicArray[newSmm.firstEmpty].sizeValues = sortedMultiMap.dynamicArray[j].sizeValues;
                newSmm.dynamicArray[newSmm.firstEmpty].capacityValues = sortedMultiMap.dynamicArray[j].capacityValues;
                for (int index = 0; index < sortedMultiMap.dynamicArray[i].sizeValues; index++)
                    newSmm.dynamicArray[newSmm.firstEmpty].values[index] = sortedMultiMap.dynamicArray[j].values[index];
                newSmm.next[newSmm.firstEmpty] = -1;
                newSmm.next[current] = newSmm.firstEmpty;
                newSmm.changeFirstEmpty();
            }
        }
        j++;
        newSmm.sizeArray++;
    }
    return newSmm;

}