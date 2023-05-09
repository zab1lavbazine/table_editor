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
  Object* collide(Object& obj, const std::string Action) override;
  Object* collide(Text& obj, const std::string Action) override;
  Object* collide(Number& obj, const std::string Action) override;

 private:
  std::string m_text;
};