#include "../include/number.h"

#include <iostream>
#include <string>

Number::Number() {}
Number::Number(const double& number) : m_number(number) {}
Number::~Number() {}

double Number::getNumber() const { return this->m_number; }

void Number::setNumber(const double& number) { this->m_number = number; }

std::ostream& Number::print(std::ostream& os) const {
  os << this->m_number;
  return os;
}

Object* Number::clone() const { return new Number(*this); }

// operator overloading +- ---------------------------------
Number& Number::operator+(const Number& number) {
  this->m_number += number.m_number;
  return *this;
}

// operator overloading + ---------------------------------
Number& Number::operator+=(const Number& number) {
  this->m_number = number.m_number + this->m_number;
  return *this;
}

// double dispatch for collision
Object* Number::collide(Object& obj, OPERATIONS Action) {
  return obj.collide(*this, Action);
}

Object* Number::collide(Text& obj, OPERATIONS Action) {
  switch (Action) {
    case OPERATIONS::SUM: {
      if (obj.getText().length() == 0 &&
          std::to_string(this->m_number).length() == 0) {
        Object* result = new Text("");
        return result;
      } else if (obj.getText().length() == 0) {
        Object* result = new Text(std::to_string(this->m_number));
        return result;
      } else if (std::to_string(this->m_number).length() == 0) {
        Object* result = new Text(obj.getText());
        return result;
      }
      Object* result = new Text(obj.getText() + std::to_string(this->m_number));
      return result;
      break;
    }
    case OPERATIONS::SUB: {
      throw std::invalid_argument("Text cannot be subtracted");
      break;
    }
    case OPERATIONS::MUL: {
      throw std::invalid_argument("Text cannot be multiplied");
      break;
    }
    case OPERATIONS::DIV: {
      throw std::invalid_argument("Text cannot be divided");
      break;
    }
  }
  return nullptr;
}
Object* Number::collide(Number& obj, OPERATIONS Action) {
  switch (Action) {
    case OPERATIONS::SUM: {
      Object* result = new Number(obj.getNumber() + this->m_number);
      return result;
      break;
    }
    case OPERATIONS::SUB: {
      Object* result = new Number(obj.getNumber() - this->m_number);
      return result;
      break;
    }
    case OPERATIONS::MUL: {
      Object* result = new Number(obj.getNumber() * this->m_number);
      return result;
      break;
    }
    case OPERATIONS::DIV: {
      if (this->m_number == 0) {
        throw std::invalid_argument("Division by zero");
      }
      Object* result = new Number(obj.getNumber() / this->m_number);
      return result;
      break;
    }
  }
  return nullptr;
}
