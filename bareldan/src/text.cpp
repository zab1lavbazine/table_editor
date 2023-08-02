#include "../include/text.h"

Text::Text() {}
Text::Text(const std::string& text) : m_text(text) {}
Text::~Text() {}

std::string Text::getText() const { return this->m_text; }

void Text::setText(const std::string& text) { this->m_text = text; }

Object* Text::clone() const { return new Text(*this); }

std::ostream& Text::print(std::ostream& os) const {
  os << this->m_text;
  return os;
}

std::string Text::get_text() const { return this->m_text; }

// double dispatch for collision
Object* Text::collide(Object& obj, OPERATIONS Action) {
  return obj.collide(*this, Action);
}

Object* Text::collide(Text& obj, OPERATIONS Action) {
  switch (Action) {
    case OPERATIONS::SUM: {
      Object* result = Visitor::addition(obj, *(this));
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
      throw std::invalid_argument("cannot use sin on text");
      break;
    }
    case OPERATIONS::COS: {
      throw std::invalid_argument("cannot use cos on text");
      break;
    }
  }
  return nullptr;
}

Object* Text::collide([[maybe_unused]] EMPTY& obj, OPERATIONS Action) {
  switch (Action) {
    case OPERATIONS::SUM:
    case OPERATIONS::SUB:
    case OPERATIONS::MUL:
    case OPERATIONS::DIV: {
      return new Text(this->m_text);
      break;
    }

    case OPERATIONS::SIN: {
      throw std::invalid_argument("cannot use sin on text");
      break;
    }
    case OPERATIONS::COS: {
      throw std::invalid_argument("cannot use cos on text");
      break;
    }
  }
  return nullptr;
}

Object* Text::collide(Number& obj, OPERATIONS Action) {
  switch (Action) {
    case OPERATIONS::SUM: {
      Object* result = Visitor::addition(obj, (*this), false);
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
      throw std::invalid_argument("cannot use sin on text");
      break;
    }
    case OPERATIONS::COS: {
      throw std::invalid_argument("cannot use cos on text");
      break;
    }
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

nlohmann::json Text::toJSON() const {
  return nlohmann::json{{"type", "text"}, {"value", this->m_text}};
}
