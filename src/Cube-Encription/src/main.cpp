#include "/home/khachik/Linux-Emuliator/src/Cube-Encription/src/encryption.hpp"

int main() {
    std::string text;
    std::getline(std::cin, text);
    Encryption e(text);
    std::cout << "Encrypted text: " << e.encript() << std::endl;
    std::cout << "Decrypted text: " << e.decript() << std::endl;
}