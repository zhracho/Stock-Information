#pragma once
#include <string>
#include "Stock.h"
class RedBlack {
    struct Node {
        string stockName;
        string date;
        double adjClose;
        int totalVolume;
        int color;
        int height = 1;

        Node* left;
        Node* right;
        Node* parent;

        Node(string stockName, string date, double adjClose, int totalVolume) {
            this->stockName = stockName;
            this->date = date;
            this->adjClose = adjClose;
            this->totalVolume = totalVolume;
            //1 is red
            this->color = 1;

            this->left = nullptr;
            this->right = nullptr;
            this->parent = nullptr;

        }

        Node(Stock stonk){
            this->stockName = stonk.stockName;
            this->date = stonk.date;
            this->adjClose = stonk.adjClose;
            this->totalVolume = stonk.totalVolume;
            //1 is red
            this->color = 1;

            this->left = nullptr;
            this->right = nullptr;
            this->parent = nullptr;
        }

    };
private:
    Node* root = nullptr;
    Node* insertHelper(Node* node, Stock stonk, Node* prev);
    Node* rotateRight(Node* node);
    Node* rotateLeft(Node* node);
    Node* rotateLeftRight(Node* node);
    Node* rotateRightLeft(Node* node);
    int updateHeight(Node* node);
    Node* balanceHelper(Node* node, Stock stonk);
public:
    void insert(Stock stonk);

};



