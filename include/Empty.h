
#include <iostream>
#pragma once
#include "../libs/json.hpp"
#include "Number.h"
#include "ObjectInsideCell.h"
#include "OperationsBetweenObj.h"
#include "Text.h"

class EMPTY : public Object {
 public:
  EMPTY() : Object(Type::EMPTY) {};
  ~EMPTY() {};
  EMPTY(const EMPTY& obj) : Object(obj) { this->m_type = obj.m_type; }

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