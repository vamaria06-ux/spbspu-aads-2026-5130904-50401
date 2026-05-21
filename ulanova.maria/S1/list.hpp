#include <stdexcept>
namespace ulanova
{
  namespace detail
  {
    template < class T >
    struct Node
    {
      T data;
      Node< T >* next;
    };
  }
  template < class T >
  class List;

  template< class T >
  class LIter
  {
  public:
    T& operator*() noexcept;
    LIter& operator++() noexcept;
    LIter operator++(int) noexcept;
    bool operator!=(const LIter& other) const noexcept;
    bool operator==(const LIter& other) const noexcept;
    T* operator->() noexcept;
  private:
    LIter(detail::Node< T >* n = nullptr, detail::Node< T >* h = nullptr);

    detail::Node< T >* node;
    detail::Node< T >* head;

    friend class List< T >;
  };

  template< class T >
  class LCIter
  {
  public:
    const T& operator*() const noexcept;
    LCIter& operator++() noexcept;
    LCIter operator++(int) noexcept;
    bool operator!=(const LCIter& other) const noexcept;
    bool operator==(const LCIter& other) const noexcept;
    const T* operator->() const noexcept;
  private:
    LCIter(detail::Node< T >* n = nullptr, detail::Node< T >* h = nullptr);

    detail::Node< T >* node;
    detail::Node< T >* head;

    friend class List< T >;
  };

  template < class T >
  class List
  {
  public:
    List();
    List(const List& other);
    List(List&& other) noexcept;
    ~List();

    List& operator=(const List& other);
    List& operator=(List&& other) noexcept;

    void push_front(const T& value) noexcept;
    void push_back(const T& value) noexcept;
    void pop_front() noexcept;

    LIter< T > insert_after(LIter< T > pos, const T& value) noexcept;
    void erase_after(LIter< T > pos) noexcept;

    LIter< T > begin() noexcept;
    LIter< T > end() noexcept;

    LCIter< T > cbegin() const noexcept;
    LCIter< T > cend() const noexcept;

    void clear();

    T& front();
  private:
    detail::Node< T >* head;
  };

  template < class T >
  T& LIter< T>::operator*() noexcept
  {
    return node->data;
  }

  template < class T >
  LIter< T >& LIter< T >::operator++() noexcept
  {
    if (!node)
    {
      return *this;
    }
    node = node->next;
    if (node == head)
    {
      node = nullptr;
    }
    return *this;
  }

  template< class T >
  LIter< T > LIter< T >::operator++(int) noexcept
  {
    LIter< T > result(*this);
    ++(*this);
    return result;
  }

  template < class T >
  bool LIter< T >::operator!=(const LIter& other) const noexcept
  {
    return node != other.node;
  }

  template < class T >
  bool LIter< T >::operator==(const LIter& other) const noexcept
  {
    return node == other.node;
  }

  template < class T >
  T* LIter< T >::operator->() noexcept
  {
    return &(node->data);
  }

  template< class T >
  LIter< T >::LIter(detail::Node< T >* n, detail::Node< T >* h):
    node(n),
    head(h)
  {}

  template < class T >
  const T& LCIter< T >::operator*() const noexcept
  {
    return node->data;
  }

  template < class T >
  LCIter< T> & LCIter< T >::operator++() noexcept
  {
    if (!node)
    {
      return *this;
    }
    node = node->next;
    if (node == head)
    {
      node = nullptr;
    }
    return *this;
  }

  template< class T >
  LCIter< T > LCIter< T >::operator++(int) noexcept
  {
    LCIter< T > result(*this);
    ++(*this);
    return result;
  }

  template < class T >
  bool LCIter< T >::operator!=(const LCIter& other) const noexcept
  {
    return node != other.node;
  }

  template < class T >
  bool LCIter< T >::operator==(const LCIter& other) const noexcept
  {
    return node == other.node;
  }

