#include "functions.hpp"
#include <cstddef>
#include <cctype>
#include <limits>

ulanova::List< ulanova::Sequence > ulanova::read_sequences(std::istream& in)
{
  ulanova::List< ulanova::Sequence > sequences;
  std::string name;

  while (in >> name)
  {
    ulanova::Sequence seq;
    seq.name = name;

    while (true)
    {
      int c = in.peek();

      if (c == EOF || c == '\n')
      {
        break;
      }

      if (std::isdigit(c))
      {
        size_t value;
        in >> value;
        seq.values.push_back(value);
      }
      else
      {
        in.get();
      }
    }

    sequences.push_back(seq);
  }

  return sequences;
}

ulanova::List< ulanova::List < size_t > > ulanova::transpose_sequences(const ulanova::List< ulanova::Sequence >& seqs)
{
  ulanova::List< ulanova::List < size_t > > result;

  if (seqs.cbegin() == seqs.cend())
  {
    return result;
  }

  ulanova::List< ulanova::LCIter < size_t > > iters;

  for (ulanova::LCIter < ulanova::Sequence > it = seqs.cbegin(); it != seqs.cend(); ++it)
  {
    iters.push_back(it->values.cbegin());
  }

  bool done = false;

  while (!done)
  {
    done = true;

    ulanova::List< size_t >  row;

    ulanova::LCIter< ulanova::Sequence > seq_it = seqs.cbegin();
    ulanova::LIter< ulanova::LCIter < size_t > > iter_it = iters.begin();

    for (; seq_it != seqs.cend(); ++seq_it, ++iter_it)
    {
      ulanova::LCIter< size_t > & cur = *iter_it;

      if (cur != seq_it->values.cend())
      {
        row.push_back(*cur);
        ++cur;
        done = false;
      }
    }

    if (row.cbegin() != row.cend())
    {
      result.push_back(row);
    }
  }

  return result;
}

ulanova::List< size_t >  ulanova::calculate_sums(const ulanova::List< ulanova::List < size_t > >& seqs)
{
  ulanova::List< size_t >  sums;

  for (ulanova::LCIter< ulanova::List < size_t > > it = seqs.cbegin(); it != seqs.cend(); ++it)
  {
    size_t sum = 0;

    for (ulanova::LCIter< size_t >  jt = it->cbegin(); jt != it->cend(); ++jt)
    {
      size_t value = *jt;
      if (sum > std::numeric_limits< size_t > ::max() - value)
      {
        std::cerr << "overflow\n";
        std::exit(1);
      }
      sum += value;
    }

    sums.push_back(sum);
  }

  return sums;
}

void ulanova::print_sequences(std::ostream& out, const ulanova::List< ulanova::List < size_t > >& seqs)
{
  for (ulanova::LCIter< ulanova::List < size_t > > it = seqs.cbegin(); it != seqs.cend(); ++it)
  {
    bool first = true;

    for (ulanova::LCIter< size_t >  jt = it->cbegin(); jt != it->cend(); ++jt)
    {
      if (!first)
      {
        out << " ";
      }

      out << *jt;
      first = false;
    }

    out << "\n";
  }
}

void ulanova::print_sums(std::ostream& out, const ulanova::List< size_t > & sums)
{
  bool first = true;

  for (ulanova::LCIter< size_t >  it = sums.cbegin(); it != sums.cend(); ++it)
  {
    if (!first)
    {
      out << " ";
    }

    out << *it;
    first = false;
  }

  out << "\n";
}
