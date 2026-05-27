#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <list.hpp>
#include <stdexcept>

namespace ulanova
{
  template <class T>
  class Queue
  {
  public:
    void push(const T& value);
    void clear();
    T drop();
    bool empty() const;
  private:
    List<T> list_;
  };

  template <class T>
  void Queue<T>::push(const T& value)
  {
    list_.push_back(value);
  }
  template <class T>
  void Queue<T>:: clear()
  {
    while (!empty())
    {
      drop();
    }
  }
  template <class T>
  T Queue<T>::drop()
  {
    if (empty())
    {
      throw std::runtime_error("Queue is empty");
    }
    T value = list_.front();
    list_.pop_front();
    return value;
  }
  template <class T>
  bool Queue<T>::empty() const
  {
    return list_.empty();
  }
}
#endif
