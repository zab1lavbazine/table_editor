
#include <iostream>
#pragma once
#include "number.h"
#include "object.h"
#include "text.h"

class EMPTY : public Object {
 public:
  EMPTY(){};
  ~EMPTY(){};
  EMPTY(const EMPTY& obj) = default;
  // print object
  virtual std::ostream& print(std::ostream& os) const override {
    return os << " ";
  }
  virtual Object* clone() const override {
    return new EMPTY(*this);
  }  // clone object

  std::string toString() const override { return ""; }

  // double dispatch for collision
  Object* collide(Object& obj, OPERATIONS Action) override;
  Object* collide(class Text& obj, OPERATIONS Action) override;
  Object* collide(class Number& obj, OPERATIONS Action) override;
  Object* collide(class EMPTY& obj, OPERATIONS Action) override;

  nlohmann::json toJSON() const override;
};