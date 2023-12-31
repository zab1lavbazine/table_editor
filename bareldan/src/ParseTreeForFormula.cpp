#include "ParseTreeForFormula.h"

// helper function for removing spaces from formula
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

// helper function for counting formulas in formula
int ParseTreeForFormula::countFormulas(const std::shared_ptr<Node>& node) {
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

// helper function for checking if operator is valid
bool ParseTreeForFormula::isOperator(const char& ch) {
  return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

std::string ParseTreeForFormula::getIndentation(int depth) {
  std::string indentation;
  for (int i = 0; i < depth; ++i) {
    indentation += "  ";
  }
  return indentation;
}

// main function for parsing formula to tree
std::shared_ptr<Node> ParseTreeForFormula::buildParseTree() {
  formula = removeSpaces(formula);

  size_t length = formula.length();
  size_t index = 0;
  std::shared_ptr<Node> root = parseExpression(index, length);
  // print formula
  // printParseTree(root);
  return root;
}

// helper function for parsing formula to tree with recursion +/-
std::shared_ptr<Node> ParseTreeForFormula::parseExpression(size_t& index,
                                                           size_t length) {
  std::shared_ptr<Node> left = parseTerm(index, length);

  while (index < length && (formula[index] == '+' || formula[index] == '-')) {
    char op = formula[index];
    ++index;
    std::shared_ptr<Node> right = parseTerm(index, length);

    std::shared_ptr<Node> newNode = std::make_shared<Node>(std::string(1, op));
    newNode->left = left;
    newNode->right = right;
    left = newNode;
  }

  return left;
}

// helper function for parsing formula to tree with recursion */ /
std::shared_ptr<Node> ParseTreeForFormula::parseTerm(size_t& index,
                                                     size_t length) {
  std::shared_ptr<Node> left = parseFactor(index, length);

  while (index < length && (formula[index] == '*' || formula[index] == '/')) {
    char op = formula[index];
    ++index;
    std::shared_ptr<Node> right = parseFactor(index, length);

    std::shared_ptr<Node> newNode = std::make_shared<Node>(std::string(1, op));
    newNode->left = left;
    newNode->right = right;
    left = newNode;
  }

  return left;
}

std::shared_ptr<Node> ParseTreeForFormula::parseAlphaToken(size_t& index,
                                                           size_t length) {
  size_t StartIndex = index;
  // char ch = formula[index];

  while (index < length && std::isalnum(formula[index])) {
    ++index;
  }

  std::string token = formula.substr(StartIndex, index - StartIndex);

  if (token == "sin" || token == "cos") {
    return parseFunction(token, index, length);
  } else {
    return std::make_shared<Node>(token);
  }
}

std::shared_ptr<Node> ParseTreeForFormula::parseFunction(
    const std::string& token, size_t& index, size_t length) {
  if (index < length && formula[index] == '(') {
    ++index;
    std::shared_ptr<Node> expression = parseExpression(index, length);
    if (index < length && formula[index] == ')') {
      ++index;
      std::shared_ptr<Node> node = std::make_shared<Node>(token);
      node->left = expression;
      return node;
    } else {
      throw std::invalid_argument("Unbalanced parentheses! ) after sin");
    }
  } else {
    throw std::invalid_argument("Expected '(' after sin!");
  }
}

std::shared_ptr<Node> ParseTreeForFormula::parseStringToken(size_t& index,
                                                            size_t length) {
  size_t StartIndex = index;
  index++;
  // std::cout << "formula index : " << formula[index] << std::endl;
  while (index < length && formula[index] != '"') {
    ++index;
  }
  std::string token = formula.substr(StartIndex, index - StartIndex + 1);
  ++index;
  return std::make_shared<Node>(token);
}

std::shared_ptr<Node> ParseTreeForFormula::parseNumberToken(size_t& index,
                                                            size_t length) {
  size_t startIndex = index;

  while (index < length &&
         (std::isdigit(formula[index]) || formula[index] == '.')) {
    ++index;
  }

  std::string token = formula.substr(startIndex, index - startIndex);
  return std::make_shared<Node>(token);
}

std::shared_ptr<Node> ParseTreeForFormula::parseSubexpression(size_t& index,
                                                              size_t length) {
  ++index;
  std::shared_ptr<Node> expression = parseExpression(index, length);

  if (index < length && formula[index] == ')') {
    ++index;
  } else {
    std::cerr << "Error: Unbalanced parentheses!" << std::endl;
  }

  return expression;
}



std::shared_ptr<Node> ParseTreeForFormula::parseFactor(size_t& index,
                                                       size_t length) {
  std::shared_ptr<Node> node = nullptr;

  if (index < length) {
    char ch = formula[index];

    if (std::isalpha(ch)) {
      node = parseAlphaToken(index, length);
    } else if (ch == '"') {
      node = parseStringToken(index, length);
    } else if (std::isdigit(ch) || ch == '.') {
      node = parseNumberToken(index, length);
    } else if (ch == '(') {
      node = parseSubexpression(index, length);
    }
  }
  return node;
}