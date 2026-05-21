#include <boost/test/unit_test.hpp>
#include "list.hpp"

#include <utility>


BOOST_AUTO_TEST_CASE(push_front_test)
{
  ulanova::List< int > list;
  list.push_front(1);
  list.push_front(2);
  list.push_front(3);
  ulanova::LIter< int > it = list.begin();
  BOOST_CHECK(*it == 3);
  ++it;
  BOOST_CHECK(*it == 2);
  ++it;
  BOOST_CHECK(*it == 1);
}
BOOST_AUTO_TEST_CASE(front_test)
{
  ulanova::List< int > list;
  list.push_front(1);
  list.push_front(2);
  list.push_front(3);
  BOOST_CHECK(list.front() == 3);
}
BOOST_AUTO_TEST_CASE(front_reference_test)
{
  ulanova::List< int > list;
  list.push_front(1);
  list.front() = 10;
  BOOST_CHECK(list.front() == 10);
}
BOOST_AUTO_TEST_CASE(begin_test)
{
  ulanova::List< int > list;
  list.push_front(1);
  list.push_front(2);
  ulanova::LIter< int > it = list.begin();
  BOOST_CHECK(*it == 2);
}
BOOST_AUTO_TEST_CASE(iterator_increment_test)
{
  ulanova::List< int > list;
  list.push_front(1);
  list.push_front(2);
  list.push_front(3);
  ulanova::LIter< int > it = list.begin();
  BOOST_CHECK(*it == 3);
  ++it;
  BOOST_CHECK(*it == 2);
  ++it;
  BOOST_CHECK(*it == 1);
}
BOOST_AUTO_TEST_CASE(pop_front)
{
  ulanova::List< int > list;
  list.push_front(1);
  list.push_front(2);
  list.push_front(3);
  list.pop_front();
  ulanova::LIter< int > it = list.begin();
  BOOST_CHECK(*it == 2);
}
BOOST_AUTO_TEST_CASE(push_back_basic_test)
{
  ulanova::List< int > list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  ulanova::LIter< int > it = list.begin();
  BOOST_CHECK(*it == 1);
  ++it;
  BOOST_CHECK(*it == 2);
}
BOOST_AUTO_TEST_CASE(insert_after_test)
{
  ulanova::List< int > list;
  list.push_front(1);
  list.push_front(2);
  ulanova::LIter< int > it = list.begin();
  list.insert_after(it,5);
  ++it;
  BOOST_CHECK(*it == 5);
}
BOOST_AUTO_TEST_CASE(erase_after_test)
{
  ulanova::List< int > list;
  list.push_front(1);
  list.push_front(2);
  list.push_front(3);
  ulanova::LIter< int > it = list.begin();
  list.erase_after(it);
  ++it;
  BOOST_CHECK(*it == 1);
}
BOOST_AUTO_TEST_CASE(iterator_traverse_test)
{
  ulanova::List< int > list;
  list.push_front(1);
  list.push_front(2);
  list.push_front(3);
  int sum = 0;
  for (ulanova::LIter< int > it = list.begin(); it != list.end(); ++it)
  {
    sum += *it;
  }
  BOOST_CHECK(sum == 6);
}
BOOST_AUTO_TEST_CASE(const_iterator_test)
{
  ulanova::List< int > list;
  list.push_front(1);
  list.push_front(2);
  const ulanova::List< int >& clist = list;
  ulanova::LCIter< int > it = clist.cbegin();
  BOOST_CHECK(*it == 2);
}
BOOST_AUTO_TEST_CASE(empty_list_iterators_test)
{
  ulanova::List< int > list;
  BOOST_CHECK(list.begin() == list.end());
  BOOST_CHECK(list.cbegin() == list.cend());
}

BOOST_AUTO_TEST_CASE(pop_front_empty_test)
{
  ulanova::List< int > list;
  list.pop_front();
  BOOST_CHECK(list.begin() == list.end());
}

BOOST_AUTO_TEST_CASE(clear_test)
{
  ulanova::List< int > list;
  list.push_back(1);
  list.push_back(2);
  list.clear();
  BOOST_CHECK(list.begin() == list.end());
}

BOOST_AUTO_TEST_CASE(copy_constructor_test)
{
  ulanova::List< int > source;
  source.push_back(1);
  source.push_back(2);

  ulanova::List< int > copy(source);
  source.front() = 10;

  ulanova::LIter< int > it = copy.begin();
  BOOST_CHECK(*it == 1);
  ++it;
  BOOST_CHECK(*it == 2);
}

BOOST_AUTO_TEST_CASE(copy_assignment_test)
{
  ulanova::List< int > source;
  source.push_back(1);
  source.push_back(2);

  ulanova::List< int > copy;
  copy.push_back(9);
  copy = source;

  ulanova::LIter< int > it = copy.begin();
  BOOST_CHECK(*it == 1);
  ++it;
  BOOST_CHECK(*it == 2);
}

BOOST_AUTO_TEST_CASE(move_constructor_test)
{
  ulanova::List< int > source;
  source.push_back(1);
  source.push_back(2);

  ulanova::List< int > moved(std::move(source));

  ulanova::LIter< int > it = moved.begin();
  BOOST_CHECK(*it == 1);
  ++it;
  BOOST_CHECK(*it == 2);
  BOOST_CHECK(source.begin() == source.end());
}

BOOST_AUTO_TEST_CASE(move_assignment_test)
{
  ulanova::List< int > source;
  source.push_back(1);
  source.push_back(2);

  ulanova::List< int > moved;
  moved.push_back(9);
  moved = std::move(source);

  ulanova::LIter< int > it = moved.begin();
  BOOST_CHECK(*it == 1);
  ++it;
  BOOST_CHECK(*it == 2);
  BOOST_CHECK(source.begin() == source.end());
}

BOOST_AUTO_TEST_CASE(postfix_increment_test)
{
  ulanova::List< int > list;
  list.push_back(1);
  list.push_back(2);

  ulanova::LIter< int > it = list.begin();
  BOOST_CHECK(*(it++) == 1);
  BOOST_CHECK(*it == 2);
}

