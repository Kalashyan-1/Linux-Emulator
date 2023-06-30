#include "result.hpp"

Result::~Result() {
    for (auto a : wrongAnswers) {
        delete a;
    }
}
void Result::add(Qusetion* q) {
    wrongAnswers.push_back(q);
}
void Result::printFinalRes() {
    std::cout << "\n\n\n---------------------------------------------------------------------\n" << std::endl;
    std::cout << "Here is total worng answers and count:" << wrongAnswers.size() << std::endl;
    for (auto a : wrongAnswers) {
        std::cout << "Question: \033[1;31m" + a->getQuest().first + "\033[0m" << std::endl;
        std::cout << "Answer: ";
        for (auto b : a->getQuest().second) {
            std::cout << "\033[1;32m";
            std::cout << b + "\n";
            std::cout << "\033[0m";
        }
        std::cout << std::endl;
    }
    int per = 100 - ((100 * wrongAnswers.size()) / 8); 
    std::cout << "Done " <<  per << "%" << std::endl;
}