#include "infix.hpp"
#include "math_functions.hpp"
#include "stack.hpp"

#include <sstream>
#include <string>

std::string ulanova::infix_to_postfix(const std::string& expr)
{
  Stack<char> ops;
  Queue<std::string> output;

  std::stringstream s(expr);
  std::string token;

  while (s >> token)
  {
  if (!is_operator(token[0]) && token != "(" && token != ")")
  {
      output.push(token);
  }
  else if (token == "(")
  {
      ops.push('(');
  }
  else if (token == ")")
  {
      while (!ops.empty() && ops.front() != '(')
      {
      output.push(std::string(1, ops.front()));
      ops.pop();
      }
      ops.pop();
  }
  else
  {
      char op = token[0];
      while (!ops.empty() && priority(ops.front()) >= priority(op))
      {
      output.push(std::string(1, ops.front()));
      ops.pop();
      }
      ops.push(op);
  }
  }
  while (!ops.empty())
  {
  output.push(std::string(1, ops.front()));
  ops.pop();
  }
  std::string result;
  while (!output.empty())
  {
  result += output.front() + " ";
  output.pop();
  }
  return result;
}
