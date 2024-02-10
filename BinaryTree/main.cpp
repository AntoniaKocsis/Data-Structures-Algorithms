#include <iostream>
#include <queue>
#include <stack>

using namespace std;
struct Node {
    int info;
    Node *left;
    Node *right;
};

class BinaryTree {
private:
    Node *root;
public:
    BinaryTree() {
        root = nullptr;
    }

    void insert(int c) {
        Node *newNode = new Node;
        newNode->info = c;
        newNode->left = nullptr;
        newNode->right = nullptr;
        if (root == nullptr) {
            root = newNode;
            return;
        }
        queue<Node *> nodes;
        nodes.push(root);
        while (!nodes.empty()) {
            Node *current = nodes.front();
            nodes.pop();
            if (current->left == nullptr) {
                current->left = newNode;
                return;
            } else {
                nodes.push(current->left);
            }
            if (current->right == nullptr) {
                current->right = newNode;
                return;
            } else {
                nodes.push(current->right);
            }
        }
    }

    void levelOrder() {
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

    void preorder() {
        stack<Node *> nodes;
        Node *current = root;
        if (root != nullptr) {
            nodes.push(root);
        }
        while (!nodes.empty()) {
            current = nodes.top();
            cout << current->info << " ";
            nodes.pop();

            if (current->right != nullptr) {
                nodes.push(current->right);
            }
            if (current->left != nullptr) {
                nodes.push(current->left);
            }
        }


    }

    void inorder() {
        stack<Node *> nodes;
        Node *current = root;
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

    void postorder() {
        stack<Node *> nodes;
        Node *current = root;
        while (current != nullptr) {
            if (current->right != nullptr)
                nodes.push(current->right);
            nodes.push(current);
            current = current->left;
        }
        while (!nodes.empty()) {
            current = nodes.top();
            nodes.pop();
            if (current->right != nullptr && !nodes.empty() && current->right == nodes.top()) {
                nodes.pop();
                nodes.push(current);
                current = current->right;

            } else {
                cout << current->info << " ";
                current = nullptr;
            }
            while (current != nullptr) {
                if (current->right != nullptr)
                    nodes.push(current->right);
                nodes.push(current);
                current = current->left;
            }
        }

    }

};

int main() {
    BinaryTree tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(9);
    tree.levelOrder();
    cout << endl;
    tree.preorder();
    cout << endl;
    tree.inorder();
    cout << endl;
    tree.postorder();

    return 0;
}
