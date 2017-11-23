#ifndef DIRECTORY_ITERATOR
#define DIRECTORY_ITERATOR
#include "directory.h"
class DirectoryIterator{
public:
  DirectoryIterator(Directory *dir):_dir(dir){

  };
private:
  Directory *_dir;
};

#endif
