
#include "RingDHT.h"

void displayLoginMenu(Login& myComputer, RingDHT& ring)
{
    int choice;
    while (true) {
        std::cout << "\nLogin Menu:\n";
        std::cout << "1. Log In\n";
        std::cout << "2. Display Logged-In User\n";
        std::cout << "3. Search for other computer\n";
        std::cout << "4. Insert File\n";
        std::cout << "5. Remove File\n";
        std::cout << "6. Search File\n";
        std::cout << "0. Back to Main Menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            int nodeIndex;
            std::string computerName;
            std::cout << "Enter the index of the node to log in: ";
            std::cin >> nodeIndex;
            myComputer.authenticateUser(nodeIndex);
            break;
        }
        case 2: {
            Node* loggedInUser = myComputer.getLoggedInUser();
            if (loggedInUser) {
                std::cout << "Logged-in user: Node " << loggedInUser->data << "\n";
            }
            else
            {
                std::cout << "No user logged in.\n";
            }
            break;
        }
        case 3: {

            if (myComputer.getLoggedInUser())
            {
                int targetIndex;
                std::cout << "Enter the index of the target node to search: ";
                std::cin >> targetIndex;

                Node* targetNode = myComputer.searchNode(targetIndex);
                if (targetNode) {
                    std::cout << "Found target node: Node " << targetNode->data << "\n";
                }
                else
                {
                    std::cout << "Target node not found.\n";
                }
            }
            else
            {
                std::cout << "Please log in first.\n";
            }
            break;
        }
        case 4:
        {
            std::string name, path;

            std::cout << "Enter Name of the file: ";
            std::cin >> name;

            std::cout << "Enter Path of the file: ";
            std::cin >> path;

            File file(name, path);

            myComputer.insertFile(file);

            break;
        }
        case 5:
        {
            int file;
            std::cout << "Enter file: ";
            std::cin >> file;
            myComputer.removeFile(file);
            break;
        }
        case 6: {
            int file;
            std::cout << "Enter file: ";
            std::cin >> file;
            if (myComputer.searchFile(file) == -1)
            {
                std::cout << "File Not Found.\n";
            }
            break;
        }
        case 0:
            std::cout << "Returning to the main menu.\n";
            return;
        default:
            std::cerr << "Invalid choice. Please enter a valid option." << std::endl;
        }
    }
}




int main() {
    // Ask the user for the number of bits
    int numBits;
    cout << "Enter the number of bits for the routing table: ";
    cin >> numBits;

    // Create a circular linked list with the specified number of bits
    RingDHT list(numBits);

    // Inserting nodes in order
    list.insertInOrder(1);
    list.insertInOrder(4);
    list.insertInOrder(9);
    list.insertInOrder(11);
    list.insertInOrder(14);
    list.insertInOrder(18);
    list.insertInOrder(20);
    list.insertInOrder(21);
    list.insertInOrder(28);

    // Displaying the list with routing tables
    cout << "Double Circular Linked List with Routing Tables: " << endl;
    list.display();

    //list.deleteNode(14);
    //list.deleteNode(21);

    Node* searchedNode = list.searchNode(9);
    if (searchedNode != nullptr) {
        cout << "Node found: " << searchedNode->data << endl;
    }
    else {
        cout << "Node not found." << endl;
    }

    // Displaying the updated list with routing tables
    cout << "Updated Double Circular Linked List with Routing Tables: " << endl;
    list.display();

    Login comp(&list);

    displayLoginMenu(comp, list);

    return 0;
}

