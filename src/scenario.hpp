#ifndef SCEN_
#define SCEN_

#include "qusetion.hpp"
#include <functional>
#include "state.hpp"
class Scenario {
public:
    void initScen();
    std::vector<std::vector<std::pair<std::string, int>>> getScen() const;

private: 
    std::vector<std::pair<Qusetion*, std::function<void (State&)>>> quests; 
    std::vector<std::vector<std::pair<std::string, int>>> scen;
};


#endif   // SCEN_
