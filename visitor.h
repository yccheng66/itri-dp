#ifndef VISITOR_H
#define VISITOR_H

class File;
class Link;
class Directory;

class Visitor {
public:
  virtual void visit(File *)=0;
  virtual void visit(Link *)=0;
  virtual void visit(Directory *)=0;
};

#endif
