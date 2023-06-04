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
      if (this->m_text.length() == 0 && obj.m_text.length() == 0) {
        Object* result = new Text("");
        return result;
      } else if (this->m_text.length() == 0) {
        Object* result = new Text(obj.m_text);
        return result;
      } else if (obj.m_text.length() == 0) {
        Object* result = new Text(this->m_text);
        return result;
      }
      Object* result = new Text(obj.m_text + this->m_text);
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

Object* Text::collide([[maybe_unused]] EMPTY& obj, OPERATIONS Action) {
  switch (Action) {
    case OPERATIONS::SUM: {
      Object* result = new Text(this->m_text);
      return result;
      break;
    }
    case OPERATIONS::SUB: {
      Object* result = new Text(this->m_text);
      return result;
      break;
    }
    case OPERATIONS::MUL: {
      Object* result = new Text(this->m_text);
      return result;
      break;
    }
    case OPERATIONS::DIV: {
      Object* result = new Text(this->m_text);
      return result;
      break;
    }
  }
  return nullptr;
}

Object* Text::collide(Number& obj, OPERATIONS Action) {
  switch (Action) {
    case OPERATIONS::SUM: {
      if (this->m_text.length() == 0 &&
          std::to_string(obj.getNumber()).length() == 0) {
        Object* result = new Text("");
        return result;
      } else if (this->m_text.length() == 0) {
        if (obj.getNumber() == int(obj.getNumber())) {
          Object* result = new Text(std::to_string(int(obj.getNumber())));
          return result;
        } else {
          if (std::to_string(obj.getNumber()).length() == 0) {
            Object* result = new Text("");
            return result;
          }
          Object* result = new Text(std::to_string(obj.getNumber()));
          return result;
        }
      } else if (std::to_string(obj.getNumber()).length() == 0) {
        Object* result = new Text(this->m_text);
        return result;
      }

      if (obj.getNumber() == int(obj.getNumber())) {
        Object* result =
            new Text(std::to_string(int(obj.getNumber())) + this->m_text);
        return result;
      } else {
        Object* result =
            new Text(std::to_string(obj.getNumber()) + this->m_text);
        return result;
      }
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
