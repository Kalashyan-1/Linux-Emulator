#ifndef ADD_USER_
#define ADD_USER_

#include "../command.hpp"
#include "../file.hpp"
#include "../user.hpp"
#include "../Cube-Encription/src/encryption.hpp"


class Adduser : public Command {
public:
   Adduser(const std::string& n);
   void execute(State& st, Result& result, int) override;
   Folder* find(State& state, const std::string& str);
   void initQuests() override;
private:
   Encryption en;
}; 

#include "adduser.cpp"

#endif