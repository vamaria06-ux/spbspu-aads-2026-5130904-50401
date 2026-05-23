#ifndef BSTREE_HPP
#define BSTREE_HPP

#include <cstddef>
#include <utility>

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
      virtual ~NodeBase() = default;
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

  private:
    detail::NodeBase* fake_root_;
    detail::NodeBase* fake_leaf_;
    size_t size_;
    Compare compare_;

    void create_fakes();
    void clear_from(detail::NodeBase* node) noexcept;
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

#endif
