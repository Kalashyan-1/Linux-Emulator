#include "scenario.hpp"

void Scenario::initScen() {
    std::vector<std::pair<std::string, int>> vec;
    vec.push_back({"cd", 0});
    vec.push_back({"mkdir", 0});
    vec.push_back({"cd", 3});
    vec.push_back({"cd", 2});
    vec.push_back({"rm", 0});
    vec.push_back({"cd", 1});
    vec.push_back({"adduser", 0});
    vec.push_back({"deluser", 0});
    scen.push_back(vec);
}

std::vector<std::vector<std::pair<std::string, int>>> Scenario::getScen() const {
    return scen;
}
