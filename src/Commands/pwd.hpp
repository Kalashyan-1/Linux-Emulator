#ifndef PWD_
#define PWD_

#include "../command.hpp"
 
class Pwd : public Command {
public:
   Pwd(const std::string& n);
   void execute(State& st, Result& result, int) override;
   void initQuests() override;
};


#endif 