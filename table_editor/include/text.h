#include <iostream>
#include <string>

#pragma once

#include "../include/number.h"
#include "../include/object.h"

class Text : public Object {
 public:
  Text();
  Text(const std::string& text);
  ~Text();
  std::string getText() const;
  void setText(const std::string& text);
  std::string get_text() const;
  std::ostream& print(std::ostream& os) const override;
  Object* clone() const override;

  Text& operator+(const Text& text);

  Text& operator+=(const Text& text);

  // double dispatch for collision
  Object* collide(Object& obj, OPERATIONS Action) override;
  Object* collide(Text& obj, OPERATIONS Action) override;
  Object* collide(Number& obj, OPERATIONS Action) override;
  Object* collide(EMPTY& obj, OPERATIONS Action) override;

  std::string toString() const override { return this->m_text; }

  nlohmann::json toJSON() const override;

 private:
  std::string m_text;
};