#ifndef STATE_
#define STATE_

#include "folder.hpp"
#include "user.hpp"

class State {
private:
    Folder* root;
    Folder* current;
    Folder* previous;
    std::vector<User*>& users;

public:
    State(Folder* c, Folder* p, std::vector<User*>& v) : previous{p}, current{c}, users{v} {}
    State() = default;
    State(std::vector<User*>& v): users{v} {}    
    Folder* getCurrentState() const {return current;}
    Folder* getPreviousState() const {return previous;}
    Folder* getRoot() const {return root;}
    std::vector<User*>& getUser() const {return users;}
    void setRoot(Folder* r) {root = r;}
    void setCurrentState(Folder* c) {current = c;}
    void setPreviousState(Folder* p) {previous = p;}
    // void setUser(std::vector<User*>& v) {users = v;} 
    void addUser(User* u) {users.insert(users.begin(), u);}
    friend std::ostream& operator<<(std::ostream& stream, State& st) {
        stream << "Current name: " + st.current->getName() << " ,Path: " + st.current->getPath() << " ,Parent name: " + st.current->getParent()->getName() << std::endl;
        stream << "Previous name: " + st.previous->getName() << " ,Path: " + st.previous->getPath()<< ((st.previous == st.root)? "root" : " ,Parent name: " + st.previous->getParent()->getName()) << std::endl;
        return stream;
    }
};



#endif  //STATE_