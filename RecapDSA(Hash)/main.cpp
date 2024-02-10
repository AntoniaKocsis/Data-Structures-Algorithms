#include <iostream>
//#include <cstdlib>
using namespace std;
struct Node {
    int info;
    Node *next;
};

class SeparateChaining {
private:
    int capacity;
    Node **hashtable;

public:
    SeparateChaining(int tableSize) : capacity(tableSize) {
        hashtable = new Node *[capacity];
        for (int i = 0; i < capacity; i++)
            hashtable[i] = nullptr;
    }

    int hashFunction(int value) {
        return abs(value) % capacity;
    }

    void insert(int value) {
        int position = hashFunction(value);
        Node *newNode = new Node;
        newNode->info = value;
        newNode->next = nullptr;
        if (hashtable[position] == nullptr) {
            hashtable[position] = newNode;
        } else {
            newNode->next = hashtable[position];
            hashtable[position] = newNode;
        }
    }

    void remove(int value) {
        int position = hashFunction(value);
        Node *current = hashtable[position];
        if (current->info == value) {
            hashtable[position] = hashtable[position]->next;
            delete current;
            return;
        }
        Node *previous = nullptr;
        while (current != nullptr && current->info != value) {
            previous = current;
            current = current->next;
        }
        if (current == nullptr)
            return;
        previous->next = current->next;

    }

    void display() {
        for (int i = 0; i < capacity; i++) {
            cout << "Position " << i << ": ";
            Node *current = hashtable[i];
            while (current != nullptr) {
                cout << current->info << " --> ";
                current = current->next;
            }
            cout << "NIL" << endl;
        }

    }

    // Destructor to clean up memory
    ~SeparateChaining() {
        for (int i = 0; i < capacity; i++) {
            Node *current = hashtable[i];
            Node *next = nullptr;
            while (current != nullptr) {
                next = current->next;
                delete current;
                current = next;
            }
        }
        delete[] hashtable;
    }
};

void separateChaining() {

    SeparateChaining hashtable(10);

    hashtable.insert(5);
    hashtable.insert(16);
    hashtable.insert(24);
    hashtable.insert(35);

    hashtable.display();
    hashtable.remove(5);
    hashtable.remove(35);
    cout << endl;
    hashtable.display();
}
struct MNode{
    int value;
    int positionVisited;
};
class OpenAdressing {
private:
    int capacity;
    int length;
    MNode *hashTable;
    float c1, c2;
    int lastPositionVisited;
public:
    OpenAdressing() {
        capacity = 10;
        length = 0;
        lastPositionVisited = 0;
        c1 = 0.5;
        c2 = 0.5;
        hashTable = new MNode[capacity];
        for (int i = 0; i < capacity; i++) {
            hashTable[i].value = 0;
            hashTable[i].positionVisited = -1;
        }
    }

    int hashFunctionLinearProbing(int value, int i) {
        return ((abs(value) % capacity) + i) % capacity;
    }

    int hashFunctionQuadratic(int value, int i) {
        return ((abs(value) % capacity) + int(c1 * i) + int(c2 * i * i)) % capacity;

    }

    int doubleHashing(int value, int i) {
        int firstH = abs(value) % capacity;
        int secondH = abs(value) / capacity;
        return (firstH + i * secondH) % capacity;
    }

    void insert(int value, string probing) {
        int position;
        if (probing == "linear") {
            position = hashFunctionLinearProbing(value, 0);
        } else if (probing == "quadratic") {
            position = hashFunctionQuadratic(value, 0);
        } else {
            position = doubleHashing(value, 0);

        }
        if (hashTable[position].value == 0) {
            hashTable[position].value = value;
            length++;
            return;
        }
        int current = hashFunctionLinearProbing(value, 1);
        int numberOfTries = 2;
        while (hashTable[current].value != 0 && numberOfTries < capacity) {
            current = hashFunctionLinearProbing(value, numberOfTries);
            numberOfTries++;
        }
        hashTable[current].value = value;
    }

    bool search(int value){
        int current = hashFunctionLinearProbing(value,0);
        if(hashTable[current].value == 0)
            return false;
        int i = 0;
        while(hashTable[current].value != value && i<capacity&& hashTable[current].value != 0){
            current = hashFunctionLinearProbing(value,i);
            i++;
        }
        if(hashTable[current].value == 0)
            return false;
        return true;
    }

    void printHash() {
        for (int i = 0; i < capacity; i++)
            cout << i << "  ";
        cout << endl;
        for (int i = 0; i < capacity; i++) {
            cout << hashTable[i].value << "  ";
        }
    }
};

void linearProbing() {
    OpenAdressing h1;
    h1.insert(5, "linear");
    h1.insert(4, "linear");
    h1.insert(15, "linear");
    h1.insert(3, "linear");
    h1.insert(14, "linear");
    h1.insert(9, "linear");
    h1.insert(19, "linear");
    h1.insert(29, "linear");
    h1.printHash();
}

void otherProbing() {
    OpenAdressing h1;
    h1.insert(9, "quadratic");
    h1.insert(19, "quadratic");
    h1.insert(8, "quadratic");
    h1.insert(18, "quadratic");
    h1.printHash();
    cout << endl;
    OpenAdressing h2;
    h2.insert(9, "");
    h2.insert(19, "");
    h2.insert(8, "");
    h2.insert(18, "");
    h2.printHash();
}
int main() {
    OpenAdressing h1;
    h1.insert(5, "linear");
    h1.insert(4, "linear");
    h1.insert(15, "linear");
    h1.insert(3, "linear");
    h1.insert(14, "linear");
    h1.insert(9, "linear");
    h1.insert(19, "linear");
    h1.insert(29, "linear");
    h1.printHash();
    cout<<endl;
    cout<<h1.search(29);
    return 0;
}
