#include "cell.h"

#include "number.h"
#include "text.h"

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
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const Cell& cell) {
  return cell.print(os);
}

Object* Cell::getObject() const { return m_object; }


