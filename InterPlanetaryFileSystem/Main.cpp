#include <iostream>
#include <string>

int basicHash(const std::string& input) {
    int hash = 0;

    for (char c : input) {
        hash += static_cast<int>(c);
    }

    return hash;
}

int main() {
    std::string input = "Hello, Worlddkjfwfenpfineiongioerngionringweniobgorgoubeougbuiwebgjowebuigbweioguiwebguiwebuibgowebguiwebuigbiwebgobweuigbuiwebguibweuibguwebuigbepijngpiwenhpgiberign!";
    int hashed = basicHash(input);

    std::cout << "Input: " << input << std::endl;
    std::cout << "Basic Hash: " << hashed << std::endl;

    return 0;
}
