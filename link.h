#ifndef LINK_H
#define LINK_H

#include "node.h"
#include <sstream>
using std::stringstream;
#include <vector>
using std::vector;

class Link : public Node {
public:
  Link(string const &  linkname,Node *source = nullptr):Node(linkname),_source(source){
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

  // since we only have the link name, in linking to source, we need to prefix it with the path from the current directory ot it
  vector<string> pathToSource(string const & prefix) const {
    string pathName = sourceName(prefix);
    stringstream ss(pathName);
    vector<string> legs;
    char name[256];
    while (ss.getline(name, 256, '/'))
      legs.push_back(name);
    return legs;
  }

  void setSource(Node * src) { _source = src;}

  string sourceName(string const & prefix) const {
      char buf[1024];
      ssize_t len;
      if ((len = readlink((prefix+_name).c_str(), buf, sizeof(buf)-1)) != -1)
        buf[len] = '\0';
      else
        throw string("link source does not exist");
      return string(buf);
    }

private:
  //string _name;
  Node * _source;
};

#endif
