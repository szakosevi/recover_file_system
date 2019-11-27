#include <iostream>
#include <string>
#include <stdlib.h>
#include <map>
#ifndef FILESYSTEM_H
#define FILESYSTEM_H

class File
{
  private:
    int size;

  public:
    File(int s);
    File();
    int getSize() const;
    void setSize(int size);
};

class Directory
{
  private: 
    std::map<std::string,File> files;
    std::map<std::string,Directory> subDirs;
    Directory* parent;

  public:
    Directory() :files(), subDirs(), parent(nullptr){}
    std::map<std::string,Directory> getSubDirs();
    std::map<std::string,File> getFiles();
    Directory* getParent();
    Directory* addDir(const std::string& name);
    File* addFile(const std::string& name);
    friend std::ostream& operator<<(std::ostream& out, const Directory& d);
};

#endif