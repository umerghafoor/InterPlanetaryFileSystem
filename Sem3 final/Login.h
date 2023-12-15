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

public:
    Login(RingDHT* dht) : dht(dht), loggedInUser(nullptr) {}
    bool authenticateUser(int);
    Node* getLoggedInUser() const;
    Node* searchNode(int) const;
    void insertFile(File file);
    void removeFile(int file);
    int searchFile(int file);
};