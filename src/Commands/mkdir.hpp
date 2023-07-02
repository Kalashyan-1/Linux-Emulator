#ifndef MKDIR_
#define MKDIR_

#include "../command.hpp"

class Mkdir : public Command {
public:
   Mkdir(const std::string& n);
   void execute(State& st, Result& result, int) override;
   void initQuests() override;
};

#endif