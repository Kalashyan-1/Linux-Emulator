#ifndef EMUL_
#define EMUL_

#include <unordered_map>
#include "filesystem.hpp"
#include "folder.hpp"
#include "file.hpp"
#include "include/icludeCommands.hpp"
#include "scenario.hpp"
#include <sstream>
#include "state.hpp"
#include "result.hpp"

class Emuliator {
private:
    Folder* filesys;
    Command* com;
    std::unordered_map<std::string, Command*> commands;
    std::vector<User*> users;
    State state;
    Result result;
    Scenario scenar;
private:
    void initEmul();
    void intiMap();
    void info();
public:
    Emuliator() : state{users}{};
    void run();
    std::vector<User*>& getUsers() {return users;}
    // ~Emuliator();
};

#include "emuliator.cpp"

#endif  //EMUL_