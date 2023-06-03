#include "Formula.h"

#include <../include/Formula.h>

// print function for formula
std::ostream& Formula::print(std::ostream& os) const {
  if (m_formula != nullptr) {
    os << m_formula->value;
  }
  return os;
}

// operator for output
std::ostream& operator<<(std::ostream& os, const Formula& formula) {
  formula.print(os);
  return os;
}

// clone formula
Formula Formula::clone() const {
  std::shared_ptr<Node> new_formula = cloneTree(m_formula);
  return Formula(new_formula);
}

// get formula from tree
std::string Formula::treeToString(std::shared_ptr<Node> node) const {
  if (!node) {
    return "";
  }

  if (!node->left && !node->right) {
    // Leaf node, return its value
    return node->value;
  }

  // if sin or cos
  if (node->value == "sin" || node->value == "cos") {
    std::string leftString = treeToString(node->left);
    std::string result = node->value + leftString;
    return result;
  }

  std::string leftString = treeToString(node->left);
  std::string rightString = treeToString(node->right);

  std::string result =
      "(" + leftString + " " + node->value + " " + rightString + ")";
  return result;
}

// clone all formula tree
std::shared_ptr<Node> Formula::cloneTree(std::shared_ptr<Node> node) const {
  if (!node) {
    return nullptr;
  }

  std::shared_ptr<Node> newNode = std::make_shared<Node>(node->value);
  newNode->left = cloneTree(node->left);
  newNode->right = cloneTree(node->right);

  return newNode;
}