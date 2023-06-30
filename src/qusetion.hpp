#ifndef QUEST_
#define QUEST_

#include <vector>
#include <string>

class Qusetion {
private:
    std::pair<std::string, std::vector<std::string>> questoion;
public:
    Qusetion(const std::string& quest, const std::vector<std::string> answers) : questoion {quest, answers} {}
    std::pair<std::string, std::vector<std::string>> getQuest() const {return questoion;}
};

#endif