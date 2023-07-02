#include "pwd.hpp"

Pwd::Pwd(const std::string& n) {
    name = n; 
    initQuests();
}
void Pwd::execute(State& st, Result& result, int i) {
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


void Pwd::initQuests() {
    Qusetion* q = new Qusetion("Print working directory.", {"pwd ", "pwd -LP ", "pwd -L ", "pwd -P "});
    quests.push_back({q, [&](State& st) {
        std::string print;
        Folder* f = st.getCurrentState();
        if (f == st.getRoot()) {
            print = f->getPath();   
        } else if (f->getParent() == st.getRoot()) {
            print = st.getCurrentState()->getPath() + st.getCurrentState()->getName();
        } else {
            print = st.getCurrentState()->getPath() + '/' + st.getCurrentState()->getName();
        }
        std::cout << print << std::endl;
    }});
}
