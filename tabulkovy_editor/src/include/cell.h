#include <iostream>
#include <string>

#pragma once
#include "../include/number.h"
#include "../include/text.h"

class Cell {
 public:
  Cell() : m_object(nullptr) {}
  Cell(const Cell& cell);

  template <typename T>
  Cell(const T& object) {
    this->m_object = new T(object);
  }
  ~Cell();
  void setObject(Object* object) {
    delete m_object;
    m_object = object;
  }
  Object* getObject() const;
  Cell& operator=(const Cell& cell);
  friend std::ostream& operator<<(std::ostream& os, const Cell& cell);
  std::ostream& print(std::ostream& os) const;

  Cell operator+(const Cell& cell);
  Cell operator-(const Cell& cell);
  Cell operator*(const Cell& cell);
  Cell operator/(const Cell& cell);

 private:
  Object* m_object;
};
