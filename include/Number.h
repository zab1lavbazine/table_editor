#include <iostream>
#include <string>

#pragma once

#include "../libs/json.hpp"
#include "ObjectInsideCell.h"
#include "OperationsBetweenObj.h"
#include "Text.h"

class Number : public Object {
 public:
  Number();
  Number(const double& number);
  ~Number();

  // get and set number
  double getNumber() const;
  void setNumber(const double& number);

  // print object
  std::ostream& print(std::ostream& os) const override;

  // clone object
  Object* clone() const override;

  // operator overloading +- ---------------------------------
  Number& operator+=(const Number& number);
  Number& operator+(const Number& number);
  // double dispatch for collision
  Object* collide(Object& obj, OPERATIONS Action) override;
  Object* collide(Text& obj, OPERATIONS Action) override;
  Object* collide(Number& obj, OPERATIONS Action) override;
  Object* collide(EMPTY& obj, OPERATIONS Action) override;

  // toString for saving in json
  std::string toString() const override {
    if (this->m_number == (int)this->m_number) {
      return std::to_string((int)this->m_number);
    }
    return std::to_string(this->m_number);
  }

  // parse from json
  nlohmann::json toJSON() const override;

 private:
  double m_number;
};