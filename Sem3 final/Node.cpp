#include "Node.h"

Node::Node(int value, int numBits) : data(value), next(nullptr), prev(nullptr) {
    this->Files_btree = new btree(numBits);
    // Initialize routing table with entries for succ(p + 2^i), i = 1, ..., log2(N)
    for (int i = 0; i < numBits; ++i) {
        int entry = (value + (1 << i)) % (1 << numBits);
        routingTable.push_back(nullptr); // Initialize with nullptr, update later
    }
}
