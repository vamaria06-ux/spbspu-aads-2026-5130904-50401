#include "postfix.hpp"
#include "math_functions.hpp"
#include "stack.hpp"

#include <sstream>
#include <string>

long long ulanova::postfix(const std::string& expr)
{
  Stack< long long > stack;
  size_t pos = 0;

  while (pos < expr.size())
  {
    while (pos < expr.size() && expr[pos] == ' ')
    {
      ++pos;
    }

    if (pos == expr.size())
    {
      break;
    }

    size_t end = pos;
    while (end < expr.size() && expr[end] != ' ')
    {
      ++end;
    }
    std::string token = expr.substr(pos, end - pos);

    if (token.size() == 1 && is_operator(token[0]))
    {
      long long b = stack.front();
      stack.pop();

      long long a = stack.front();
      stack.pop();

      long long res = apply_op(a, b, token[0]);
    }
    else
    {
      stack.push(std::stoll(token));
    }
    pos = end;
  }
  long long result = stack.front();
  stack.pop();
  return result;
}
