#include <iostream>
#include <string>

#pragma once

#include "object.h"
#include "text.h"

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
  Object* collide(Object& obj, const std::string Action) override;
  Object* collide(Text& obj, const std::string Action) override;
  Object* collide(Number& obj, const std::string Action) override;

 private:
  double m_number;
};