#include "binary-search-tree.h"
#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

BinarySearchTree::Node::Node(DataType newval) {
    val = newval;
    left = NULL;
    right = NULL;
}

int BinarySearchTree::getNodeDepth(Node* n) const {
    if (n == NULL)
        return -1;
    if (n->left == NULL && n->right == NULL)
        return 0;
    else {
        return 1 + ::max(getNodeDepth(n->left), getNodeDepth(n->right));
    }
}

BinarySearchTree::BinarySearchTree() {
    root_ = NULL;
    size_ = 0;
}

BinarySearchTree::~BinarySearchTree() {
    if (root_ != NULL){
        stack <Node*> S;
        S.push(root_);

        while (!S.empty()) {
            Node *P = S.top();
            S.pop();

            if (P->left != NULL)
                S.push(P->left);
            if (P->right != NULL)
                S.push(P->right);

            delete P; // using post-order traversal algorithm
        }
    }
}

unsigned int BinarySearchTree::size() const {
    return size_;
}

BinarySearchTree::DataType BinarySearchTree::max() const {
    Node *temp = root_;
    while (temp->right != NULL){
        temp = temp->right;
    }
    return temp->val; // assuming temp will never be null, so tree will never be empty
}

BinarySearchTree::DataType BinarySearchTree::min() const {
    Node *temp = root_;
    while (temp->left != NULL){
        temp = temp->left;
    }
    return temp->val; // assuming temp will never be null, so tree will never be empty
}

int BinarySearchTree::height() const {
    return getNodeDepth(root_);
}

void BinarySearchTree::print() const { //BFT print
    if (root_ == NULL){
        cout << "Tree is empty!" << endl;
        return;
    }
    queue <Node*> Q;
    Q.push(root_);
    while (!Q.empty()){
        Node* P = Q.front();
        Q.pop();
        cout << P->val << " ";
        if (P->left != NULL)
            Q.push(P->left);
        if (P->right != NULL)
            Q.push(P->right);
    }
}

bool BinarySearchTree::exists(DataType val) const {
    Node* current_node = root_;
    while (current_node != NULL){
        if (current_node->val == val)
            return true;
        else if (val < current_node->val ){
            current_node = current_node->left;
        }
        else // val > current->val
            current_node = current_node->right;
    }
    return false;
}

BinarySearchTree::Node* BinarySearchTree::getRootNode() {
    return root_;
}

BinarySearchTree::Node** BinarySearchTree::getRootNodeAddress() {
    return &root_;
}

bool BinarySearchTree::insert(DataType val) {
    Node* new_node = new Node(val);

    if (root_ == NULL){
        root_ = new_node;
        size_++;
        return true;
    }
    Node* current_node = root_;
    while (current_node != NULL){
        if (current_node->val == val)
            return false;
        else if (val < current_node->val ){
            if(current_node->left == NULL){
                current_node->left = new_node;
                size_++;
                return true;
            }
            else
                current_node = current_node->left;
        }
        else // val > current->val
            if(current_node->right == NULL){
                current_node->right = new_node;
                size_++;
                return true;
            }
            else
                current_node = current_node->right;
    }
    return false;
}

bool BinarySearchTree::remove(DataType val) {
    if (root_ == NULL)
        return false;

    // Find val in BST
    Node* current_node = root_;
    Node* parent_node = NULL;
    bool isLeftChild = false;
    bool found = false;

    while (current_node != NULL){
        if (current_node->val == val){
            found = true;
            break;
        }
        else if(val < current_node->val){
            parent_node = current_node;
            current_node = current_node->left;
            isLeftChild = true;
        }
        else {
            parent_node = current_node;
            current_node = current_node->right;
            isLeftChild = false;
        }
    }
    if(!found)
        return false;

    // Val is a leaf node
    if (current_node->right == NULL && current_node->left == NULL){
        if (current_node == root_){
            delete root_;
            root_ = NULL;
            size_--;
            return true;
        }
        delete current_node;
        if (isLeftChild)
            parent_node->left = NULL;
        else
            parent_node->right = NULL;
        size_--;
        return true;
    }

    // Val has one child node (right)
    if(current_node->right != NULL && current_node->left == NULL){
        if (current_node == root_){
            root_ = current_node -> right;
        }
        else {
            if (isLeftChild)
                parent_node->left = current_node->right;
            else
                parent_node->right = current_node->right;
        }
        delete current_node;
        size_--;
        return true;
    }

    // Val has one child node (left)
    if(current_node->right == NULL && current_node->left != NULL) {
        if (current_node == root_){
            root_ = current_node -> left;
        }
        else {
            if (isLeftChild)
                parent_node->left = current_node->left;
            else
                parent_node->right = current_node->left;
        }
        delete current_node;
        size_--;
        return true;
    }

    // Val has two child nodes (predecessor)
    if(current_node->right != NULL && current_node->left != NULL){
        Node* predecessor_parent = current_node;
        Node* predecessor = current_node->left;
        isLeftChild = true;

        while(predecessor->right != NULL){
            predecessor_parent = predecessor;
            predecessor = predecessor->right;
            isLeftChild = false;
        }
        current_node->val = predecessor->val; // swap values
        if (predecessor->left == NULL){ // leaf node
            if (isLeftChild)
                predecessor_parent->left = NULL;
            else
                predecessor_parent->right = NULL;
        }
        else {
            if (isLeftChild)
                predecessor_parent->left = predecessor->left;
            else
                predecessor_parent->right = predecessor->left;
        }
        delete predecessor;
        size_--;
        return true;
    }
    return false;
}
