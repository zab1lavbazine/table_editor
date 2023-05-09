#include "../include/cell.h"

#include <sstream>

#include "../include/number.h"
#include "../include/text.h"

Cell::Cell(const Cell& cell) : m_object(cell.m_object->clone()) {}

Cell::~Cell() { delete m_object; }

Cell& Cell::operator=(const Cell& cell) {
  if (this != &cell) {
    delete m_object;
    m_object = cell.m_object->clone();
  }
  return *this;
}

std::ostream& Cell::print(std::ostream& os) const {
  if (m_object != nullptr) {
    m_object->print(os);
  } else {
    os << "empty";
  }
  return os;
}

std::string Cell::toString() const {
  std::stringstream ss;
  ss << *this->m_object;
  return ss.str();
}

Cell Cell::operator+(const Cell& cell) {
  Cell new_cell;
  new_cell.m_object = this->m_object->collide(*cell.m_object, "SUM");
  return new_cell;
}

Cell Cell::operator*(const Cell& cell) {
  Cell new_cell;
  new_cell.m_object = this->m_object->collide(*cell.m_object, "MUL");
  return new_cell;
}

Cell Cell::operator-(const Cell& cell) {
  Cell new_cell;
  new_cell.m_object = this->m_object->collide(*cell.m_object, "SUB");
  return new_cell;
}

Cell Cell::operator/(const Cell& cell) {
  Cell new_cell;
  new_cell.m_object = this->m_object->collide(*cell.m_object, "DIV");
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