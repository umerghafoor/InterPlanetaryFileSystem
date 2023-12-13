#include <iostream>
#include <string>
//#include <openssl/sha.h>

class Computer {
public:
    std::string name;

    Computer() : name("") {}
    explicit Computer(const std::string& computerName) : name(computerName) {}
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

    int getSize() { return size; }
    int getIdentifierBits()
    {
        return identifierBits;
    }

    void initializeRing() {
        if (identifierBits <= 0) {
            std::cerr << "Invalid number of bits." << std::endl;
            return;
        }

        head = new Node(0, identifierBits, "");
        Node* current = head;

        for (int i = 1; i < size; ++i) {
            current->next = new Node(i, identifierBits, "");
            current->next->prev = current;
            current = current->next;
        }

        // Close the ring
        current->next = head;
        head->prev = current;

    }

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

    void displayRing() const {
        if (!head) {
            std::cerr << "Ring is not initialized." << std::endl;
            return;
        }

        Node* current = head;
        do {
            if (current->state) {
                std::cout << "Node " << current->data << " (Computer: " << current->computer.name
                    << ", State: " << current->state << "): ";

                for (int i = 0; i < identifierBits; ++i) {
                    if (current->fingerTable[i]) {
                        std::cout << current->fingerTable[i]->data << " ";
                    }
                    else {
                        // Handle the case where the fingerTable entry is not valid
                        std::cout << "N/A ";
                    }
                }

                std::cout << std::endl;
            }
            current = current->next;
        } while (current != head);
    }

    Node* findNode(int index) const {
        Node* current = head;
        do {
            if (current->data == index) {
                return current;
            }
            current = current->next;
        } while (current != head);
        return nullptr; // Node not found or not active
    }


    void initializeFingerTables() {
        Node* current = head;
        do 
        {
            for (int i = 0; i < identifierBits; ++i) 
            {
                int fingerIndex = (current->data + (1 << i)) % size;
                Node* temp = findNextNode(fingerIndex);
                while (temp->state == 0)
                {
                    temp = temp->next;
                    if (temp == current)
                    {
                        break;
                    }
                }
                current->fingerTable[i] =temp;
            }
            current = current->next;
        } while (current != head);

    }

    Node* findNextNode(int index) const {
        Node* current = head;
        int originalIndex = current->data;

        do {
            if (current->data == index) {
                return current;
            }
            current = current->next;
        } while (current->data != originalIndex);

        return nullptr;  // Node not found or not active
    }


    void addComputerToNode(int nodeIndex, const std::string& computerName) {
        Node* targetNode = findNode(nodeIndex);
        if (targetNode) {
            targetNode->computer.name = computerName;
            targetNode->state = true;
            updateFingerTables();
        }
        else {
            std::cerr << "Node not found." << std::endl;
        }
    }

    void deleteComputerFromNode(int nodeIndex) {
        Node* targetNode = findNode(nodeIndex);
        if (targetNode) {
            targetNode->computer.name = "";
            targetNode->state = false;
            updateFingerTables();
        }
        else {
            std::cerr << "Node not found." << std::endl;
        }
    }

    void updateFingerTables() {
        // Update finger tables for all nodes
        initializeFingerTables();
    }
};

class Login {
private:
    RingDHT* dht;
    Node* loggedInUser;  // Pointer to the currently logged-in user

public:
    Login(RingDHT* dht) : dht(dht), loggedInUser(nullptr) {}

    bool authenticateUser(int nodeIndex, const std::string& computerName) {
        Node* userNode = dht->findNode(nodeIndex);
        if (userNode && userNode->computer.name == computerName) {
            std::cout << "Login successful. Welcome, " << computerName << "!\n";
            loggedInUser = userNode;  // Store the pointer to the logged-in user
            return true;
        }
        else {
            std::cout << "Login failed. Invalid credentials.\n";
            loggedInUser = nullptr;  // Clear the logged-in user pointer
            return false;
        }
    }

    Node* getLoggedInUser() const {
        return loggedInUser;
    }

