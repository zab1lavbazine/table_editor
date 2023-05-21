#include <iostream>
#include <string>

#pragma once

#include "../include/object.h"
#include "../include/text.h"

class Number : public Object {
 public:
  Number();
  Number(const double& number);
  ~Number();
  double getNumber() const;
  void setNumber(const double& number);
  std::ostream& print(std::ostream& os) const override;
  Object* clone() const override;

  Number& operator+=(const Number& number);
  Number& operator+(const Number& number);
  // double dispatch for collision
  Object* collide(Object& obj, OPERATIONS Action) override;
  Object* collide(Text& obj, OPERATIONS Action) override;
  Object* collide(Number& obj, OPERATIONS Action) override;

 private:
  double m_number;
};