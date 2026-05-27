#ifndef STACK_HPP
#define STACK_HPP
#include <list.hpp>
#include <stdexcept>
#include <utility>

namespace ulanova
{
  template < class T >
  class Stack
  {
  public:
    void push(const T& value);
    void push(T&& value);
    void clear();
    T drop();
    T& front();
    bool empty();
  private:
    List< T > list_;
  };

  template < class T >
  void Stack< T >::push(const T& value)
  {
    list_.push_front(value);
  }
  template< class T >
  void Stack< T >::push(T&& value)
  {
    list_.push_front(std::move(value));
  }
  template < class T >
  void Stack< T >::clear()
  {
    while (!empty())
    {
      drop();
    }
  }
  template < class T >
  T Stack< T >::drop()
  {
    if (empty())
    {
      throw std::runtime_error("Stack is empty");
    }
    T value = list_.front();
    list_.pop_front();
    return value;
  }
  template < class T >
  T& Stack< T >::front()
  {
    if(empty())
    {
      throw std::runtime_error("Stack is empty");
    }
    return list_.front();
  }
  template < class T >
  bool Stack< T >::empty()
  {
    return list_.empty();
  }
}
#endif
