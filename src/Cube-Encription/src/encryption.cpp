#include "encryption.hpp"

Encryption::Encryption(const std::string& str) : cube {str}
{   
    initMap();
}

void Encryption::rotateLeft(std::string& str) {
    int top[] {0, 1, 5, 4, 0};
    int bottom[] {3, 2, 6, 7, 3};
    std::string res(str.size(),' ');
    for (int i = 0; i < str.size() / 2; ++i) {
        res[top[i]] = str[top[i + 1]];
        res[bottom[i]] = str[bottom[i + 1]];
    }
    str = res;
}

void Encryption::rotateRight(std::string& str) {
    int top[] {0, 1, 5, 4, 0};
    int bottom[] {3, 2, 6, 7, 3};
    std::string res(str.size(),' ');
    for (int i = 0; i < str.size() / 2; ++i) {
        res[top[i + 1]] = str[top[i]];
        res[bottom[i + 1]] = str[bottom[i]];
    }
    str = res;
}

void Encryption::rotateUp(std::string& str) {
    int top[] {0, 4, 7, 3, 0};
    int bottom[] {1, 5, 6, 2, 1};
    std::string res(str.size(),' ');
    for (int i = 0; i < str.size() / 2; ++i) {
        res[top[i + 1]] = str[top[i]];
        res[bottom[i + 1]] = str[bottom[i]];
    }
    str = res;
}
void Encryption::rotateDown(std::string& str) {
    int top[] {0, 4, 7, 3, 0};
    int bottom[] {1, 5, 6, 2, 1};
    std::string res(str.size(),' ');
    for (int i = 0; i < str.size() / 2; ++i) {
        res[top[i]] = str[top[i + 1]];
        res[bottom[i]] = str[bottom[i + 1]];
    }
    str = res;
}
 
std::string Encryption::encript() {
    std::ofstream file("key.txt");
    if (!file.is_open()) {std::cout << "Can not open.";}
    file << "key:" << std::endl;
    int size = cube.size() / 8;
    int tmp = cube.size() - (size * 8);
    tmp = (tmp < 8 && tmp != 0)? 8 - tmp : 0;
    while (tmp--) {
        cube.push_back('?');
    }
    size = cube.size() / 8;
    std::string s;
    std::string res = "";
    int rand;
    std::string key = "";
    int k = 0;
    for (int i = 0; i < size; ++i) {
        k += 8;
        rand = randNumGen();
        s = {cube.begin() + (i * 8), cube.begin() + k};
        if (rand < 5) {
            if (rand & 1 != 0) {
                key += 'L' + std::to_string(rand) + ',' + 'U' + std::to_string(rand + 1) + ',' + 'R' + std::to_string(rand + 3) + ':';
                for (int m = 0; m < rand; ++m) {rotateLeft(s);}
                for (int m = 0; m < rand + 1; ++m) {rotateUp(s);}
                for (int m = 0; m < rand + 3; ++m) {rotateRight(s);}
            } else {
                key += "R1:";
                rotateRight(s);
            }
        } else {
            if (rand & 1 != 0) {
                key += "L1:";
                rotateLeft(s);
            } else {
               key += 'L' + std::to_string(rand) + ',' + 'D' + std::to_string(rand - 2) + ':';
               for (int m = 0; m < rand; ++m) {rotateLeft(s);}
               for (int m = 0; m < rand - 2; ++m) {rotateDown(s);}
            }
        }
        res += s;
    }
    file << key;
    file.close();
    cube = res;
    return res;
}


std::string Encryption::decript() {
    std::ifstream file("key.txt");
    std::string key;
    std::getline(file, key);
    std::getline(file, key);
    std::cout << "key: " << key << std::endl;
    std::stringstream s(key);
    std::string tmp1;
    std::string tmp2;
    int k = 0;
    std::string res = "";
    while (std::getline(s, tmp1, ':')) {
        k += 8;
        std::string s(cube.begin() + k-8, cube.begin() + k);
        tmp1.erase(tmp1.find_last_not_of(" \t\n\r\f\v") + 1);
        std::reverse(tmp1.begin(), tmp1.end());

        std::stringstream s2(tmp1);
        
        while (std::getline(s2, tmp2, ',')) {
            tmp2.erase(tmp2.find_last_not_of(" \t\n\r\f\v") + 1);
            char ch = tmp2[tmp2.size() - 1];
            tmp2.erase(tmp2.begin() + tmp2.size() - 1);
            int size = std::stoi(tmp2);
            for (int i = 0; i < size; ++i) {
                map[ch](s);
            }
        }
        res += s;
    }
    for (int i = res.size() - 1; i > 0; --i) {
        if (*(res.begin() + i) != '?') {break;}
        res.erase(res.begin() + i);
    }
    cube = res;
    return res;
} 

int Encryption::randNumGen() {
    std::random_device rd;
    std::mt19937 mt(rd());
    int minNumber = 1;
    int maxNumber = 9;
    std::uniform_int_distribution<int> dist(minNumber, maxNumber);
    return dist(mt);
}

void Encryption::initMap() {
    map['L'] = [this](std::string& vec) { rotateRight(vec); };
    map['R'] = [this](std::string& vec) { rotateLeft(vec); };
    map['U'] = [this](std::string& vec) { rotateDown(vec); };
    map['D'] = [this](std::string& vec) { rotateUp(vec); };
}
