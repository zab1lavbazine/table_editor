
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#pragma once

#include "Node.h"

class Formula {
 public:
  Formula(std::shared_ptr<Node> formula) : m_formula(formula) {}
  ~Formula() = default;
  Formula() = default;

  // manipulations with formula
  std::shared_ptr<Node> getFormula() const { return this->m_formula; }
  void setFormula(const std::shared_ptr<Node>& formula) {
    this->m_formula = formula;
  }

  // print fucntion for formula
  std::ostream& print(std::ostream& os) const;
  friend std::ostream& operator<<(std::ostream& os, const Formula& formula);
  std::string toString() const { return treeToString(m_formula); }
  std::string treeToString(std::shared_ptr<Node> node) const;

  // clone formula
  Formula clone() const;

  // get formula
  std::shared_ptr<Node> get() const { return this->m_formula; }

 private:
  std::shared_ptr<Node> cloneTree(std::shared_ptr<Node> node) const;

 private:
  std::shared_ptr<Node> m_formula;
};