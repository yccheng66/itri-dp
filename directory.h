#ifndef DIRECTORY_H
#define DIRECTORY_H
#include "node.h"
#include "link.h"
#include <dirent.h>

class Directory : public Node {
public:
  Directory(string const & s):Node(s) {
    if ((_dp =  opendir(_name.c_str())) == NULL)
      throw string("directory does not exit");
  }
  string name() const {return _name;}
  int getCharCount() const {
    throw string("is a directory");
  }
  void addEntry(Node * n){
    _children.push_back(n);
  }
  int numEntries(){
    return _children.size();
  }
  Node* getEntry(int index) {
    return _children[index];
  }
  void populateEntries() {
    struct dirent * entry = nullptr;
    if (0 == chdir(name().c_str()))
      while ((entry = readdir(_dp)) != nullptr) {
        if (entry->d_type == DT_REG)
          addEntry(new File(entry->d_name));
        else if (entry->d_type == DT_DIR)
          addEntry(new Directory(entry->d_name));
        else if (entry->d_type == DT_LNK)
          addEntry(new Link(entry->d_name, nullptr));
      }
    else
      throw string("chdir error");
    sort(_children.begin(), _children.end(), [](Node* a, Node * b){return a->name() < b->name();});
  }
private:
  //string _name;
  DIR * _dp;
  std::vector<Node *> _children;
};

#endif
