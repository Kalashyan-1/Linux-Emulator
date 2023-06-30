#include "file.hpp"

File::File(const std::string& n, const std::string& p) {
    name = n, 
    path = p;
    permitions = 01230;
}
std::string File::getName() const {return name;}
std::string File::getPath() const {return path;}
void File::addContent(const std::string& str)  {content += str;}
void File::remove() {content = "";}
void File::display() const {std::cout << content << std::endl;}
std::string File::getContent() const {return content;}
void File::setContent(const std::string& str) {content = str;}
Folder* File::getParent() const {return parent;} 
void File::setParent(Folder* p) {parent = p;} 