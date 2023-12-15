#pragma once

int HashforComputer(const std::string& input) {
    int hash = 0;

    for (char c : input) {
        hash += static_cast<int>(c);
    }

    return hash;
}