#include "postfix.hpp"
#include "math_functions.hpp"
#include "stack.hpp"

#include <sstream>
#include <string>

long long ulanova::postfix(const std::string& expr)
{
  Stack< long long > stack;
  std::stringstream s(expr);
  std::string token;

  while (s >> token)
  {
    if (token.size() == 1 && is_operator(token[0]))
    {
      long long b = stack.front();
      stack.pop();

      long long a = stack.front();
      stack.pop();

      long long res = apply_op(a, b, token[0]);
      stack.push(res);
    }
    else
    {
      long long value = std::stoll(token);
      stack.push(value);
    }
  }

  long long result = stack.front();
  stack.pop();
  return result;
}