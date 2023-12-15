#include "Login.h"

bool Login::authenticateUser(int nodeIndex)
{
    loggedInUser = dht->searchNode(nodeIndex);

    if (loggedInUser == nullptr)
    {
        return 0;
    }
    return true;
}

Node* Login::getLoggedInUser() const
{
    return loggedInUser;
}

Node* Login::searchNode(int targetIndex) const
{
    if (!loggedInUser) {
        std::cerr << "No user logged in.\n";
        return nullptr;
    }

    Node* current = loggedInUser;
    int steps = 0; // Counter to track the number of nodes traversed
    bool endindex = 0;
    if (targetIndex > current->data)
    {
        endindex = 1;
    }

    std::cout << "Nodes traversed: ";
    std::cout << "Node " << current->data << " -> ";
    for (size_t i = 0; i < dht->getIdentifierBits(); i++) {
        steps++;
        if (targetIndex == current->data)
        {
            // Found the node with the target index
            std::cout << "Node " << current->data << "\n";
            std::cout << "Total nodes traversed: " << steps << "\n";
            return current;
        }
        if (targetIndex < current->routingTable[0]->data)
        {
            current = current->routingTable[0];
            std::cout << "Node " << current->data << "\n";
            std::cout << "Total nodes traversed: " << steps << "\n";
            return current;
        }

        //std::cout << "(" << i << ',' << current->fingerTable[i]->data << ')';


        if (current->routingTable[i]->data < current->data && current->data < targetIndex && endindex)
        {
            // Move to the previous node
            if (i == 0)
            {
                current = current->routingTable[i];
                i = -1; // Reset the loop to start from the beginning
                std::cout << "Node " << current->data << " -> ";
                if (current->data < targetIndex)
                {
                    std::cout << "Total nodes traversed: " << steps << "\n";
                    return current;
                }
            }
            else
            {
                current = current->routingTable[i - 1];
                i = -1; // Reset the loop to start from the beginning
                std::cout << "Node " << current->data << " -> ";
            }
        }

        else if (targetIndex < current->routingTable[i]->data)
        {
            // Move to the previous node
            current = current->routingTable[i - 1];
            i = -1; // Reset the loop to start from the beginning
            std::cout << "Node " << current->data << " -> ";
        }
        else if (i == dht->getIdentifierBits() - 1)
        {
            current = current->routingTable[i];
            i = -1;
            std::cout << "Node " << current->data << " -> ";
        }
    }

    // Print the last traversed node when the loop completes
    std::cout << "Node " << current->data << "\n";
    std::cout << "Total nodes traversed: " << steps << "\n";

    return current;
}

void Login::insertFile(File file)
{
    if (loggedInUser)
    {
        int comp = 12;// = file;
        Node* node = this->searchNode(comp);
        int key = 1;

        node->Files_btree->insert(key, file);
    }
}

void Login::removeFile(int key)
{
    if (loggedInUser)
    {
        int comp = 12;// = file;
        Node* node = this->searchNode(comp);

        node->Files_btree->remove(key);
    }
}

int Login::searchFile(int key)
{
    if (loggedInUser)
    {
        int comp = 12;// = file;
        Node* node = this->searchNode(comp);

        btreenode* result = node->Files_btree->search(key);

        if (result)
        {
            std::cout << "Name " << result->filepath->name << " \n";
            std::cout << "path " << result->filepath->path << "\n";
            return 0;
        }
        return -1;
    }
    return -1;
}
