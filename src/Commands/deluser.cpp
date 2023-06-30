#include "deluser.hpp"

Deluser::Deluser(const std::string& n) {
    name = n; 
    initQuests();
}

void Deluser::execute(State& st, Result& result, int i) {
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
        std::cout << "\033[1;35m" <<  st.getUser().back()->getName() + "@Emuliator: " + print + " $ " <<"\033[0m";
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

Folder* Deluser::find(State& state, const std::string& str) {
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

void Deluser::initQuests() {
    Qusetion* q = new Qusetion("Delete the newly created user, such that to be deleted all information connected with that user.", {"deluser my_user "});
    quests.push_back({q, [&](State& st) {
        Folder* f;
        User* u;
        std::string tmp;
        std::string tmp2 = "";
        auto users = st.getUser();
        int c = 0;
        for (auto us : users) {
            if (us->getName() == "my_user") {
                users.erase(users.begin() + c);
            }
            c++;
        }

        f = find(st, "etc");
        for (auto ch : f->getChildren()) {
            auto name = ch->getName();
            if ((name == "passwd" || name == "shadow" || name == "group") && dynamic_cast<File*>(ch)) {
                File* file = dynamic_cast<File*>(ch);
                std::stringstream ss(file->getContent());
                while (std::getline(ss, tmp)) {
                    std::stringstream s2(tmp);
                    std::getline(s2, tmp, ':');
                    if (tmp == "my_dir") {
                        tmp = "";
                        continue;
                    }
                    tmp2 += tmp + "\n";
                }
                file->setContent(tmp2);
                break;
            }
        }

        f = find(st, "home");
        auto child = f->getChildren();
        f = dynamic_cast<Folder*>(child[child.size() - 1]);

        std::queue<Folder*> qu;
        qu.push(f);
        while (!qu.empty()) {
            auto a = qu.front();
            qu.pop();
            int size = a->getChildren().size();
            for (auto ch : a->getChildren()) {
                if (dynamic_cast<File*>(ch)) {
                    delete ch;
                    continue;
                }
                qu.push(dynamic_cast<Folder*>(ch));
            }
            delete a;
        }
    }});
}
