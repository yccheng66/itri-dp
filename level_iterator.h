#ifndef LEVEL_ITERATOR_H
#define LEVEL_ITERATOR_H
#include <queue>
#include "directory.h"
#include "iterator.h"

template<class Item>
class LevelIterator:public Iterator<Item>{
public:
  LevelIterator(Directory *dir):_dir(dir), _itq(nullptr) {
  }

  void first() {
    if (_itq)
      delete _itq;

    Iterator<Item>* firstIterator = _dir->createIterator();
    firstIterator->first();
    _itq = new std::queue<Iterator<Item> *>;
    _itq->push(firstIterator);
  }

  Item currentItem() const {
    return _itq->front()->currentItem();
  };

  void next() {
    _itq->front()->next();
    if (_itq->front()->isDone()) {
      _itq->pop();
    }
    else {
      Iterator<Item> *it = _itq->front()->currentItem()->createIterator();
      if (!it->isDone())
      {
        it->first();
        _itq->push(it);
      }
    }
  }

  bool isDone() const {
    return _itq->empty();
  }

private:
  Directory *_dir;
  std::queue<Iterator<Item> *> *_itq;
};


#endif
