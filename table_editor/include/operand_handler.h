#include <stack>
#include <string>

class MessHandler {
  static int getPrecedence(char op);

 public:
  static std::string infixToPostfix(const std::string& infix);
};