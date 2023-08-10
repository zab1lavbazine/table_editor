#include "../include/number.h"

#include <stdbool.h>

// help functions

//

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

// collide with Empty Object
Object* Number::collide([[maybe_unused]] EMPTY& obj,
                        [[maybe_unused]] OPERATIONS Action) {
  return new Number(this->m_number);
}

// collide with Text Object
Object* Number::collide(Text& obj, OPERATIONS Action) {
  switch (Action) {
    case OPERATIONS::SUM: {
      Object* result = Visitor::addition(*(this), obj, true);
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

    case OPERATIONS::SIN: {
      throw std::invalid_argument("Text cannot be used with sin");
      break;
    }
    case OPERATIONS::COS: {
      throw std::invalid_argument("Text cannot be used with cos");
      break;
    }
  }
  return nullptr;
}

// collide with Number Object
Object* Number::collide(Number& obj, OPERATIONS Action) {
  switch (Action) {
    case OPERATIONS::SUM: {
      Object* result = Visitor::addition(obj, *(this));
      return result;
      break;
    }
    case OPERATIONS::SUB: {
      Object* result = Visitor::subtraction(obj, *(this));
      return result;
      break;
    }
    case OPERATIONS::MUL: {
      Object* result = Visitor::multiplication(obj, *(this));
      return result;
      break;
    }
    case OPERATIONS::DIV: {
      if (this->m_number == 0) {
        throw std::invalid_argument("Division by zero");
      }
      Object* result = Visitor::division(obj, (*this), false);
      return result;
      break;
    }
    case OPERATIONS::SIN: {
      Object* result = Visitor::sinus(*(this));
      return result;
      break;
    }
    case OPERATIONS::COS: {
      Object* result = Visitor::cosinus(*(this));
      return result;
      break;
    }
  }
  return nullptr;
}

// collide with Formula Object
nlohmann::json Number::toJSON() const {
  return nlohmann::json{{"type", "number"}, {"value", this->m_number}};
}
