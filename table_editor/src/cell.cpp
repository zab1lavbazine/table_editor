#include "../include/cell.h"

// copy constructor
Cell::Cell(const Cell& cell) : m_object(cell.m_object->clone()) {
  this->m_formula = cell.m_formula.clone();
}

// destructor
Cell::~Cell() { delete m_object; }

// print cell function
std::ostream& Cell::print(std::ostream& os) const {
  if (m_object != nullptr) {
    m_object->print(os);
  }
  return os;
}

// get cell characteristics
// shows formula and value inside
std::string Cell::getCharacteistics() const {
  std::stringstream ss;
  ss << "Formula: ";
  ss << this->m_formula.toString() << std::endl;
  ss << "value inside: " << *this->getObject();
  return ss.str();
}

// cell into string / used for saving in json
std::string Cell::toString() const {
  std::stringstream ss;
  ss << this->m_object->toString();
  return ss.str();
}

// operator for adding cells
Cell Cell::operator+(const Cell& cell) {
  Cell new_cell;
  new_cell.m_object =
      this->m_object->collide(*cell.m_object, Object::OPERATIONS::SUM);
  return new_cell;
}

// operator for multiplying cells

Cell Cell::operator*(const Cell& cell) {
  Cell new_cell;
  new_cell.m_object =
      this->m_object->collide(*cell.m_object, Object::OPERATIONS::MUL);
  return new_cell;
}

// operator for subtracting cells
Cell Cell::operator-(const Cell& cell) {
  Cell new_cell;
  new_cell.m_object =
      this->m_object->collide(*cell.m_object, Object::OPERATIONS::SUB);
  return new_cell;
}

// operator for dividing cells
Cell Cell::operator/(const Cell& cell) {
  Cell new_cell;
  new_cell.m_object =
      this->m_object->collide(*cell.m_object, Object::OPERATIONS::DIV);
  return new_cell;
}

// operator for friend function
std::ostream& operator<<(std::ostream& os, const Cell& cell) {
  return cell.print(os);
}

// operator for getting cell value
Object* Cell::getObject() const { return m_object; }

// cloning cell
Cell Cell::clone() const {
  Cell new_cell;
  new_cell.m_object = this->m_object->clone();
  return new_cell;
}

// function for setting cell object
void Cell::setObject(Object* object) {
  if (this->m_object != nullptr) delete m_object;
  m_object = object;
  m_formula.setFormula(nullptr);
}

Cell Cell::operator=(const Cell& cell) {
  if (this != &cell) {
    delete m_object;
    m_object = cell.m_object->clone();
    m_formula = cell.m_formula.clone();
  }
  return *this;
}

// function for json parsing
nlohmann::json Cell::toJSON() const {
  return nlohmann::json{{"formula", this->m_formula.toString()}};
}