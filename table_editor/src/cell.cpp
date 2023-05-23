#include "../include/cell.h"

#include <cstring>
#include <memory>
#include <sstream>
#include <vector>

Cell::Cell(const Cell& cell) : m_object(cell.m_object->clone()) {
  this->formula = cell.formula;
}

Cell::~Cell() {
  delete m_object;
  formula = "";
}

Cell& Cell::operator=(const Cell& cell) {
  if (this != &cell) {
    delete m_object;
    m_object = cell.m_object->clone();
  }
  return *this;
}

void Cell::setFormula(const std::string& formula) { this->formula = formula; }

std::string Cell::getFormula() const { return this->formula; }

std::ostream& Cell::print(std::ostream& os) const {
  if (m_object != nullptr) {
    m_object->print(os);
  }
  return os;
}

std::string Cell::getCharacteistics() const {
  std::stringstream ss;
  ss << "Formula: " << this->getFormula() << std::endl;
  ss << "value inside: " << *this->getObject() << std::endl;
  return ss.str();
}

std::string Cell::toString() const {
  std::stringstream ss;
  ss << *this->m_object;
  return ss.str();
}

Cell Cell::operator+(const Cell& cell) {
  Cell new_cell;
  new_cell.m_object =
      this->m_object->collide(*cell.m_object, Object::OPERATIONS::SUM);
  return new_cell;
}

Cell Cell::operator*(const Cell& cell) {
  Cell new_cell;
  new_cell.m_object =
      this->m_object->collide(*cell.m_object, Object::OPERATIONS::MUL);
  return new_cell;
}

Cell Cell::operator-(const Cell& cell) {
  Cell new_cell;
  new_cell.m_object =
      this->m_object->collide(*cell.m_object, Object::OPERATIONS::SUB);
  return new_cell;
}

Cell Cell::operator/(const Cell& cell) {
  Cell new_cell;
  new_cell.m_object =
      this->m_object->collide(*cell.m_object, Object::OPERATIONS::DIV);
  return new_cell;
}

std::ostream& operator<<(std::ostream& os, const Cell& cell) {
  return cell.print(os);
}

Object* Cell::getObject() const { return m_object; }

Cell Cell::clone() const {
  Cell new_cell;
  new_cell.m_object = this->m_object->clone();
  return new_cell;
}

void Cell::changeObject(Object* newObject) {
  if (this->m_object != nullptr) delete m_object;
  m_object = newObject;
}

void Cell::setObject(Object* object) {
  if (this->m_object != nullptr) delete m_object;
  m_object = object;
  formula = "";
}
