#include <cassert>
#include "SLL.h"
#include "DLL.h"
#include "BinaryTree.h"
#include "BinarySearchTree.h"
#include "SLLA.h"
#include "DLLA.h"
#include "CSLL.h"
void testSLL() {
    SLL sll;
    sll.insert(2);
    sll.insert(3);
    sll.insert(4);
    sll.insert(6);
    sll.printList();
    sll.remove(4);
    sll.printList();
    assert(sll.search(3) == true);
    sll.remove(2);
    sll.remove(3);
    sll.remove(6);
    sll.printList();
}

void testDLL() {
    DLL dll;
    dll.insert(2);
    dll.insert(3);
    dll.insert(4);
    dll.insert(6);
    dll.printList();
    dll.remove(2);
    dll.remove(6);
    dll.remove(4);
    dll.printList();
}

void testBT() {
    BinaryTree tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(9);
    tree.levelOrder();
    tree.preOrder();
    tree.inOrder();
    tree.postOrder();

}

void testBST() {
    BinarySearchTree bst;
    bst.insert(11);
    bst.insert(7);
    bst.insert(20);
    bst.insert(2);
    bst.insert(9);
    bst.insert(19);
    bst.insert(25);
    bst.insert(15);
    bst.insert(13);
    bst.insert(17);
    bst.insert(4);
    bst.levelOrder();
    bst.inOrder();
    bst.remove(4);
    bst.inOrder();
}

void testSLLA() {
    SLLA slla;
    slla.insert(2);
    slla.insert(3);
    slla.insert(4);
    slla.insert(5);
    slla.remove(3);
    assert(slla.search(3) == false);
}
void testDLLA(){

    DLLA dlla;
    dlla.add(1);
    dlla.add(3);
    dlla.add(5);
    dlla.add(7);
    dlla.remove(3);
}
void fromPostAndIn(){

    BinaryTree tree;
    vector<int> inorder  = {1,3,9,5,7};
    vector<int> postorder = {1,9,3,7,5};
    vector<int> preorder = {5,3,1,9,7};
    tree.buildTreePostIn(postorder,inorder);
    tree.levelOrder();
}
int main() {

    return 0;
}
