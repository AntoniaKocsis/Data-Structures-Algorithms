#include <iostream>
#include <queue>
#include <stack>
#include <cassert>

using namespace std;
struct Node {
    int info;
    Node *left;
    Node *right;
    Node *parent;
};

class BinarySearchTree {
private:
    Node *root;
    stack<int> visited;
public:
    BinarySearchTree() {
        root = nullptr;
    }

    void insert(int v) {
        visited.push(v);
        Node *newNode = new Node;
        newNode->right = nullptr;
        newNode->left = nullptr;
        newNode->parent = nullptr;
        newNode->info = v;
        if (root == nullptr) {
            root = newNode;
            return;
        }
        if (root->info <= v && root->right == nullptr) {
            newNode->parent = root;
            root->right = newNode;
            return;
        }
        if (root->info > v && root->left == nullptr) {
            newNode->parent = root;
            root->left = newNode;
            return;
        }
        Node *current = root;
        Node *previous = nullptr;
        while (current != nullptr) {
            previous = current;
            if (current->info <= v) {
                current = current->right;
            } else {
                current = current->left;
            }
        }
        if (previous->info <= v) {
            newNode->parent = previous;
            previous->right = newNode;
        } else {
            newNode->parent = previous;
            previous->left = newNode;
        }

    }

    void levelOrder() {
        cout << "Level Order" << endl;
        queue<Node *> nodes;
        Node *current = root;
        if (root != nullptr) {
            nodes.push(root);
        }
        while (!nodes.empty()) {
            current = nodes.front();
            cout << current->info << " ";
            nodes.pop();
            if (current->left != nullptr) {
                nodes.push(current->left);
            }
            if (current->right != nullptr) {
                nodes.push(current->right);
            }
        }
    }

    void findMin() {
        Node *current = root;
        Node *previous;
        while (current != nullptr) {
            previous = current;
            current = current->left;
        }
        cout << "Minimum: " << previous->info << endl;

    }

    void inOrder() {
        cout << "Inorder" << endl;
        Node *current = root;
        stack<Node *> nodes;
        while (current != nullptr) {
            nodes.push(current);
            current = current->left;

        }
        while (!nodes.empty()) {
            current = nodes.top();
            cout << current->info << " ";
            nodes.pop();
            current = current->right;
            while (current != nullptr) {
                nodes.push(current);
                current = current->left;
            }
        }
    }

    Node *findSuccessor(int v) {

        Node *current = root;
        while (current != nullptr && current->info != v) {
            if (current->info < v)
                current = current->right;
            else
                current = current->left;
        }
        if (current == nullptr) {
            return nullptr;
        }
        if (current->right != nullptr) {
            current = current->right;
            Node *previous;
            while (current != nullptr) {
                previous = current;
                current = current->left;
            }
            return previous;
        } else {
            Node *p = current->parent;
            Node *c = current;
            while (p != nullptr && p->left != c) {
                c = p;
                p = c->parent;
            }
            return p;

        }
    }

    bool search(int v) {
        visited.push(v);
        if (root == nullptr)
            return false;
        Node *current = root;
        while (current != nullptr) {
            if (current->info == v)
                return true;
            else if (current->info < v) {
                current = current->right;
            } else {
                current = current->left;
            }
        }
        return false;
    }

    void remove(int v) {
        if (root == nullptr)
            return;
        Node *current = root;
        while (current != nullptr && current->info != v) {
            if (current->info < v) {
                current = current->right;
            } else
                current = current->left;
        }
        if (current == nullptr)
            return;
        Node *previous = current->parent;
        if (current->left == nullptr && current->right == nullptr) {
            if (previous == nullptr) {
                root = nullptr;
                delete current;
                return;
            }
            if (previous->left == current) {
                previous->left = nullptr;
                delete current;
                return;
            }
            if (previous->right == current) {
                previous->right = nullptr;
                delete current;
                return;
            }
        }
        if (current->left != nullptr && current->right == nullptr) {
            Node *child = current->left;
            if (previous == nullptr) {
                child->parent = nullptr;
                root = child;
                delete current;
                return;
            }
            if (previous->left == current) {
                previous->left = child;
                child->parent = previous;
                delete current;
                return;
            }
            if (previous->right == current) {
                previous->right = child;
                child->parent = previous;
                delete current;
                return;
            }

        }
        if (current->right != nullptr && current->left == nullptr) {
            Node *child = current->right;
            if (previous == nullptr) {
                child->parent = nullptr;
                root = child;
                delete current;
                return;
            }
            if (previous->left == current) {
                previous->left = child;
                child->parent = previous;
                delete current;
                return;
            }
            if (previous->right == current) {
                previous->right = child;
                child->parent = previous;
                delete current;
                return;
            }

        }
        if (current->left != nullptr && current->right != nullptr) {
            Node *successor = findSuccessor(current->info);
            current->info = successor->info;
            Node *successorParent = successor->parent;

            if (successor == successorParent->left) {
                successorParent->left = successor->right;
            } else {
                successorParent->right = successor->right;
            }

            if (successor->right != nullptr) {
                successor->right->parent = successorParent;
            }

            delete successor;
        }


    }

    void destroy(Node *node) {
        if (node != nullptr) {
            destroy(node->left);
            destroy(node->right);
        }
    }

    vector<int> recent() {
        vector<int> recentlyVisited;
        vector<bool> checked;
        vector<int> valuesFromStack;
        while(!visited.empty()){
            int current = visited.top();
            visited.pop();
        }

    }

    ~BinarySearchTree() {
        destroy(root);
    }


};

int main() {
    BinarySearchTree bst;

    return 0;
}
