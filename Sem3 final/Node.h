#pragma once
#include<vector>
#include"BTree.h"

class Node
{
public:
    int data;
    Node* next;
    Node* prev;
    vector<Node*> routingTable;
    btree* Files_btree;

    Node(int value, int numBits);
};

