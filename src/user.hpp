#ifndef USER_
#define USER_

#include <string>

class User {
public:
    User(const std::string& str): name {str}, groupID(id  + 2) {}
    std::string getName() const {return name;}
    int getGroupId() const {return groupID;}
    int getId() const {return id;}
private:
    std::string name;
    static int id;
    int groupID;
};


#endif