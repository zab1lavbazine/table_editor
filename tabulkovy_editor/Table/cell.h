#include <iostream>
#include <string>

#pragma once
#include "number.h"
#include "text.h"

class Cell {
 public:
  Cell() : m_object(nullptr) {}
  Cell(const Cell& cell);

  template <typename T>
  Cell(const T& object) {
    this->m_object = new T(object);
  }
  ~Cell();
  template <typename T>
  void setObject(const T& object) {
    delete this->m_object;
    this->m_object = new T(object);
  }
  Object* getObject() const;
  Cell& operator=(const Cell& cell);
  friend std::ostream& operator<<(std::ostream& os, const Cell& cell);
  std::ostream& print(std::ostream& os) const;

 private:
  Object* m_object;
};
