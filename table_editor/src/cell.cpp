#include "../include/cell.h"

#include <memory>
#include <sstream>
#include <vector>

Cell::Cell(const Cell& cell) : m_object(cell.m_object->clone()) {
  this->formula = cell.formula;
  for (auto& child : cell.childs) {
    this->childs.push_back(child);
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
  for (int i = 0; i < this->getChildrencount(); i++) {
    ss << "Child " << i << ": \n"
       << this->getChild(i)->getCharacteistics() << std::endl;
  }

  ss << "=========parents=========\n";
  for (int i = 0; i < this->getParentCount(); i++) {
    ss << "Parent " << i << ": \n"
       << this->m_parent[i]->getCharacteistics() << std::endl;
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

bool Cell ::operator==(Cell* cell) const {
  return this->m_object == cell->m_object;
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

bool Cell::checkForRepeatChild(Cell* cell) const {
  for (auto& child : childs) {
    if (child.get() == cell) return true;
  }
  return false;
}

void Cell::addChild(std::shared_ptr<Cell> cell) {
  if (this->checkForRepeatChild(cell.get()))
    throw std::invalid_argument("Repeat of the child");
  // make shared

  childs.push_back(cell);
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

Cell* Cell::getChild(size_t index) const {
  if (index >= childs.size() || index < 0) return nullptr;
  if (childs[index] == nullptr) return nullptr;
  return childs[index].get();
}

bool Cell::checkForRepeatParent(Cell* cell) const {
  for (auto& parent : m_parent) {
    if (parent.get() == cell) return true;
  }
  return false;
}

void Cell::addParent(std::shared_ptr<Cell> cell) {
  if (this->checkForRepeatParent(cell.get()))
    throw std::invalid_argument("Repeat of the parent");
  m_parent.push_back(cell);
}
