#include "../include/cell.h"

#include <cstring>
#include <memory>
#include <sstream>
#include <vector>

Cell::Cell(const Cell& cell) : m_object(cell.m_object->clone()) {
  this->m_formula = cell.m_formula;
}

Cell::~Cell() { delete m_object; }

std::ostream& Cell::print(std::ostream& os) const {
  if (m_object != nullptr) {
    m_object->print(os);
  }
  return os;
}

std::string Cell::getCharacteistics() const {
  std::stringstream ss;
  ss << "Formula: ";
  ss << this->m_formula.toString() << std::endl;
  ss << "value inside: " << *this->getObject();
  return ss.str();
}

std::string Cell::toString() const {
  if (this->m_object == nullptr) return std::string("empty");
  std::stringstream ss;
  ss << this->m_object->toString();
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
  m_formula.setFormula(nullptr);
}

Cell Cell::operator=(const Cell& cell) {
  if (this != &cell) {
    delete m_object;
    m_object = cell.m_object->clone();
    m_formula = cell.m_formula;
  }
  return *this;
}