#include "folder.hpp"
#include <algorithm>

Folder::Folder(const std::string& n, const std::string& p) {
    name = n;
    path = p;
    permitions = 01407;
}
std::string Folder::getName() const {
    return name;
}
std::string Folder::getPath() const {
    return path;
}
void Folder::add(FileSystem* component) {
    children.push_back(component);
}
Folder* Folder::getParent() const {
    return parent;
}

void Folder::setParent(Folder* parent) {
    this->parent = parent;
}
void Folder::remove(FileSystem* component) {
    // children.erase(std::remove(children.begin(), children.end(), component), children.end());
    auto it = std::find(children.begin(), children.end(), component);
    if (it != children.end()) {
        children.erase(it);
    }
}

std::vector<FileSystem*> Folder::getChildren() const {return children;}


Folder* Folder::find(const std::string& str) {
    for (int i = 0; i < children.size(); ++i) {
        if (children[i]->getName() == str) {
            Folder* f = dynamic_cast<Folder*>(children[i]);
            if (f) {
             return f;
            } else {
                return nullptr;
            }
        }
    }
    return nullptr;
}

void Folder::display() const {
    std::cout << std::endl;
    for (auto a : children) {
        std::cout << a << " ";
    }
}
