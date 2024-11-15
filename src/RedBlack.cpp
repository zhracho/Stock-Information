#include "RedBlack.h"
#include <iostream>
using namespace std;


void RedBlack::insert(Stock stonk) {
    this->root = insertHelper(this->root, stonk, nullptr);
}

RedBlack::Node* RedBlack::insertHelper(RedBlack::Node *node, Stock stonk, RedBlack::Node *prev){
    if(this->root == nullptr){
        Node* stock = new Node(stonk);
        //Set to black;
        stock->color = 0;
        return stock;
    }


    if(node == nullptr) {
        Node* stock = new Node(stonk);
        stock->parent = prev;
        node = stock;
        //return node;
    }
    //Binary Search Tree implementation and initial placement
    else if(stonk.adjClose < node->adjClose) {
        node->left = insertHelper(node->left, stonk, node);
    }
    else if (stonk.adjClose > node->adjClose) {
        node->right = insertHelper(node->right, stonk, node);
    }

    node->height = 1 + max(node->left ? node->left->height : 0, node->right ? node->right->height : 0);
    if(node->parent != nullptr)
        node->parent->height = 1 + max(node->parent->left ? node->parent->left->height : 0, node->parent->right ? node->parent->right->height : 0);

//    cout << node->adjClose << " " << node->height<< endl;
    if(node == this->root){
        this->root->color = 0;
        return node;
    }

    if(prev->color == 0){
        return node;
    }


    Node* grandpa = prev->parent;
    if(grandpa == nullptr){
        return node;
    }

    bool isRight = false;
    if(grandpa->right == prev){
        isRight = true;
    }

    grandpa->height = 1 + max(grandpa->left ? grandpa->left->height : 0, grandpa->right ? grandpa->right->height : 0);

    cout <<"ans" <<grandpa->adjClose << grandpa->height<<endl;
    Node* uncle = isRight ? grandpa->left: grandpa->right;

    //Error catching to make sure we are not accessing a nullptr value
    int leftHeight = (grandpa->left ? grandpa->left->height : 0);
    int rightHeight = (grandpa->right ? grandpa->right->height : 0);

    //Calculate the balance factor which will be useful for balancing and calling rotations
    int balanceFactor = leftHeight - rightHeight;

    if(uncle && uncle->color == 1){
        uncle->color = 0;
        prev->color = 0;
        grandpa->color = 1;

    }else{
// grandparent left - grandpa right
        cout << node->adjClose << " " << balanceFactor << endl;
        if(balanceFactor == -2){
            //Get the respective heights of the tree's children
            int childLeftHeight = grandpa->right->left ? grandpa->right->left->height : 0;
            int childRightHeight = grandpa->right->right ? grandpa->right->right->height : 0;

            //If the balance factor of the children is 1 we need a left right rotation
            if(childLeftHeight - childRightHeight == 1){
                node = rotateRightLeft(node);
                updateHeight(node);
            }else{
                node = rotateLeft(node);
                updateHeight(node);
            }
        }else if(balanceFactor == 2){
            //Get the respective heights of the tree's children
            int childLeftHeight = grandpa->left->left ? grandpa->left->left->height : 0;
            int childRightHeight = grandpa->left->right ? grandpa->left->right->height : 0;

            //If the balance factor of the children is -1 we need a right left rotation
            if(childLeftHeight - childRightHeight == -1){
                node = rotateLeftRight(node);
                updateHeight(node);
            }else{
                node = rotateRight(node);
                updateHeight(node);
            }
        }
    }

    return node;

}

RedBlack::Node *RedBlack::rotateLeft(RedBlack::Node* node) {
    //Get the right node
    Node* rightChild = node->right;
    //Set the current right child to the right subtree's left child
    node->right = rightChild->left;
    //The right subtree's left child becomes the node
    rightChild->left = node;
    return rightChild;
}

RedBlack::Node *RedBlack::rotateRight(RedBlack::Node* node) {
    //Get the left node
    Node* leftChild = node->left;
    //Set the current left child to the left subtree's right child
    node->left = leftChild->right;
    //The left subtree's right child becomes the node
    leftChild->right = node;
    return leftChild;
}

RedBlack::Node *RedBlack::rotateLeftRight(RedBlack::Node* node) {
    //Perform the left rotation and then the right rotation
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

RedBlack::Node *RedBlack::rotateRightLeft(RedBlack::Node* node) {
    //Perform the right rotation and then the left rotation
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

int RedBlack::updateHeight(RedBlack::Node* node) {
    //Updates the height of our tree for insertion in constant time
    //All of these statements use ternary operations to check for nullptrs
    node->left->height = 1 + max(node->left->left ? node->left->left->height : 0,
                                 node->left->right ? node->left->right->height : 0);
    node->right->height = 1 + max(node->right->left ? node->right->left->height : 0,
                                  node->right->right ? node->right->right->height : 0);
    node->height = 1 + max(node->left->height, node->right->height);

    return node->height;

}