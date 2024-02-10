#include <iostream>
#include <queue>
#include <stack>

using namespace std;
struct Node {
    int info;
    Node *right;
    Node *left;
    Node *parent;
};

class BST {
private:
    Node *root;
public:
    BST() {
        root = nullptr;
    }


    void insert(int v) {
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

    Node *findMin() {
        Node *current = root;
        Node *prev = nullptr;
        while (current != nullptr) {
            prev = current;
            current = current->left;
        }
        return prev;
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

    void levelOrder() {
        cout << "Level Order" << endl;
        if (root == nullptr)
            return;
        queue<Node *> nodes;
        nodes.push(root);
        while (!nodes.empty()) {
            Node *current = nodes.front();
            cout << current->info << " ";
            nodes.pop();
            if (current->left != nullptr)
                nodes.push(current->left);
            if (current->right != nullptr)
                nodes.push(current->right);
        }
        cout << endl;
    }

    void inorder() {
        cout << "In Order" << endl;
        if (root == nullptr)
            return;
        Node *current = root;
        stack<Node *> nodes;
        while (current != nullptr) {
            nodes.push(current);
            current = current->left;
        }
        while (!nodes.empty()) {
            current = nodes.top();
            nodes.pop();
            cout << current->info << " ";
            current = current->right;
            while (current != nullptr) {
                nodes.push(current);
                current = current->left;
            }
        }
        cout << endl;
    }

    void successor(int v) {
        Node *current = findSuccessor(v);
        cout << current->info;
    }

    void remove(int v) {
        Node *current = root;
        Node *previous;
        while (current != nullptr && current->info != v) {
            previous = current;
            if (current->info < v)
                current = current->right;
            else
                current = current->left;
        }
        if (current == nullptr) {
            return;
        }
        if (current->right == nullptr && current->left == nullptr) {
            if (previous == nullptr) {
                root = nullptr;
            }
            delete current;
            return;
        }
        if (current->right != nullptr && current->left == nullptr) {
            Node *child = current->right;
            child->parent = previous;
            if (previous->left == current) {
                previous->left = child;
            } else if (previous->right == current) {
                previous->right = child;
            }
            delete current;
            return;
        }
        if (current->left != nullptr && current->right == nullptr) {
            Node *child = current->left;
            child->parent = previous;
            if (previous->left == current) {
                previous->left = child;
            } else if (previous->right == current) {
                previous->right = child;
            }
            delete current;
            return;
        }
        if (current->left != nullptr && current->right != nullptr) {
            Node *successor = findSuccessor(current->info);
            Node *successorParent = successor->parent;
            current->info = successor->info;

            if (successorParent->left == successor) {
                successorParent->left = successor->right;
            } else if (successorParent->right == successor) {
                successorParent->right = successor->right;
            }

            if (successor->right != nullptr) {
                successor->right->parent = successorParent;
            }
            delete successor;
        }

    }
};

int main() {
    BST tree;
    tree.insert(18);
    tree.insert(19);
    tree.insert(15);
    tree.insert(17);
    tree.insert(13);
    tree.levelOrder();
    tree.inorder();
    tree.insert(16);
    tree.remove(15);
    tree.inorder();
    return 0;
}
