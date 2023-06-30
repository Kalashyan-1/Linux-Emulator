#ifndef RES_
#define RES_

#include "qusetion.hpp"
#include <iostream>

class Result {
public:
    Result() = default;
    ~Result();
    void add(Qusetion*);
    void printFinalRes();
private: 
    std::vector<Qusetion*> wrongAnswers;
};

#include "result.cpp"

#endif  //RES_
