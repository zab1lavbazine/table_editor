
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#pragma once
#include <iostream>

#include "Node.h"

class Formula {
 public:
  Formula(std::shared_ptr<Node> formula) : m_formula(formula) {}
  ~Formula() = default;
  Formula() = default;

  std::shared_ptr<Node> getFormula() const { return this->m_formula; }
  void setFormula(const std::shared_ptr<Node>& formula) {
    this->m_formula = formula;
  }

  std::ostream& print(std::ostream& os) const {
    if (m_formula != nullptr) {
      os << m_formula->value;
    }
    return os;
  }

  friend std::ostream& operator<<(std::ostream& os, const Formula& formula) {
    if (formula.get() != nullptr) {
      os << formula.get()->value;
    }
    return os;
  }

  std::shared_ptr<Node> get() const { return this->m_formula; }

  std::string toString() const { return treeToString(m_formula); }

  std::string treeToString(std::shared_ptr<Node> node) const {
    if (!node) {
      return "";
    }

    if (!node->left && !node->right) {
      // Leaf node, return its value
      return node->value;
    }

    std::string leftString = treeToString(node->left);
    std::string rightString = treeToString(node->right);

    std::string result =
        "(" + leftString + " " + node->value + " " + rightString + ")";
    return result;
  }

 private:
  std::shared_ptr<Node> m_formula;
};