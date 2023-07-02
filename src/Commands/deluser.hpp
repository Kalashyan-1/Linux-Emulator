#ifndef DEL_USER_
#define DEL_USER_

#include "../command.hpp"
#include "../file.hpp"
#include "../user.hpp"
#include "../Cube-Encription/src/encryption.hpp"

#include <queue>

class Deluser : public Command {
public:
   Deluser(const std::string& n);
   void execute(State& st, Result& result, int) override;
   Folder* find(State& state, const std::string& str);
   void initQuests() override;

};


#endif