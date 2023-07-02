#include "cd.hpp"
 

Cd::Cd(const std::string& n) {name = n; initQuests();}

void Cd::execute(State& st, Result& result, int i) {
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

void Cd::find(State& state, const std::string& str) {
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
    if (fold) {
        state.setPreviousState(state.getCurrentState());
        state.setCurrentState(fold);
    }
    
}

void parse() {}

void Cd::initQuests()  {
    Qusetion* q = new Qusetion("Change directory to home.", {"cd ", "cd /home "});
    quests.push_back({q, [&](State& st) {
        find(st, "home");            
    }});
    q = new Qusetion("Change the directory to its parent.", {"cd .. ", "cd / "});
    quests.push_back({q, [&](State& st) {
        st.setPreviousState(st.getCurrentState());
        st.setCurrentState(st.getCurrentState()->getParent());
        
    }});
    q = new Qusetion("Change the previous directory.", {"cd - ",  "cd /home "});
    quests.push_back({q, [&](State& st) {
        Folder* f = st.getPreviousState();
        st.setPreviousState(st.getCurrentState());
        st.setCurrentState(f);
        
    }});
    q = new Qusetion("Change directory to the newly created one", {"cd my_dir ", "cd ./my_dir ", "cd /home/my_dir "});
    quests.push_back({q, [&](State& st) {
        Folder* f = st.getCurrentState();
        std::string str =  f->getPath() + f->getName() + '/' + "my_dir";
        if (str[0] == '/') {
            str.erase(str.begin());
        }
        find(st, str);
    }});
}



































 // std::vector<std::string> vec;
    // std::stringstream ss(str);
    // while (ss >> str) {
    //     vec.push_back(str);
    // }
    // if (vec.size() == 1){
    //     std::string tempStr;
    //     Folder* fold = state.getRoot();
    //         auto children = fold->getChildren();
    //         for (auto a : children) {
    //             if (a->getName() == "home") {
    //                 fold = dynamic_cast<Folder*>(a);
    //             } 
    //         }
        
    //     if (fold) {
    //         state.setPreviousState(state.getCurrentState());
    //         state.setCurrentState(fold);
    //     }
    // }
    

    // if (vec.size() == 2) {
    //     if (vec[1].size() == 1 && vec[1][0] == '-') {  // cd -
    //         auto tmp = state.getCurrentState();
    //         state.setCurrentState(state.getPreviousState());
    //         state.setPreviousState(tmp);
    //     } else if (vec[1].size() == 2 && vec[1] == "..") {   // cd ..
    //         state.setPreviousState(state.getCurrentState());
    //         state.setCurrentState(state.getCurrentState()->getParent());
    //     } else {
    //         if (vec[1].size() > 2 && vec[1][0] == '.' && vec[1][1] == '/') { // cd ./dir
    //             std::string tempStr;
    //             std::string tmp2(vec[1].begin() + 2, vec[1].end());
    //             std::stringstream ss(vec[1]);
    //             bool flag = true;
    //             Folder* fold = state.getCurrentState();
    //             while (std::getline(ss, tempStr, '/') && flag) {
    //                 auto children = fold->getChildren();
    //                 for (auto a : children) {
    //                     if (a->getName() == tempStr && dynamic_cast<Folder*>(a)) {
    //                         fold = dynamic_cast<Folder*>(a);
    //                     } else {
    //                         std::cout << "cd: "+tempStr+": No such file or directory" << std::endl;
    //                         fold = nullptr;
    //                         flag = false;
    //                         break;
    //                     }
    //                 }
    //             }
    //             if (fold) {
    //                 state.setPreviousState(state.getCurrentState());
    //                 state.setCurrentState(fold);
    //             }

    //             // std::string tempStr(vec[1].begin() + 2, vec[1].end());
    //             // auto children = state.getCurrentState()->getChildren();
    //             // for (auto a : children) {
    //             //     if (a->getName() == tempStr && dynamic_cast<Folder*>(a)) {
    //             //         state.setPreviousState(state.getCurrentState());
    //             //         state.setCurrentState(dynamic_cast<Folder*>(a));
    //             //     } else if (a->getName() == tempStr && !dynamic_cast<Folder*>(a)) {
    //             //         std::cout << tempStr + " :is not a directory" << std::endl;
    //             //     } else {
    //             //         std::cout << "cd: "+tempStr+": No such file or directory" << std::endl;
    //             //     }
    //             // }
    //         } else if (vec[1].size() > 2 && vec[1][0] == '/') {
    //             std::string tempStr;
    //             std::stringstream ss(vec[1]);
    //             bool flag = true;
    //             Folder* fold = state.getRoot();
    //             while (std::getline(ss, tempStr, '/') && flag) {
    //                 auto children = fold->getChildren();
    //                 for (auto a : children) {
    //                     if (a->getName() == tempStr && dynamic_cast<Folder*>(a)) {
    //                         fold = dynamic_cast<Folder*>(a);
    //                     } else {
    //                         std::cout << "cd: "+tempStr+": No such file or directory" << std::endl;
    //                         fold = nullptr;
    //                         flag = false;
    //                         break;
    //                     }
    //                 }
    //             }
    //             if (fold) {
    //                 state.setPreviousState(state.getCurrentState());
    //                 state.setCurrentState(fold);
    //             }
    //         }
    //     }
    // } else {
    //     if (vec[1][0] == '-') {
    //         std::cout << "the option is not correcrt or is not implemeted yet" << std::endl;
    //     }
    // }

    // for (auto a : quests) {

    // }
    