#include "emulator.hpp"
int User::id = 1000;

void Emuliator::initEmul() {
    filesys = new Folder("/", "/");
    filesys->setParent(nullptr);
    users.push_back(new User("root"));
    Folder* tmp = new Folder("etc", "/");
    tmp->setParent(filesys);
    filesys->add(tmp);
    File* f = new File("passwd", "/etc");
    f->setParent(tmp);
    tmp->add(f);
    f = new File("shadow", "/etc");
    f->setParent(tmp);
    tmp->add(f);
    f = new File("sudoers", "/etc");
    f->setParent(tmp);
    tmp->add(f);
    f = new File("group", "/etc");
    f->setParent(tmp);
    tmp->add(f);

    tmp = new Folder("home", "/");
    tmp->setParent(filesys);
    filesys->add(tmp); 
    tmp = new Folder("usr", "/");
    tmp->setParent(filesys);
    filesys->add(tmp);
    state.setCurrentState(filesys);
    state.setPreviousState(nullptr);
    state.setRoot(filesys);
    intiMap();
    scenar.initScen();
    info();
}

void Emuliator::intiMap() {
    commands["cd"] = new Cd("cd");
    commands["mkdir"] = new Mkdir("mkdir");
    commands["rm"] = new Rm("rm");
    commands["adduser"] = new Adduser("adduser");
    commands["deluser"] = new Deluser("deluser");
    commands["su"] = new Su("su");
    commands["pwd"] = new Pwd("pwd");
}

std::string parse(const std::string& com) {
    std::istringstream iss(com);
    std::string firstWord;
    iss >> firstWord;
    return firstWord;
}

void Emuliator::run() {
    initEmul();
    std::string com;
    auto scen = scenar.getScen();


    for (auto it = scen[0].begin(); it != scen[0].end(); ++it) {
        auto com = commands[it->first];
        com->execute(state, result, it->second);
    }
   
    result.printFinalRes();
}



void Emuliator::info() {
    std::cout << "\n\n\n";
    std::cout << "\033[1;33m";
    std::cout << "                                          ██████╗  ██████╗ ███╗   ███╗██╗██╗  ██╗\n";
    std::cout << "                                          ██╔══██╗██╔═══██╗████╗ ████║██║╚██╗██╔╝\n";
    std::cout << "                                          ██████╔╝██║   ██║██╔████╔██║██║ ╚███╔╝ \n";
    std::cout << "                                          ██╔═══╝ ██║   ██║██║╚██╔╝██║██║ ██╔██╗ \n";
    std::cout << "                                          ██║     ╚██████╔╝██║ ╚═╝ ██║██║██╔╝ ██╗\n";
    std::cout << "                                          ╚═╝      ╚═════╝ ╚═╝     ╚═╝╚═╝╚═╝  ╚═╝\n\n\n";


    std::cout << " POMIX is an educational program powered by Khachik Kalashyan that emulates Linux commands and quizzes users on their knowledge of these commands.\n " << 
    "It is providing a hands-on learning experience for users to practice using various Linux commands.\n\n\nLet's Start\n" << std::endl;

    std::cout << "\033[0m"; // Reset color

}