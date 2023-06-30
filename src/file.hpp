#ifndef FILE_
#define FILE_

#include "filesystem.hpp"
#include "folder.hpp"
class File : public FileSystem{
public:
    File(const std::string& n, const std::string& p);
    std::string getName() const override;
    std::string getPath() const override;
    void addContent(const std::string& str) ;
    void remove();
    void display() const override;
    std::string getContent() const;
    void setContent(const std::string&);
    Folder* getParent() const; 
    void setParent(Folder* p);
private:
    Folder* parent;
    std::string content;
};

#include "file.cpp"
#endif  //FILE_