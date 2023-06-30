#include "emuliator.hpp"

void Emuliator::initEmul() {
    filesys = new Folder("/", "/");
    filesys->setParent(nullptr);
    users.push_back(new User("root"));
    // state.setUser(users);
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
    std::cout << "\033[1;31m";
    std::cout << "                                          ██████╗  ██████╗ ███╗   ███╗██╗██╗  ██╗\n";
    std::cout << "                                          ██╔══██╗██╔═══██╗████╗ ████║██║╚██╗██╔╝\n";
    std::cout << "                                          ██████╔╝██║   ██║██╔████╔██║██║ ╚███╔╝ \n";
    std::cout << "                                          ██╔═══╝ ██║   ██║██║╚██╔╝██║██║ ██╔██╗ \n";
    std::cout << "                                          ██║     ╚██████╔╝██║ ╚═╝ ██║██║██╔╝ ██╗\n";
    std::cout << "                                          ╚═╝      ╚═════╝ ╚═╝     ╚═╝╚═╝╚═╝  ╚═╝\n";
    std::cout << "\033[0m"; // Reset color
}