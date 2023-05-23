#include "../include/cell.h"

#include <cstring>
#include <memory>
#include <sstream>
#include <vector>

Cell::Cell(const Cell& cell) : m_object(cell.m_object->clone()) {
  this->formula = cell.formula;
  for (auto& child : cell.childs) {
    this->childs.insert(child);
  }
}

Cell::~Cell() {
  delete m_object;
  // clear vector
  childs.clear();
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
  ss << "=====================\n";
  ss << "Formula: " << this->getFormula() << std::endl;
  ss << "Childs: " << this->getChildrencount() << std::endl;
  ss << "value inside: " << *this->getObject() << std::endl;
  ss << "=========childrens=========\n";
  for (auto& i : this->childs) {
    ss << "Child: \n" << i->getCharacteistics() << std::endl;
  }

  ss << "=========parents=========\n";
  for (auto& i : this->m_parent) {
    ss << "Parent: \n" << i->getCharacteistics() << std::endl;
  }
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
  // delete old object
  // set new object
  if (this->m_object != nullptr) delete m_object;
  m_object = newObject;
}

void Cell::setObject(Object* object) {
  if (this->m_object != nullptr) delete m_object;
  m_object = object;
  // set formula to empty
  formula = "";
}

void Cell::removeChild(std::shared_ptr<Cell> cell) {
  for (auto it = childs.begin(); it != childs.end(); ++it) {
    if ((*it).get() == cell.get()) {
      childs.erase(it);
      break;
    }
  }
}

void Cell::removeParent(std::shared_ptr<Cell> cell) {
  for (auto it = m_parent.begin(); it != m_parent.end(); ++it) {
    if ((*it).get() == cell.get()) {
      m_parent.erase(it);
      break;
    }
  }
}

void Cell::addChild(std::shared_ptr<Cell> cell) { childs.insert(cell); }

void Cell::addParent(std::shared_ptr<Cell> cell) { m_parent.insert(cell); }