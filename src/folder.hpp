#ifndef FOLDER_
#define FOLDER_

#include <vector>

#include "filesystem.hpp"
#include <map>
class Folder : public FileSystem {
public:
    Folder(const std::string& n, const std::string& p);
    std::string getName() const override;
    std::string getPath() const override;
    void add(FileSystem* component) ;
    void remove(FileSystem* component) ;
    void display() const override;
    Folder* getParent() const;
    void setParent(Folder*);
    Folder* find(const std::string& str);
    std::vector<FileSystem*> getChildren() const;
private:    
    std::vector<FileSystem*> children;
    Folder* parent;
};

#endif