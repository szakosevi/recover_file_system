#include "filesystem.h"

File::File()
{
  this->size = 0;
}

int File::getSize() const
{
  return size;
}

void File::setSize(int size)
{
  this->size = size;
}

std::map<std::string,Directory> Directory::getSubDirs()
{
  return this->subDirs;
}

std::map<std::string,File> Directory::getFiles()
{
  return this->files;
}

File* Directory::addFile(const std::string& name)
{
  auto file=&(*(files.emplace(name,File()).first)).second;
  return file;
}

Directory* Directory::getParent()
{
  return parent;
}


Directory* Directory::addDir(const std::string& name)
{
  /* emplace: if the directory not exist create a new and add */
  auto dir=&(*(subDirs.emplace(name,Directory()).first)).second;
  dir->parent=this;
  return dir;
}