#include "su.hpp"

Su::Su(const std::string& n) {
    name = n; 
    initQuests();
}
void Su::execute(State& st, Result& result, int i) {
    std::string tmp;
    std::string tmp2 = "";
    std::string password;
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
    
    std::cout << "tmp2: " << tmp2 << std::endl;
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
Folder* Su::find(State& state, const std::string& str) {
    std::string tempStr;    
    std::stringstream ss(str);
    bool flag = true;
    Folder* fold = state.getRoot();
    std::cout << "str: " << str << std::endl;
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
void Su::initQuests() {
    Qusetion* q = new Qusetion("Change the user to `my_user`.", {"sudo su my_user ", "su my_user "});
    quests.push_back({q, [&](State& st) {
        auto& users = st.getUser();
        for (auto& a : users) {
            if (a->getName() == "my_user") {
                std::swap(a, users[users.size() - 1]);
                break;
            }
        }
    }});

    q = new Qusetion("Change the user to `root`.", {"su root "});
    quests.push_back({q, [&](State& st) {
        Folder* f = find(st,"etc");
        std::string tmp;
        for (auto ch : f->getChildren()) {
            if (ch->getName() == "shadow" && dynamic_cast<File*>(ch)) {
                File* file = dynamic_cast<File*>(ch);
                tmp = file->getContent();
                break;
            }
        }
        std::stringstream ss(tmp);
        std::getline(ss, tmp, ':');
        std::getline(ss, tmp, ':');


        std::string password;
        Encryption en(tmp);
        en.decript();
        

        std::cout << "Write password for `my_user`" << std::endl;  
        int c = 3;
        while (c--) {
            std::cout << "New password: ";
            std::getline(std::cin, password);
            if (password == en.getCube()) {
                break;
            }
        }

        auto& users = st.getUser();
        for (auto& a : users) {
            if (a->getName() == "my_user") {
                std::swap(a, users[users.size() - 1]);
                break;
            }
        }

    }});
}
