#ifndef LINK_H
#define LINK_H

#include "node.h"
class Link : public Node {
public:
  Link(string const &  linkname,Node *source):Node(linkname),_source(source){
    //if (stat(name().c_str(), &_st) != 0)
    //       throw string("file does not exist");

  }
  string name() const {return _name;}
  int getCharCount() const {
    return _source->getCharCount();
  }
  void addEntry(Node * n){
    throw string("unable to add entry to a file");
  }
  int numEntries(){
    throw string("illegal action");
  }

private:
  //string _name;

  Node * _source;
};

#endif
