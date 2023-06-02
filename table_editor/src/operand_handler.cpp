#include "operand_handler.h"

#include <cctype>
#include <iostream>
#include <memory>

std::string removeSpaces(const std::string& formula) {
  std::string result;
  bool check = 1;
  for (char ch : formula) {
    if (ch == '"') {
      check = !check;
    }
    if (!std::isspace(ch) || check == 0) {
      result += ch;
    }
  }
  return result;
}

int MessHandler::countFormulas(const std::shared_ptr<Node>& node) {
  if (node == nullptr) {
    return 0;
  }

  int count = 0;
  if (isOperator(node->value[0])) {
    count += countFormulas(node->left);
    count += countFormulas(node->right);
  } else {
    count++;
  }

  return count;
}

bool MessHandler::isOperator(const char& ch) {
  return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

std::string MessHandler::getIndentation(int depth) {
  std::string indentation;
  for (int i = 0; i < depth; ++i) {
    indentation += "  ";
  }
  return indentation;
}

std::shared_ptr<Node> MessHandler::buildParseTree(
    const std::string& new_formula) {
  std::string formula = removeSpaces(new_formula);

  size_t length = formula.length();
  size_t index = 0;

  std::shared_ptr<Node> root = parseExpression(formula, index, length);
  return root;
}

std::shared_ptr<Node> MessHandler::parseExpression(const std::string& formula,
                                                   size_t& index,
                                                   size_t length) {
  std::shared_ptr<Node> left = parseTerm(formula, index, length);

  while (index < length && (formula[index] == '+' || formula[index] == '-')) {
    char op = formula[index];
    ++index;
    std::shared_ptr<Node> right = parseTerm(formula, index, length);

    std::shared_ptr<Node> newNode = std::make_shared<Node>(std::string(1, op));
    newNode->left = left;
    newNode->right = right;
    left = newNode;
  }

  return left;
}

std::shared_ptr<Node> MessHandler::parseTerm(const std::string& formula,
                                             size_t& index, size_t length) {
  std::shared_ptr<Node> left = parseFactor(formula, index, length);

  while (index < length && (formula[index] == '*' || formula[index] == '/')) {
    char op = formula[index];
    ++index;
    std::shared_ptr<Node> right = parseFactor(formula, index, length);

    std::shared_ptr<Node> newNode = std::make_shared<Node>(std::string(1, op));
    newNode->left = left;
    newNode->right = right;
    left = newNode;
  }

  return left;
}

std::shared_ptr<Node> MessHandler::parseFactor(const std::string& formula,
                                               size_t& index, size_t length) {
  std::shared_ptr<Node> node = nullptr;

  if (index < length) {
    char ch = formula[index];

    if (std::isalpha(ch)) {
      // Parsing a cell or a string or sin or cos

      size_t startIndex = index;
      if (ch == 's' || ch == 'c') {  // checking for sin or cos
        ++index;
        while (index < length && std::isalpha(formula[index])) {
          ++index;
        }
      } else {
        while (index < length && std::isalnum(formula[index])) {
          ++index;
        }
      }

      std::string token = formula.substr(startIndex, index - startIndex);

      if (token == "sin") {                             // sin
        if (index < length && formula[index] == '(') {  // check for (
          ++index;
          std::shared_ptr<Node> expression =
              parseExpression(formula, index, length);
          if (index < length && formula[index] == ')') {
            ++index;
            node = std::make_shared<Node>("sin");
            node->left = expression;
          } else {
            throw std::invalid_argument("Unbalanced parentheses! ) after sin");
          }
        } else {
          throw std::invalid_argument("Expected '(' after sin!");
        }
      } else if (token == "cos") {                      // cos
        if (index < length && formula[index] == '(') {  // check for
          ++index;
          std::shared_ptr<Node> expression =
              parseExpression(formula, index, length);
          if (index < length && formula[index] == ')') {
            ++index;
            node = std::make_shared<Node>("cos");
            node->left = expression;
          } else {
            std::cerr << "Error: Unbalanced parentheses!" << std::endl;
          }
        } else {
          std::cerr << "Error: Expected '(' after cos!" << std::endl;
        }
      } else  // Cell token or string
        node = std::make_shared<Node>(token);

    } else if (ch == '"') {
      // Parsing a string enclosed in double quotes
      size_t startIndex = index;
      ++index;
      while (index < length && formula[index] != '"') {
        ++index;
      }
      std::string token = formula.substr(startIndex, index - startIndex + 1);
      node = std::make_shared<Node>(token);
      ++index;
    } else if (std::isdigit(ch) || ch == '.') {
      // Parsing a number or number with a negative sign

      size_t startIndex = index;
      // if (ch == '-') ++index;
      while (index < length &&
             (std::isdigit(formula[index]) || formula[index] == '.')) {
        ++index;
      }
      std::string token = formula.substr(startIndex, index - startIndex);
      node = std::make_shared<Node>(token);
    } else if (ch == '(') {
      // Parsing a subexpression enclosed in parentheses
      ++index;
      node = parseExpression(formula, index, length);
      if (index < length && formula[index] == ')') {
        ++index;
      } else {
        std::cerr << "Error: Unbalanced parentheses!" << std::endl;
      }
    }
  }

  return node;
}