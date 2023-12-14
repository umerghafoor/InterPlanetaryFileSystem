#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Node
{
public:
    int data;
    Node* next;
    Node* prev;
    vector<Node*> routingTable;

    Node(int value, int numBits);
};

class RingDHT
{
private:
    Node* head;
    int numBits; // Number of bits for the routing table

public:
    RingDHT(int bits);

    // Function to insert a node in order and update the routing table
    void insertInOrder(int value);

    // Function to update the routing table for a given node
    void updateRoutingTable(Node* node);

    // Helper function to find the successor for routing table entries
    Node* findSuccessor(Node* node, int index);
    // Function to delete a node with a specific value
    void deleteNode(int value);

    // Function to search for a node with a specific value
    Node* searchNode(int value);

    // Helper function to update routing tables for all nodes in the list
    void updateAllRoutingTables();


    // Function to display the double circular linked list with routing tables
    void display();

    int getIdentifierBits();

};

class Login {
private:
    RingDHT* dht;
    Node* loggedInUser;  // Pointer to the currently logged-in user

public:
    Login(RingDHT* dht) : dht(dht), loggedInUser(nullptr) {}
    bool authenticateUser(int);
    Node* getLoggedInUser() const;
    Node* searchNode(int) const;
    void insertFile(int file);
    void removeFile(int file);
    int searchFile(int file);
};




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