    Node* searchNode(int targetIndex) const {
        if (!loggedInUser) {
            std::cerr << "No user logged in.\n";
            return nullptr;
        }

        Node* current = loggedInUser;
        int steps = 0; // Counter to track the number of nodes traversed

        std::cout << "Nodes traversed: ";
        std::cout << "Node " << current->data << " (" << current->computer.name << ") -> ";
        for (size_t i = 0; i < dht->getIdentifierBits(); i++) {
            steps++;

            if (targetIndex == current->fingerTable[i]->data) {
                // Found the node with the target index
                std::cout << "Node " << current->data << " (" << current->computer.name << ") -> ";
                std::cout << "Total nodes traversed: " << steps << "\n";
                return current;
            }
            if (targetIndex < current->fingerTable[0]->data)
            {
                current = current->fingerTable[0];
                std::cout << "Node " << current->data << " (" << current->computer.name << ") -> ";
                std::cout << "Total nodes traversed: " << steps << "\n";
                return current;
            }
            
            //std::cout << "(" << i << ',' << current->fingerTable[i]->data << ')';
            if ( targetIndex < current->fingerTable[i]->data) 
            {
                // Move to the previous node
                current = current->fingerTable[i-1];
                i = -1; // Reset the loop to start from the beginning
                std::cout << "Node " << current->data << " (" << current->computer.name << ") -> ";
            }
            else if (i == dht->getIdentifierBits() - 1)
            {
                current = current->fingerTable[i];
                i = -1;
                std::cout << "Node " << current->data << " (" << current->computer.name << ") -> ";
            }
        }

        // Print the last traversed node when the loop completes
        std::cout << "Node " << current->data << " (" << current->computer.name << ")\n";
        std::cout << "Total nodes traversed: " << steps << "\n";

        return current;
    }


};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insertValuesIntoFingerTables(RingDHT& ring) {
    ring.addComputerToNode(1,"1");
    ring.addComputerToNode(4, "1");
    ring.addComputerToNode(9, "1");
    ring.addComputerToNode(11, "1");
    ring.addComputerToNode(14, "1");
    ring.addComputerToNode(18, "1");
    ring.addComputerToNode(20, "1");
    ring.addComputerToNode(21, "1");
    ring.addComputerToNode(28, "1");
}




void displayLoginMenu(Login& login, RingDHT& ring) 
{
    int choice;
    while (true) {
        std::cout << "\nLogin Menu:\n";
        std::cout << "1. Log In\n";
        std::cout << "2. Display Logged-In User\n";
        std::cout << "3. Search for Node\n";
        std::cout << "4. Back to Main Menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            int nodeIndex;
            std::string computerName;
            std::cout << "Enter the index of the node to log in: ";
            std::cin >> nodeIndex;
            std::cout << "Enter the name of the computer: ";
            std::cin >> computerName;
            login.authenticateUser(nodeIndex, computerName);
            break;
        }
        case 2: {
            Node* loggedInUser = login.getLoggedInUser();
            if (loggedInUser) {
                std::cout << "Logged-in user: Node " << loggedInUser->data << " (Computer: " << loggedInUser->computer.name << ")\n";
            }
            else {
                std::cout << "No user logged in.\n";
            }
            break;
        }
        case 3: {
            
            if (login.getLoggedInUser()) 
            {
                int targetIndex;
                std::cout << "Enter the index of the target node to search: ";
                std::cin >> targetIndex;

                Node* targetNode = login.searchNode(targetIndex);
                if (targetNode) {
                    std::cout << "Found target node: Node " << targetNode->data << " (Computer: " << targetNode->computer.name << ")\n";
                }
                else {
                    std::cout << "Target node not found.\n";
                }
            }
            else {
                std::cout << "Please log in first.\n";
            }
            break;
        }
        case 4:
            std::cout << "Returning to the main menu.\n";
            return;
        default:
            std::cerr << "Invalid choice. Please enter a valid option." << std::endl;
        }
    }
}

void displayMenu(RingDHT& ring, Login& login) {
    int choice;
    while (true) {
        std::cout << "\nMain Menu:\n";
        std::cout << "1. Display Ring\n";
        std::cout << "2. Login Menu\n";
        std::cout << "3. Add Computer to Node\n";
        std::cout << "4. Delete Computer from Node\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            ring.displayRing();
            break;
        case 2:
            displayLoginMenu(login, ring);
            break;
        case 3: {
            int nodeIndex;
            std::string computerName;
            std::cout << "Enter the index of the node to add a computer: ";
            std::cin >> nodeIndex;
            std::cout << "Enter the name of the computer: ";
            std::cin >> computerName;
            ring.addComputerToNode(nodeIndex, computerName);
            std::cout << "Computer added to node." << std::endl;
            break;
        }
        case 4: {
            int nodeIndex;
            std::cout << "Enter the index of the node to delete a computer: ";
            std::cin >> nodeIndex;
            ring.deleteComputerFromNode(nodeIndex);
            std::cout << "Computer deleted from node." << std::endl;
            break;
        }
        case 5:
            std::cout << "Exiting program.\n";
            return;
        default:
            std::cerr << "Invalid choice. Please enter a valid option." << std::endl;
        }
    }
}

int main() {
    int bits;
    std::cout << "Enter the number of bits for the identifier: ";
    std::cin >> bits;

    RingDHT ring(bits);
    std::cout << "Ring DHT with " << (1 << bits) << " elements initialized." << std::endl;

    Login login(&ring);

    insertValuesIntoFingerTables(ring);

    displayMenu(ring, login);

    return 0;
}