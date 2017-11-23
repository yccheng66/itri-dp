#ifndef DIRECTORY_BUILDER_H
#define DIRECTORY_BUILDER_H
#include "node.h"
#include "link.h"
#include "directory.h"

class DirectoryBuilder{
public:
    DirectoryBuilder(){}
    void buildDirectory(string const & path){
      _dir = new Directory(path);
      populateEntries();
    }
    Directory* getDirectory() const{
      return _dir;
    }
private:
  Directory* _dir;
  void populateEntries() {
    struct dirent * entry = nullptr;
    if (0 == chdir(_dir->name().c_str()))
      while ((entry = readdir(_dir->getDp())) != nullptr) {
        if (entry->d_type == DT_REG)
          _dir->addEntry(new File(entry->d_name));
        else if (entry->d_type == DT_DIR)
          _dir->addEntry(new Directory(entry->d_name));
        else if (entry->d_type == DT_LNK)
          _dir->addEntry(new Link(entry->d_name, nullptr));
      }
    else
      throw string("chdir error");
    sort(_dir->getChildren().begin(), _dir->getChildren().end(), [](Node* a, Node * b){return a->name() < b->name();});
  }

};

#endif
