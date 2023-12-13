#include <iostream>
#include <string>
//#include <openssl/sha.h>
#include"Class.h"


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