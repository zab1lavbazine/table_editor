#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#pragma once
#include "../include/Formula.h"
#include "../include/Node.h"
#include "../include/empty.h"
#include "../include/number.h"
#include "../include/object.h"
#include "../include/text.h"
#include "../libs/json.hpp"

class Cell {
 public:
  Cell() : m_object(nullptr) {}
  Cell(const Cell& cell);
  Cell(Object* object) : m_object(object) {}

  // constructor for creating cell from object

  /// @brief constructor for creating cell with object inside
  /// @tparam T
  /// @param object Text, Number or Empty
  template <typename T>
  Cell(const T& object) {
    this->m_object = new T(object);
  }
  // destructor
  ~Cell();

  // manipulations with cell and object
  void setObject(Object* object);
  void changeObject(Object* object);
  Object* getObject() const;
  void setFormula(const std::shared_ptr<Node>& formula) {
    this->m_formula.setFormula(formula);
  }

  // function for printing cell or object or formula
  friend std::ostream& operator<<(std::ostream& os, const Cell& cell);
  std::ostream& print(std::ostream& os) const;
  std::string getCharacteistics() const;
  std::string toString() const;

  // formula functions to string
  std::shared_ptr<Node> getFormula() const { return this->m_formula.get(); }
  std::string toStringFormula() const { return this->m_formula.toString(); }

  // for all manipulations with cell like +, -, *, /, =

  /// @brief all operators for manipulating with cells and objects in them
  /// @param cell
  /// @return Cewll
  Cell operator+(const Cell& cell);
  Cell operator-(const Cell& cell);
  Cell operator*(const Cell& cell);
  Cell operator/(const Cell& cell);
  Cell operator=(const Cell& cell);

 

  Cell clone() const;

  // for saving and loading

  /// @brief load cell from json
  /// @return json file with cell
  nlohmann::json toJSON() const;

 private:
  Object* m_object;
  Formula m_formula;
};
