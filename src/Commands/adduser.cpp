#include "adduser.hpp"

Adduser::Adduser(const std::string& n) {
    name = n;
    initQuests();
}

void Adduser::execute(State& st, Result& result, int i) {
    std::string tmp;
    std::string tmp2 = "";
    bool flag = false;
        auto a = quests[i];
        Folder* f = st.getCurrentState();
        std::string print;
        std::cout << "> " + a.first->getQuest().first << std::endl;
        if (f == st.getRoot()) {
            print = f->getPath();   
        } else if (f->getParent() == st.getRoot()) {
            print = st.getCurrentState()->getPath() + st.getCurrentState()->getName();
        } else {
            print = st.getCurrentState()->getPath() + '/' + st.getCurrentState()->getName();
        }
        std::cout << "\033[1;35m" <<  st.getUser().back()->getName() + "@Emulator: " + print + " $ " <<"\033[0m";
        std::getline(std::cin, tmp);
        std::stringstream ss(tmp);
        while (ss >> tmp) {
            tmp2 += tmp + " ";
        }
        
        for (auto b : a.first->getQuest().second) {
            if (tmp2 == b) {
                std::cout << "\033[1;32m Correct answer! \033[0m" << std::endl;
                a.second(st);
                flag = true;
                break;
           }
        }
        if (!flag) {
            std::cout << "\033[1;31m Wrong answer! \033[0m" << std::endl;
            std::cout << "At this point, the program automatically performed the necessary action." << std::endl;
            a.second(st);
            result.add(a.first);
            flag = false;
        }
}

Folder* Adduser::find(State& state, const std::string& str) {
    std::string tempStr;    
    std::stringstream ss(str);
    bool flag = true;
    Folder* fold = state.getRoot();
    while (std::getline(ss, tempStr, '/') && flag) {
        auto children = fold->getChildren();
        for (auto a : children) {
            if (a->getName() == tempStr && dynamic_cast<Folder*>(a)) {
                fold = dynamic_cast<Folder*>(a);
                flag = false;
                break;
            } 
        }
        if (flag) {
            std::cout << "cd: "+tempStr+": No such file or directory" << std::endl;
            fold = nullptr;
            flag = true;
            break;
        }
        flag = true;
    }
    return fold;  
}

void Adduser::initQuests() {
    Qusetion* q = new Qusetion("Create a new user named `my_user`, such that a directory is created in home directory and allow.\nDo not use any option.", {"adduser my_user "});
    quests.push_back({q, [&](State& st) {
        std::string password;
        std::string tmp;

        while (true) {
            std::cout << "New password: ";
            std::getline(std::cin, password);
            std::cout << "Retype new password: ";
            std::getline(std::cin, tmp);
            if (password == tmp) {
                break;
            }
        }
        en.setText(password);
        Folder* f;
        
        User* u = new User("my_user");
        st.addUser(u);
        f = find(st, "etc");
       
       
        for (auto ch : f->getChildren()) {
            if (ch->getName() == "passwd" && dynamic_cast<File*>(ch)) {
                File* file = dynamic_cast<File*>(ch);
                file->setContent(u->getName() + ":x:" + std::to_string(u->getId()) + ":" + std::to_string(u->getGroupId()) + ":/home/" + u->getName() + "\n");
                break;
            }
        }
        en.encript();
        for (auto ch : f->getChildren()) {
            if (ch->getName() == "shadow" && dynamic_cast<File*>(ch)) {
                File* file = dynamic_cast<File*>(ch);
                file->setContent(u->getName() + ":" + en.getCube() + ':' + "\n");
                break;
            }
        }
        for (auto ch : f->getChildren()) {
            if (ch->getName() == "group" && dynamic_cast<File*>(ch)) {
                File* file = dynamic_cast<File*>(ch);
                file->setContent(u->getName() + ":" + std::to_string(u->getGroupId()) + "\n");
                break;
            }
        }
        f = find(st, "home");
        Folder* newf = new Folder(u->getName(), f->getPath() + f->getName());
        newf->setParent(f);
        f->add(newf);
    }});
}
