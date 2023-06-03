
#include <iostream>
#pragma once
#include "../libs/json.hpp"
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

  // clone object
  virtual Object* clone() const override { return new EMPTY(*this); }

  // toString for saving in json
  std::string toString() const override { return ""; }

  // collide for all objects
  Object* collide(Object& obj, OPERATIONS Action) override;
  Object* collide(class Text& obj, OPERATIONS Action) override;
  Object* collide(class Number& obj, OPERATIONS Action) override;
  Object* collide(class EMPTY& obj, OPERATIONS Action) override;

  nlohmann::json toJSON() const override;
};