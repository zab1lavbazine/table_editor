#include "number.h"

#include <iostream>
#include <string>

Number::Number() {}
Number::Number(const int& number) : m_number(number) {}
Number::~Number() {}

int Number::getNumber() const { return this->m_number; }

void Number::setNumber(const int& number) { this->m_number = number; }

std::ostream& Number::print(std::ostream& os) const {
  os << "Number: " << this->m_number;
  return os;
}

Object* Number::clone() const { return new Number(*this); }
