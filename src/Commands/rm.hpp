#ifndef RM_
#define RM_

#include "../command.hpp"
#include "../file.hpp"
#include <queue>

class Rm  : public Command {
public:
    Rm(const std::string& n);
    void execute(State& st, Result& result, int) override;
    Folder* find(State& state, const std::string& str);
    void initQuests() override;
};
 
#endif  //RM_