#include <iostream>
#include <memory>
#include <stack>
#include <string>

#pragma once

#include "Node.h"
#include "cell.h"

class ParseTreeForFormula {
 public:
  // function for parsing formula in tree

  ParseTreeForFormula(const std::string& formula) : formula(formula) {}

  /// @brief function for parsing formula in tree
  /// @param formula
  /// @return std::shared_ptr<Node>
  std::shared_ptr<Node> buildParseTree();
  std::shared_ptr<Node> parseExpression(size_t& index, size_t length);
  std::shared_ptr<Node> parseTerm(size_t& index, size_t length);
  std::shared_ptr<Node> parseFactor(size_t& index, size_t length);

  std::shared_ptr<Node> parseAlphaToken(size_t& index, size_t length);
  std::shared_ptr<Node> parseFunction(const std::string& token, size_t& index,
                                      size_t length);
  std::shared_ptr<Node> parseStringToken(size_t& index, size_t length);
  std::shared_ptr<Node> parseNumberToken(size_t& index, size_t length);

  std::shared_ptr<Node> parseSubexpression(size_t& index, size_t length);

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

  std::string formula;
  std::shared_ptr<Node> root;
};