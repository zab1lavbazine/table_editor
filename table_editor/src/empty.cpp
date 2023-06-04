#include "empty.h"

// double  dispatch
Object* EMPTY::collide(Object& obj, OPERATIONS Action) {
  return obj.collide(*this, Action);
}

// collide with Empty Object
Object* EMPTY::collide(EMPTY& obj, OPERATIONS Action) {
  switch (Action) {
    case OPERATIONS::SUM: {
      Object* result = new EMPTY(obj);
      return result;
      break;
    }
    case OPERATIONS::SUB: {
      Object* result = new EMPTY(obj);
      return result;
      break;
    }
    case OPERATIONS::MUL: {
      Object* result = new EMPTY(obj);
      return result;
      break;
    }
    case OPERATIONS::DIV: {
      Object* result = new EMPTY(obj);
      return result;
      break;
    }
  }
  return nullptr;
}

// collide with Number Object
Object* EMPTY::collide(Number& obj, OPERATIONS Action) {
  switch (Action) {
    case OPERATIONS::SUM: {
      Object* result = new Number(obj.getNumber());
      return result;
      break;
    }
    case OPERATIONS::SUB: {
      Object* result = new Number(obj.getNumber());
      return result;
      break;
    }
    case OPERATIONS::MUL: {
      Object* result = new Number(obj.getNumber());
      return result;
      break;
    }
    case OPERATIONS::DIV: {
      Object* result = new Number(obj.getNumber());
      return result;
      break;
    }
  }
  return nullptr;
}

// collide with Text Object
Object* EMPTY::collide(Text& obj, OPERATIONS Action) {
  switch (Action) {
    case OPERATIONS::SUM: {
      Object* result = new Text(obj.getText());
      return result;
      break;
    }
    case OPERATIONS::SUB: {
      Object* result = new Text(obj.getText());
      return result;
      break;
    }
    case OPERATIONS::MUL: {
      Object* result = new Text(obj.getText());
      return result;
      break;
    }
    case OPERATIONS::DIV: {
      Object* result = new Text(obj.getText());
      return result;
      break;
    }
  }
  return nullptr;
}

// parse to JSON
nlohmann::json EMPTY::toJSON() const { return nlohmann::json(); }