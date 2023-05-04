#include <iostream>
#include <string>

Cell::Cell() {}
Cell::Cell(const Cell& cell) : m_object(cell.m_object) {}

template <typename T>
Cell::Cell(const T& object) : m_object(new T(object)) {}
Cell& Cell::operator=(const Cell& cell) {
  if (this != &cell) {
    this->m_object = cell.m_object;
  }
  return *this;
}

Cell::~Cell() { delete this->m_object; }

Cell::Cell(Object* object) : m_object(object) {}

Object* Cell::getObject() const { return this->m_object; }

void Cell::setObject(Object* object) {
  delete this->m_object;
  this->m_object = object;
}

std::ostream& Cell::print(std::ostream& os) const {
  os << this->m_object;
  return os;
}
