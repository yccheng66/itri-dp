#ifndef ITERATOR
#define ITERATOR

template<class Item>
class Iterator{
public:
  virtual void first() = 0;
  virtual Item currentItem() const = 0;
  virtual void next() = 0;
  virtual bool isDone() const = 0;

  virtual ~Iterator() {}

};

template<class Item>
class NullIterator:public Iterator<Item>{
public:
  void first() {}
  Item currentItem() const {
    return Item();
  }
  void next() {}
  bool isDone() const {
    return true;
  }
};

#endif
