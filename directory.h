#ifndef DIRECTORY_H
#define DIRECTORY_H
#include "node.h"
#include "link.h"
#include "iterator.h"
#include <dirent.h>



class Directory : public Node {

public:
  template<class Item>
  class DirectoryIterator:public Iterator<Item>{
  public:
    DirectoryIterator(Directory *dir):_dir(dir){

    }
    void first(){
      _current = 0;
    }
    Item currentItem() const {
      return _dir->getEntry(_current);
    };
    void next() {
      _current ++;
    }
    bool isDone() const {
      return _current >= _dir->numEntries();
    }
  private:
    Directory *_dir;
    int _current;
  };

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
    n->setParent(this);
  }
  int numEntries(){
    return _children.size();
  }
  Node* getEntry(int index) {
    return _children[index];
  }
  DIR* getDp(){
    return _dp;
  }
  std::vector<Node *> & getChildren(){
    return _children;
  }
  Iterator<Node *> *createIterator(){
    return new DirectoryIterator<Node *>(this);
  }
private:
  //string _name;
  DIR * _dp;
  std::vector<Node *> _children;
};

#endif
