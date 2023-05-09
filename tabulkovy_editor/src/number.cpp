#include "../include/number.h"

#include <iostream>
#include <string>

#define SUM "SUM"
#define MUL "MUL"
#define DIV "DIV"
#define SUB "SUB"

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
Object* Number::collide(Object& obj, const std::string Action) {
  return obj.collide(*this, Action);
}
Object* Number::collide(Text& obj, const std::string Action) {
  if (obj.getText() == "empty" && Action == SUM) {
    Object* result = new Text(std::to_string(this->m_number));
    return result;
  } else if (Action == SUM) {
    Object* result =
        new Text(std::to_string(this->m_number) + " " + obj.getText());
    return result;
  } else if (Action == SUB) {
    throw std::invalid_argument("Text cannot be subtracted");
  } else if (Action == MUL) {
    throw std::invalid_argument("Text cannot be multiplied");
  } else if (Action == DIV) {
    throw std::invalid_argument("Text cannot be divided");
  }
  return nullptr;
}
Object* Number::collide(Number& obj, const std::string Action) {
  if (Action == SUM) {
    Object* result = new Number(this->m_number + obj.getNumber());
    return result;
  } else if (Action == SUB) {
    Object* result = new Number(this->m_number - obj.getNumber());
    return result;
  } else if (Action == MUL) {
    Object* result = new Number(this->m_number * obj.getNumber());
    return result;
  } else if (Action == DIV) {
    Object* result = new Number(this->m_number / obj.getNumber());
    return result;
  }
  return nullptr;
}
