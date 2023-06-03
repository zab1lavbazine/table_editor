#include <iostream>
#include <memory>
#include <stack>
#include <string>

#include "../include/Formula.h"
#include "../include/Node.h"

class MessHandler {
 public:
  // function for parsing formula in tree

  /// @brief function for parsing formula in tree
  /// @param formula
  /// @return std::shared_ptr<Node>
  std::shared_ptr<Node> buildParseTree(const std::string& formula);
  std::shared_ptr<Node> parseExpression(const std::string& formula,
                                        size_t& index, size_t length);
  std::shared_ptr<Node> parseTerm(const std::string& formula, size_t& index,
                                  size_t length);
  std::shared_ptr<Node> parseFactor(const std::string& formula, size_t& index,
                                    size_t length);

  int countFormulas(const std::shared_ptr<Node>& node);

  // print function for tree
  void printParseTree(const std::shared_ptr<Node>& node, int depth = 0) {
    if (node != nullptr) {
      std::cout << getIndentation(depth) << "|_" << node->value << std::endl;
      printParseTree(node->left, depth + 1);
      printParseTree(node->right, depth + 1);
    }
  }

 private:
  bool isOperator(const char& ch);
  std::string getIndentation(int depth);
};