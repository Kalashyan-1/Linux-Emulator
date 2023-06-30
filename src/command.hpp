#ifndef COMMAND_
#define COMMAND_

#include "qusetion.hpp"
#include <functional>
#include <map>
#include "folder.hpp"
#include "state.hpp"
#include "result.hpp"
#include <sstream>

class Command {
protected:
   std::vector<std::pair<Qusetion*, std::function<void (State&)>>> quests; 
   std::map<std::string, std::function<void(Folder*)>> options;
   std::string name;
public:
   Command(const std::string& n) :name {n} {}
   Command() = default;
   // virtual ~Command() = 0;
   virtual void execute(State&, Result&, int) = 0;
   virtual void initQuests() = 0;
};

#endif   //COMMAND_