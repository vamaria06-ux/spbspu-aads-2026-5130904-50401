#ifndef BSTREE_HPP
#define BSTREE_HPP

#include <cstddef>
#include <utility>
#include <stdexcept>

namespace ulanova
{
  namespace detail
  {
    struct NodeBase
    {
      NodeBase* parent;
      NodeBase* left;
      NodeBase* right;
      size_t height;

      NodeBase();
      NodeBase(NodeBase* parent_node, NodeBase* left_node, NodeBase* right_node);
      virtual ~NodeBase();
    };

    template< class Key, class Value >
    struct Node: NodeBase
    {
      std::pair< const Key, Value > data;

      Node( const Key& key, const Value& value, NodeBase* parent_node, NodeBase* fake_leaf);
    };
  };

  template< class Key, class Value, class Compare >
  class BSTree
  {
  public:
    BSTree();
    ~BSTree();

    bool empty() const noexcept;
    size_t size() const noexcept;
    void clear() noexcept;

    void push(const Key& key, const Value& value);

    bool contains(const Key & key) const noexcept;
    Value & at(const Key & key);
    const Value & at(const Key & key) const;

  private:
    detail::NodeBase* fake_root_;
    detail::NodeBase* fake_leaf_;
    size_t size_;
    Compare compare_;

    void create_fakes();
    void clear_from(detail::NodeBase* node) noexcept;

    using node_t = detail::Node< Key, Value >;

    node_t * as_node(detail::NodeBase* node) const noexcept;
    void update_height(detail::NodeBase* node) noexcept;
    size_t get_height(detail::NodeBase* node) const noexcept;

    detail::NodeBase * find_node(const Key & key) const noexcept;
  };
}

template< class Key, class Value >
ulanova::detail::Node< Key, Value >::Node(
  const Key& key,
  const Value& value,
  ulanova::detail::NodeBase* parent_node,
  ulanova::detail::NodeBase* fake_leaf
):
  ulanova::detail::NodeBase(parent_node, fake_leaf, fake_leaf),
  data(key, value)
{
  height = 1;
}

template< class Key, class Value, class Compare >
ulanova::BSTree< Key, Value, Compare >::BSTree():
  fake_root_(nullptr),
  fake_leaf_(nullptr),
  size_(0),
  compare_(Compare())
{
  create_fakes();
}

template< class Key, class Value, class Compare >
ulanova::BSTree< Key, Value, Compare >::~BSTree()
{
  if (fake_root_ != nullptr)
  {
    clear(),
    delete fake_root_;
    delete fake_leaf_;
  }
}

template< class Key, class Value, class Compare >
bool ulanova::BSTree< Key, Value, Compare >::empty() const noexcept
{
  return size_ == 0;
}

template< class Key, class Value, class Compare >
std::size_t ulanova::BSTree< Key, Value, Compare >::size() const noexcept
{
  return size_;
}

template< class Key, class Value, class Compare >
void ulanova::BSTree< Key, Value, Compare >::clear() noexcept
{
  clear_from(fake_root_->left);
  fake_root_->left = fake_leaf_;
  fake_root_->right = fake_leaf_;
  size_ = 0;
}

template< class Key, class Value, class Compare >
void ulanova::BSTree< Key, Value, Compare >::create_fakes()
{
  fake_leaf_ = new detail::NodeBase();
  try
  {
    fake_root_ = new detail::NodeBase(nullptr, fake_leaf_, fake_leaf_);
  }
  catch (...)
  {
    delete fake_leaf_;
    fake_leaf_ = nullptr;
    throw;
  }
}

template< class Key, class Value, class Compare >
void ulanova::BSTree< Key, Value, Compare >::clear_from(detail::NodeBase * node) noexcept
{
  if (node == fake_leaf_)
  {
    return;
  }

  clear_from(node->left);
  clear_from(node->right);
  delete node;
}

template< class Key, class Value, class Compare >
void ulanova::BSTree< Key, Value, Compare >::push(const Key & key, const Value & value)
{
  detail::NodeBase * parent = fake_root_;
  detail::NodeBase * current = fake_root_->left;

  while (current != fake_leaf_)
  {
    node_t * current_node = as_node(current);
    parent = current;

    if (compare_(key, current_node->data.first))
    {
      current = current->left;
    }
    else if (compare_(current_node->data.first, key))
    {
      current = current->right;
    }
    else
    {
      current_node->data.second = value;
      return;
    }
  }

  detail::NodeBase * new_node = new node_t(key, value, parent, fake_leaf_);

  if (parent == fake_root_)
  {
    fake_root_->left = new_node;
  }
  else
  {
    node_t * parent_node = as_node(parent);
    if (compare_(key, parent_node->data.first))
    {
      parent->left = new_node;
    }
    else
    {
      parent->right = new_node;
    }
  }

  ++size_;

  while (parent != nullptr)
  {
    update_height(parent);
    parent = parent->parent;
  }
}

template< class Key, class Value, class Compare >
typename ulanova::BSTree< Key, Value, Compare >::node_t *
ulanova::BSTree< Key, Value, Compare >::as_node(detail::NodeBase * node) const noexcept
{
  return static_cast< node_t * >(node);
}

template< class Key, class Value, class Compare >
std::size_t ulanova::BSTree< Key, Value, Compare >::get_height(detail::NodeBase * node) const noexcept
{
  if (node == fake_leaf_)
  {
    return 0;
  }
  return node->height;
}

template< class Key, class Value, class Compare >
void ulanova::BSTree< Key, Value, Compare >::update_height(detail::NodeBase * node) noexcept
{
  const std::size_t left_height = get_height(node->left);
  const std::size_t right_height = get_height(node->right);

  if (left_height > right_height)
  {
    node->height = left_height + 1;
  }
  else
  {
    node->height = right_height + 1;
  }
}

template< class Key, class Value, class Compare >
bool ulanova::BSTree< Key, Value, Compare >::contains(const Key & key) const noexcept
{
  return find_node(key) != fake_leaf_;
}

template< class Key, class Value, class Compare >
Value & ulanova::BSTree< Key, Value, Compare >::at(const Key & key)
{
  detail::NodeBase * node = find_node(key);
  if (node == fake_leaf_)
  {
    throw std::out_of_range("key not found");
  }

  return as_node(node)->data.second;
}

template< class Key, class Value, class Compare >
const Value & ulanova::BSTree< Key, Value, Compare >::at(const Key & key) const
{
  detail::NodeBase * node = find_node(key);
  if (node == fake_leaf_)
  {
    throw std::out_of_range("key not found");
  }

  return as_node(node)->data.second;
}

template< class Key, class Value, class Compare >
ulanova::detail::NodeBase *
ulanova::BSTree< Key, Value, Compare >::find_node(const Key & key) const noexcept
{
  detail::NodeBase * current = fake_root_->left;

  while (current != fake_leaf_)
  {
    node_t * current_node = as_node(current);

    if (compare_(key, current_node->data.first))
    {
      current = current->left;
    }
    else if (compare_(current_node->data.first, key))
    {
      current = current->right;
    }
    else
    {
      return current;
    }
  }

  return fake_leaf_;
}

#endif
