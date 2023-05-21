#include <iostream>
#include <string>

#pragma once

class Object {
 public:
  enum class OPERATIONS { SUM, MUL, DIV, SUB };
  virtual ~Object() {}
  Object() = default;

  Object(const Object& obj) = default;

  // ostream operator for printing
  friend std::ostream& operator<<(std::ostream& os, const Object& obj) {
    return obj.print(os);
  }
  // print object
  virtual std::ostream& print(std::ostream& os) const = 0;
  virtual Object* clone() const = 0;  // clone object

  // double dispatch for collision
  virtual Object* collide(Object& obj, OPERATIONS Action) = 0;
  virtual Object* collide(class Text& obj, OPERATIONS Action) = 0;
  virtual Object* collide(class Number& obj, OPERATIONS Action) = 0;
};