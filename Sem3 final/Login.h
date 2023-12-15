#pragma once
#include"RingDHT.h"
#include"Node.h"
#include"File.h"
#include"BTreeNode.h"
#include<iostream>

class Login {
private:
    RingDHT* dht;
    Node* loggedInUser;  // Pointer to the currently logged-in user
    int bits;

public:
    Login(RingDHT* dht, int bits) : dht(dht), loggedInUser(nullptr), bits(bits) {}
    bool authenticateUser(int);
    Node* getLoggedInUser() const;
    Node* searchNode(int) const;
    void insertFile(File);
    void removeFile(string);
    int searchFile(string);
    void printBtree();
};