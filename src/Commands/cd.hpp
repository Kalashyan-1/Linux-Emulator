#ifndef CD_
#define CD_

#include "../command.hpp"

class Cd : public Command {
public:
    Cd(const std::string& n);
    void execute(State& st, Result& result, int) override;
    void find(State& state, const std::string& str);
    void initQuests() override;
};


#endif  //CD_