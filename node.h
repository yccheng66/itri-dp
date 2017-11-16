#ifndef NODE_H
#define NODE_H
#include <string>
#include <fstream>
#include <sys/stat.h>

using std::string;

class Node {
public:
  virtual string name() const = 0;
  virtual int getCharCount() const = 0;
};


class File : public Node {
public:
  // File(string const &  s):_name(s){
  File(string const &  s):_name(s){
    if (stat(name().c_str(), &_st) != 0)
         throw string("file does not exist");
  }
  string name() const {return _name;}
  int getCharCount() const {
    return _st.st_size;
  }
private:
  string _name;
  struct stat _st;
};

#include <dirent.h>

class Directory : public Node {
public:
  Directory(string const & s):_name(s) {
    if ((_dp =  opendir(_name.c_str())) == NULL)
      throw string("directory does not exit");
  }
  string name() const {return _name;}
  int getCharCount() const {
    throw string("is a directory");
  }
private:
  string _name;
  DIR * _dp;
};
#endif
