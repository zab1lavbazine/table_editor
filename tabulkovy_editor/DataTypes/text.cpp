#include "text.h"

#include <iostream>
#include <string>

#define SUM "SUM"
#define SUB "SUB"
#define MUL "MUL"
#define DIV "DIV"

Text::Text() {}
Text::Text(const std::string& text) : m_text(text) {}
Text::~Text() {}

std::string Text::getText() const { return this->m_text; }

void Text::setText(const std::string& text) { this->m_text = text; }

Object* Text::clone() const { return new Text(*this); }

std::ostream& Text::print(std::ostream& os) const {
  os << "T:" << this->m_text;
  return os;
}

std::string Text::get_text() const { return this->m_text; }

// double dispatch for collision
Object* Text::collide(Object& obj, const std::string Action) {
  return obj.collide(*this, Action);
}

Object* Text::collide(Text& obj, const std::string Action) {
  if (Action == SUM) {
    Object* result = new Text(this->m_text + " " + obj.m_text);
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

Object* Text::collide(Number& obj, const std::string Action) {
  if (Action == SUM) {
    Object* result =
        new Text(std::to_string(obj.getNumber()) + " " + this->m_text);
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

// operator overloading +- ---------------------------------
Text& Text::operator+=(const Text& text) {
  this->m_text = text.m_text + this->m_text;
  return *this;
}

// opertator overloading + ---------------------------------
Text& Text::operator+(const Text& text) {
  this->m_text += text.m_text;
  return *this;
}