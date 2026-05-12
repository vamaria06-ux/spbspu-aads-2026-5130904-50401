#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <cstddef>
#include <utility>

#include "top_it_vector.hpp"

namespace ulanova
{
  template <class Key, class Value, class Hash, class Equal>
  class HashTable
  {
    explicit HashTable(size_t slots = 8);
    HashTable(size_t slots, const Hash& hash, const Equal& equal);

    void swap(HashTable& rhs) noexcept;

    bool isEmpty() const noexcept;
    size_t getsize() const noexcept;
    size_t getcapacity() const noexcept;

  private:
    enum class BucketState
    {
      Empty,
      Occupied,
      Deleted
    };

    struct Bucket
    {
      BucketState state;
      Key key;
      Value value;

      Bucket():
        state(BucketState::Empty),
        key(),
        value()
      {}
    };
    Vector<Bucket> buckets_;
    size_t size_;
    Hash hash_;
    Equal equal_;

    static const size_t npos = static_cast<size_t>(-1);

    size_t findIndex(const Key& key) const;
    size_t findPlace(const Key& key, bool& found) const;
    size_t nextIndex(size_t index) const noexcept;
  };
}
template <class Key, class Value, class Hash, class Equal>
ulanova::HashTable<Key, Value, Hash, Equal>::HashTable(size_t slots):
  buckets_(slots),
  size_(0),
  hash_(),
  equal_()
{}

template <class Key, class Value, class Hash, class Equal>
ulanova::HashTable<Key, Value, Hash, Equal>::HashTable(size_t slots, const Hash& hash, const Equal& equal):
  buckets_(slots),
  size_(0),
  hash_(hash),
  equal_(equal)
{}

template <class Key, class Value, class Hash, class Equal>
void ulanova::HashTable<Key, Value, Hash, Equal>::swap(HashTable& rhs) noexcept
{
  buckets_.swap(rhs.buckets_);
  std::swap(size_, rhs.size_);
  std::swap(hash_, rhs.hash_);
  std::swap(equal_, rhs.equal_);
}

template <class Key, class Value, class Hash, class Equal>
bool ulanova::HashTable<Key, Value, Hash, Equal>::isEmpty() const noexcept
{
  return size_ == 0;
}

template <class Key, class Value, class Hash, class Equal>
size_t ulanova::HashTable<Key, Value, Hash, Equal>::getsize() const noexcept
{
  return size_;
}

template <class Key, class Value, class Hash, class Equal>
size_t ulanova::HashTable<Key, Value, Hash, Equal>::getcapacity() const noexcept
{
  return buckets_.getsize();
}

template <class Key, class Value, class Hash, class Equal>
size_t ulanova::HashTable<Key, Value,Hash,Equal>::nextIndex(size_t index) const noexcept
{
  return (index + 1) % buckets_.getsize();
}

template <class Key, class Value, class Hash, class Equal>
size_t ulanova::HashTable<Key,Value, Hash, Equal>::findIndex(const Key& key) const
{
  if (buckets_.isEmpty())
  {
    return npos;
  }
  size_t index = hash_(key) % buckets_.getsize();
  for (size_t i = 0; i < buckets_.getsize(); ++i)
  {
    const Bucket& bucket = buckets_[index];
    if (bucket.state == BucketState::Empty)
    {
      return npos;
    }
    if (bucket.state == BucketState::Occupied && equal_(bucket.key, key))
    {
      return index;
    }
    index = nextIndex(index);
  }
  return npos;

}
#endif
