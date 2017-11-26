#ifndef CHAR_COUNT_VISITOR_H
#define CHAR_COUNT_VISITOR_H
#include "visitor.h"
#include "node.h"
#include "link.h"
#include "directory.h"

class CharCountVisitor : public Visitor {
public:
  CharCountVisitor():_count(0) { }
  virtual void visit(File * file) { _count += file->getCharCount();}
  virtual void visit(Link * link) {
    Node * n= link->getSource();
    if (n)
      n->accept(*this);
    }
  virtual void visit(Directory * dir) {
    Iterator<Node *> * it = dir->createIterator();
  for (; !it->isDone(); it->next())
    if (it->currentItem()->name() != "." && it->currentItem()->name() != "..")
      it->currentItem()->accept(*this);
  }
  int getResult () const {return _count;}
private:
  int _count;
};

class SuffixVisitor : public Visitor {
public:
  SuffixVisitor(): _sname("") {}
  void visit(File * file) {_sname = file->name();}
  void visit(Link * link) {_sname = link->name()+"@";}
  void visit(Directory *dir) {_sname = dir->name()+"/";}
  string getResult () const {return _sname;}
private:
  string _sname;
};
#endif
