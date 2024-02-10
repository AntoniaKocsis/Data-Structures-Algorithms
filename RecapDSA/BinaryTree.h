#pragma once

#include <queue>
#include <stack>

struct TreeNode {
    int info;
    TreeNode *right;
    TreeNode *left;
};

class BinaryTree {
private:
    TreeNode *root;
public:
    BinaryTree() {
        root = nullptr;
    }

    void insert(int e) {
        TreeNode *newNode = new TreeNode;
        newNode->info = e;
        newNode->left = nullptr;
        newNode->right = nullptr;
        if (root == nullptr) {
            root = newNode;
            return;
        }
        queue < TreeNode * > nodes;
        nodes.push(root);
        while (!nodes.empty()) {
            TreeNode *current = nodes.front();
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
        cout << "Level Order" << endl;
        if (root == nullptr)
            return;
        queue < TreeNode * > nodes;
        if (root != nullptr)
            nodes.push(root);
        while (!nodes.empty()) {
            TreeNode *current = nodes.front();
            cout << current->info << " ";
            nodes.pop();
            if (current->left != nullptr)
                nodes.push(current->left);
            if (current->right != nullptr)
                nodes.push(current->right);
        }
        cout << endl;
    }

    void preOrder() {
        cout << "Preorder" << endl;
        if (root == nullptr)
            return;
        stack < TreeNode * > nodes;
        nodes.push(root);
        while (!nodes.empty()) {
            TreeNode *current = nodes.top();
            cout << current->info << " ";
            nodes.pop();
            if (current->right != nullptr)
                nodes.push(current->right);
            if (current->left != nullptr)
                nodes.push(current->left);
        }
        cout << endl;
    }

    void inOrder() {
        cout << "In Order" << endl;
        if (root == nullptr)
            return;
        stack < TreeNode * > nodes;
        TreeNode *current = root;
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
        cout << endl;
    }

    void postOrder() {
        cout << "Post Order" << endl;
        if (root == nullptr)
            return;
        stack < TreeNode * > nodes;
        TreeNode *current = root;
        while (current != nullptr) {
            if (current->right != nullptr)
                nodes.push(current->right);
            nodes.push(current);
            current = current->left;
        }
        while (!nodes.empty()) {
            current = nodes.top();
            nodes.pop();
            if (current->right != nullptr && !nodes.empty() && nodes.top() == current->right) {
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
        cout << endl;
    }

    TreeNode *
    buildTreeHelperPostIn(vector<int> postOrder, vector<int> inOrder, int &postIndex, int startIn, int endIn) {
        if (startIn > endIn)
            return nullptr;

        TreeNode *newNode = new TreeNode;
        newNode->right = nullptr;
        newNode->left = nullptr;
        newNode->info = postOrder[postIndex];

        postIndex--;
        int rootIndex;
        for (int i = startIn; i <= endIn; i++) {
            if (inOrder[i] == newNode->info) {
                rootIndex = i;
                break;
            }
        }
        newNode->right = buildTreeHelperPostIn(postOrder, inOrder, postIndex, rootIndex + 1, endIn);
        newNode->left = buildTreeHelperPostIn(postOrder, inOrder, postIndex, startIn, rootIndex - 1);
        return newNode;
    }

    void buildTreePostIn(vector<int> postOrder, vector<int> inOrder) {
        int postIndex = postOrder.size() - 1;
        root = buildTreeHelperPostIn(postOrder, inOrder, postIndex, 0, inOrder.size() - 1);
    }
    TreeNode* buildTreeHelper(vector<int> preorder, vector<int> inorder, int preIndex,int startIn,int endIn){
        if (startIn > endIn)
            return nullptr;

        TreeNode *newNode = new TreeNode;
        newNode->right = nullptr;
        newNode->left = nullptr;
        newNode->info = preorder[preIndex];
        preIndex++;
        int rootIndex;
        for(int i = startIn;i<=endIn;i++)
            if(inorder[i] == newNode->info){
                rootIndex = i;
                break;
            }

        newNode->right = buildTreeHelper(preorder,inorder,preIndex,rootIndex+1,endIn);
        newNode->left = buildTreeHelper(preorder,inorder,preIndex,startIn,rootIndex -1);
        return newNode;

    }
    void buildTree(vector<int> preorder, vector<int> inorder) {
        int preIndex = 0;
        root = buildTreeHelper(preorder,inorder,preIndex,0,inorder.size()-1);
    }
};