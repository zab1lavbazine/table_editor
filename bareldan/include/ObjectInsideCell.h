#include <cstring>
#include <iostream>
#include <string>

#pragma once
#include "../libs/json.hpp"

class Object {
 public:
  enum class OPERATIONS { SUM, MUL, DIV, SUB, SIN, COS };
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

  /// @brief Collide function for all objects in cell
  /// @param obj
  /// @param Action
  /// @return Object*
  virtual Object* collide(Object& obj, OPERATIONS Action) = 0;
  virtual Object* collide(class Text& obj, OPERATIONS Action) = 0;
  virtual Object* collide(class Number& obj, OPERATIONS Action) = 0;
  virtual Object* collide(class EMPTY& obj, OPERATIONS Action) = 0;

  virtual nlohmann::json toJSON() const = 0;

  // toString for printing
  virtual std::string toString() const = 0;
};