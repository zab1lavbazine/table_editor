#include "Empty.h"

// double  dispatch
Object* EMPTY::collide(Object& obj, OPERATIONS Action) {
  return obj.collide(*this, Action);
}

// collide with Empty Object
Object* EMPTY::collide([[maybe_unused]] EMPTY& obj,
                       [[maybe_unused]] OPERATIONS Action) {
  return new EMPTY();
}

// collide with Number Object
Object* EMPTY::collide(Number& obj, OPERATIONS Action) {
  switch (Action) {
    case OPERATIONS::SUM:
    case OPERATIONS::SUB:
    case OPERATIONS::MUL:
    case OPERATIONS::DIV: {
      Object* result = new Number(obj.getNumber());
      return result;
      break;
    }
    case OPERATIONS::SIN: {
      Object* result = new Number(std::sin(obj.getNumber()));
      return result;
      break;
    }
    case OPERATIONS::COS: {
      Object* result = new Number(std::cos(obj.getNumber()));
      return result;
      break;
    }
  }
  return nullptr;
}

// collide with Text Object
Object* EMPTY::collide(Text& obj, OPERATIONS Action) {
  switch (Action) {
    case OPERATIONS::SUM:
    case OPERATIONS::SUB:
    case OPERATIONS::MUL:
    case OPERATIONS::DIV: {
      Object* result = new Text(obj.getText());
      return result;
      break;
    }

    case OPERATIONS::SIN: {
      throw std::invalid_argument("cannot use sin on text");
    }
    case OPERATIONS::COS: {
      throw std::invalid_argument("cannot use cos on text");
    }
  }
  return nullptr;
}

// parse to JSON
nlohmann::json EMPTY::toJSON() const { return nlohmann::json(); }