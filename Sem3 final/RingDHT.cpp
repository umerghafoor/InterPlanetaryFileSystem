#include "RingDHT.h"

RingDHT::RingDHT(int bits) : head(nullptr), numBits(bits)
{
}

// Function to insert a node in order and update the routing table
void RingDHT::insertInOrder(int value) {
    Node* newNode = new Node(value, numBits);

    if (head == nullptr || value <= head->data)
    {
        // If the list is empty or the value is less than or equal to the head's data,
        // insert at the beginning
        if (head == nullptr)
        {
            head = newNode;
            head->next = head;
            head->prev = head;
        }
        else {
            Node* last = head->prev;
            last->next = newNode;
            newNode->prev = last;
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }

    }
    else
    {
        // Otherwise, find the correct position to insert the new node
        Node* current = head->next;

        while (current != head && value > current->data)
        {
            current = current->next;
        }

        // Insert the new node before the current node
        Node* prevNode = current->prev;

        prevNode->next = newNode;
        newNode->prev = prevNode;
        newNode->next = current;
        current->prev = newNode;

        // Update routing table for the new node
    }

    Node* c = head;
    do
    {
        updateRoutingTable(c);
        for (int i = 0; i < numBits; ++i)
        {
            std::cout << c->routingTable[i]->data << ' ';
        }
        std::cout << '\n';
        c = c->next;
    } while (c != head);
    std::cout << '\n';
}

// Function to update the routing table for a given node
void RingDHT::updateRoutingTable(Node* node)
{
    for (int i = 0; i < numBits; ++i)
    {
        Node* successor = findSuccessor(node, i);
        node->routingTable[i] = successor;
    }
}

// Helper function to find the successor for routing table entries
Node* RingDHT::findSuccessor(Node* node, int index) {
    int target = (node->data + (1 << index)) % (1 << numBits);
    Node* current = head;

    while (current->next != head && (current->next->data % (1 << numBits)) < target)
    {
        current = current->next;
    }

    return current->next;
}
// Function to delete a node with a specific value
void RingDHT::deleteNode(int value) {
    if (head == nullptr) {
        cout << "List is empty. Cannot delete." << endl;
        return;
    }

    Node* current = head;
    Node* nodeToDelete = nullptr;

    // Find the node with the specified value
    do {
        if (current->data == value) {
            nodeToDelete = current;
            break;
        }
        current = current->next;
    } while (current != head);

    // If the node is found, delete it
    if (nodeToDelete != nullptr) {
        if (nodeToDelete == head) {
            // If the node to delete is the head, update the head
            head = head->next;
        }

        // Adjust the pointers of neighboring nodes
        nodeToDelete->prev->next = nodeToDelete->next;
        nodeToDelete->next->prev = nodeToDelete->prev;

        // Delete the node
        delete nodeToDelete;

        // Update routing tables for all nodes
        updateAllRoutingTables();
    }
    else {
        cout << "Node with value " << value << " not found." << endl;
    }
}

// Function to search for a node with a specific value
Node* RingDHT::searchNode(int value) {
    if (head == nullptr) {
        cout << "List is empty. Cannot search." << endl;
        return nullptr;
    }

    Node* current = head;

    // Search for the node with the specified value
    do {
        if (current->data == value) {
            return current;
        }
        current = current->next;
    } while (current != head);

    cout << "Node with value " << value << " not found." << endl;
    return nullptr;
}

// Helper function to update routing tables for all nodes in the list
void RingDHT::updateAllRoutingTables() {
    Node* current = head;
    do {
        updateRoutingTable(current);
        current = current->next;
    } while (current != head);
}


// Function to display the double circular linked list with routing tables
void RingDHT::display() {
    if (head == nullptr) {
        cout << "List is empty." << endl;
        return;
    }

    Node* current = head;

    do {
        cout << "Node " << current->data << ": [ ";
        for (Node* entry : current->routingTable) {
            cout << (entry ? to_string(entry->data) : "null") << " ";
        }
        cout << "]" << endl;

        current = current->next;
    } while (current != head);

    cout << endl;
}

int RingDHT::getIdentifierBits()
{
    return numBits;
}
