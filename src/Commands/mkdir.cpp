#include "mkdir.hpp"


Mkdir::Mkdir(const std::string& n) {name = n; initQuests();}

void Mkdir::execute(State& st, Result& result, int i) {
    std::string tmp;
    std::string tmp2 = "";
    bool flag = false;
    // for (auto a : quests) {
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
        std::cout << "\033[1;35m" <<  st.getUser().back()->getName() + "@Emuliator: " + print + " $ " <<"\033[0m";
        std::getline(std::cin, tmp);
        std::stringstream ss(tmp);
        while (ss >> tmp) {
            tmp2 += tmp + " ";
        }
        if (*(tmp2.end() - 2) == '/' && *(tmp2.end() - 3) == ' ') {
            tmp2.erase(tmp2.end() - 2);
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
        flag = false;
        tmp2 = "";
    // }

    // std::cout << "\033[1;35m" <<  "root@Emuliator: " + st.getCurrentState()->getPath() + st.getCurrentState()->getName() + " $ " <<"\033[0m";

   
}


void Mkdir::initQuests()  {
    Qusetion* q = new Qusetion("Create a new directory named `my_dir` in the current directory.", {"mkdir ./my_dir ", "mkdir my_dir "});
    quests.push_back({q, [&](State& st) {
        Folder* f = st.getCurrentState();
        Folder* newf = new Folder("my_dir", f->getPath() + f->getName());
        newf->setParent(f);
        std::cout << st;
        f->add(newf);
    }});
}
