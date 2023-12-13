#pragma once
#include<iostream>
#include<string>

struct TreeNode {
    Computer computer;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const Computer& comp) : computer(comp), left(nullptr), right(nullptr) {}
};

class Computer {
public:
    std::string name;

    Computer() : name("") {}

    explicit Computer(const std::string& computerName) : name(computerName) {}

    // Binary Search Tree (BST) related members and methods
private:
    

    TreeNode* root;

public:
    // Constructor for initializing the BST
    Computer(const std::string& computerName, const std::string& rootName) : name(computerName), root(nullptr) {
        root = new TreeNode(Computer(rootName));
    }

    // Function to insert a computer into the BST
    void insert(const Computer& comp) {
        root = insertRecursive(root, comp);
    }

    // Function to search for a computer in the BST
    bool search(const std::string& compName) const {
        return searchRecursive(root, compName);
    }

    // Function for in-order traversal of the BST
    void inOrderTraversal() const {
        inOrderTraversalRecursive(root);
    }

    // Destructor to clean up the BST
    ~Computer() {
        destroyTree(root);
    }

private:
    // Helper function for recursive insertion into the BST
    TreeNode* insertRecursive(TreeNode* currentNode, const Computer& comp) {
        if (currentNode == nullptr) {
            return new TreeNode(comp);
        }

        if (comp.name < currentNode->computer.name) {
            currentNode->left = insertRecursive(currentNode->left, comp);
        }
        else if (comp.name > currentNode->computer.name) {
            currentNode->right = insertRecursive(currentNode->right, comp);
        }

        return currentNode;
    }

    // Helper function for recursive search in the BST
    bool searchRecursive(TreeNode* currentNode, const std::string& compName) const {
        if (currentNode == nullptr) {
            return false;
        }

        if (compName == currentNode->computer.name) {
            return true;
        }
        else if (compName < currentNode->computer.name) {
            return searchRecursive(currentNode->left, compName);
        }
        else {
            return searchRecursive(currentNode->right, compName);
        }
    }

    // Helper function for in-order traversal of the BST
    void inOrderTraversalRecursive(TreeNode* currentNode) const {
        if (currentNode != nullptr) {
            inOrderTraversalRecursive(currentNode->left);
            std::cout << currentNode->computer.name << " ";
            inOrderTraversalRecursive(currentNode->right);
        }
    }

    // Helper function to clean up the BST
    void destroyTree(TreeNode* currentNode) {
        if (currentNode != nullptr) {
            destroyTree(currentNode->left);
            destroyTree(currentNode->right);
            delete currentNode;
        }
    }
};

class Node {
public:
    int data;
    bool state;
    Node* next;
    Node* prev;
    Node** fingerTable;
    Computer computer;

    Node() : data(-1), next(nullptr), prev(nullptr), fingerTable(nullptr), state(false) {}
    Node(int value, int bits, const std::string& computerName)
        : data(value), next(nullptr), prev(nullptr), computer(computerName), state(false)
    {
        fingerTable = new Node * [bits];
        for (int i = 0; i < bits; ++i)
        {
            fingerTable[i] = nullptr;
        }
    }

    ~Node() {
        delete[] fingerTable;
    }
};

class RingDHT {
private:
    int identifierBits;
    int size;
    Node* head;
    Computer loggedInComputer;

public:
    RingDHT(int bits) : identifierBits(bits), size(1 << bits) {
        head = nullptr;
        initializeRing();
        initializeFingerTables();
    }

    int getSize();
    int getIdentifierBits();
    void initializeRing();
    void displayRing() const;
    Node* findNode(int) const;
    void initializeFingerTables();
    Node* findNextNode(int) const;
    void addComputerToNode(int, const std::string&);
    void deleteComputerFromNode(int);
    void updateFingerTables();

    ~RingDHT() {
        if (head) {
            Node* current = head;
            Node* temp;
            do {
                temp = current->next;
                delete current;
                current = temp;
            } while (current != head);
        }
    }
};

class Login {
private:
    RingDHT* dht;
    Node* loggedInUser;  // Pointer to the currently logged-in user

public:
    Login(RingDHT* dht) : dht(dht), loggedInUser(nullptr) {}
    bool authenticateUser(int, const std::string&);
    Node* getLoggedInUser() const;
    Node* searchNode(int) const;
    void insertValuesIntoFingerTables(RingDHT&);
};