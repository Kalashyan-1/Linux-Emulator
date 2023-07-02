#include "rm.hpp"

Rm::Rm(const std::string& n) {
    name = n; 
    initQuests();
}
void Rm::execute(State& st, Result& result, int i) {
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
        if (*(tmp2.end() - 2) == '/' && *(tmp2.end() - 3) == ' ') {
            tmp2.erase(tmp2.end() - 2);
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

Folder* Rm::find(State& state, const std::string& str) {
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

void Rm::initQuests() {
    Qusetion* q = new Qusetion("Delete newly created directory.", {"rm -rf my_dir ", "rm -r my_dir "});
    quests.push_back({q, [&](State& st) {
        auto cur = st.getCurrentState();
        std::string str = cur->getPath() + cur->getName();
        if (*(str.begin()) == '/') {
            str.erase(str.begin());
        }
        Folder* f = find(st, str);
        auto child = f->getChildren();
        for (auto ch : child) {
            if (ch->getName() == "my_dir" && dynamic_cast<Folder*>(ch)) {
                f = dynamic_cast<Folder*>(ch);
                break;
            }
        }
        std::queue<Folder*> qu;
        qu.push(f);
        while (!qu.empty()) {
            auto a = qu.front();
            qu.pop();
            int size = a->getChildren().size();
            for (auto ch : a->getChildren()) {
                if (dynamic_cast<File*>(a)) {
                    delete ch;
                    continue;
                }
                qu.push(dynamic_cast<Folder*>(a));
            }
            delete a;
        }
    }});
}
