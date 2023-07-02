#ifndef SU_
#define SU_

#include "../command.hpp"
#include "../file.hpp"
#include "../Cube-Encription/src/encryption.hpp"

class Su : public Command {
public:
   Su(const std::string& n);
   void execute(State& st, Result& result, int) override;
   Folder* find(State& state, const std::string& str);
   void initQuests() override;
};

#endif //SU_