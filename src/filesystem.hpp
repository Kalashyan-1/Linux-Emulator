#ifndef FILE_SYS_
#define FILE_SYS_

#include <string>
#include <iostream>

#define READ_PERMISSION  4
#define WRITE_PERMISSION  2
#define EXECUTE_PERMISSION 1

class FileSystem {
public:
    virtual std::string getName() const = 0;
    virtual std::string getPath() const = 0;
    virtual void display() const = 0;
    int setPermissions(int owner, int group, int other) {
        return (owner * 8 * 8) + (group * 8) + other;
    }
protected:
    std::string path;
    std::string name;
    int permitions;
}; 

#endif   //FILE_SYS_