  template < class T >
  const T* LCIter< T >::operator->() const noexcept
  {
    return &(node->data);
  }

  template< class T >
  LCIter< T >::LCIter(detail::Node< T >* n, detail::Node< T >* h):
    node(n),
    head(h)
  {}


  template< class T >
  List< T >::List() : head(nullptr) {}
  template< class T >
  List< T >::List(const List& other) : head(nullptr)
  {
    for (LCIter< T > it = other.cbegin(); it != other.cend(); ++it)
    {
      push_back(*it);
    }
  }

  template< class T >
  List< T >::List(List< T >&& other) noexcept:
    head(other.head)
  {
    other.head = nullptr;
  }

  template< class T >
  List< T >::~List()
  {
    clear();
  }

  template< class T >
  List< T >& List< T >::operator=(const List< T >& other)
  {
    if (this != &other)
    {
      List< T > temp(other);
      swap(temp);
    }
    return *this;
  }

  template< class T >
  List< T >& List< T >::operator=(List< T >&& other) noexcept
  {
    if (this != &other)
    {
      clear();
      head = other.head;
      other.head = nullptr;
    }
    return *this;
  }

  template < class T >
  void List< T >::push_front(const T& value) noexcept
  {
    detail::Node< T >* new_node = new detail::Node< T >{value,nullptr};
    if (!head)
    {
      head = new_node;
      head->next = head;
      return;
    }
    detail::Node< T >* last = head;
    while (last->next != head)
    {
      last = last->next;
    }
    new_node->next = head;
    last->next = new_node;
    head = new_node;
  }
  template < class T >
  void List< T >::push_back(const T& value) noexcept
  {
    detail::Node< T >* new_node = new detail::Node< T >{value,nullptr};
    if(!head)
    {
      head = new_node;
      head->next = head;
      return;
    }
    detail::Node< T >* last = head;
    while (last ->next != head)
    {
      last = last->next;
    }
    last->next = new_node;
    new_node->next = head;
  }
  template < class T >
  void List< T >::pop_front() noexcept
  {
    if (!head)
    {
      return;
    }
    if (head->next == head)
    {
      delete head;
      head = nullptr;
      return;
    }
    detail::Node< T >* last = head;
    while (last->next != head)
    {
      last = last->next;
    }
    detail::Node< T >* temp = head;
    head = head->next;
    last->next = head;
    delete temp;
  }

  template < class T >
  T& List< T >::front()
  {
    if (!head)
    {
      throw std::logic_error("empty list");
    }
    return head->data;
  }

  template < class T >
  LIter< T > List< T >::begin() noexcept
  {
    return LIter< T >(head,head);
  }
  template < class T >
  LIter< T > List< T >::end() noexcept
  {
    return LIter< T >(nullptr,head);
  }

  template < class T >
  LCIter< T > List< T >::cbegin() const noexcept
  {
    return LCIter< T >(head,head);
  }
  template < class T >
  LCIter< T > List< T >::cend() const noexcept
  {
    return LCIter< T >(nullptr,head);
  }

  template < class T >
  void List< T >::clear()
  {
    while (head)
    {
      pop_front();
    }
  }

  template < class T >
  LIter< T > List< T >::insert_after(LIter< T > pos, const T& value) noexcept
  {
    if (!pos.node)
    {
      return end();
    }
    detail::Node< T >* new_node = new detail::Node< T >{value, pos.node->next};
    pos.node->next = new_node;
    return LIter< T >(new_node, head);
  }
  template < class T >
  void List< T >::erase_after(LIter< T > pos) noexcept
  {
    if (!pos.node)
    {
      return;
    }
    detail::Node< T >* temp = pos.node->next;
    if (!temp)
    {
      return;
    }
    if (temp == head)
    {
      if (head->next == head)
      {
        delete head;
        head = nullptr;
        return;
      }
      head = head->next;
    }
    pos.node->next = temp->next;
    delete temp;
  }
}
