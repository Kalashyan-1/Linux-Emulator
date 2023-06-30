#ifndef SU_
#define SU_

#include "../command.hpp"
#include "../file.hpp"
class Su : public Command {
public:
   Su(const std::string& n);
   void execute(State& st, Result& result, int) override;
   Folder* find(State& state, const std::string& str);
   void initQuests() override;
};

#include "su.cpp"

#endif //SU_