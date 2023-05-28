#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

#pragma once
#include "../include/Formula.h"
#include "../include/Node.h"
#include "../include/empty.h"
#include "../include/number.h"
#include "../include/object.h"
#include "../include/text.h"

class Cell {
 public:
  Cell() : m_object(nullptr) {}
  Cell(const Cell& cell);
  Cell(Object* object) : m_object(object) {}

  template <typename T>
  Cell(const T& object) {
    this->m_object = new T(object);
  }
  ~Cell();

  void setObject(Object* object);

  void changeObject(Object* object);
  Object* getObject() const;
  Cell& operator=(const Cell& cell);
  friend std::ostream& operator<<(std::ostream& os, const Cell& cell);
  std::ostream& print(std::ostream& os) const;
  std::string getCharacteistics() const;
  std::string toString() const;
  void setFormula(const std::shared_ptr<Node>& formula) {
    this->m_formula.setFormula(formula);
  }
  std::shared_ptr<Node> getFormula() const { return this->m_formula.get(); }
  std::string toStringFormula() const { return this->m_formula.toString(); }

  Cell operator+(const Cell& cell);
  Cell operator-(const Cell& cell);
  Cell operator*(const Cell& cell);
  Cell operator/(const Cell& cell);

  Cell clone() const;

 private:
  Object* m_object;
  Formula m_formula;
};
