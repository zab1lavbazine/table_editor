#include <iostream>
#include <memory>
#include <string>
#include <vector>

#pragma once
#include "../include/empty.h"
#include "../include/number.h"
#include "../include/object.h"
#include "../include/text.h"

class Cell {
 public:
  Cell() : m_object(nullptr) {}
  Cell(const Cell& cell);
  Cell(Object* object) : m_object(object) {}

  template <typename T>
  Cell(const T& object) {
    this->m_object = new T(object);
  }
  ~Cell();
  void setObject(Object* object);
  void changeObject(Object* object);
  Object* getObject() const;
  Cell& operator=(const Cell& cell);
  friend std::ostream& operator<<(std::ostream& os, const Cell& cell);
  std::ostream& print(std::ostream& os) const;
  std::string getCharacteistics() const;
  std::string toString() const;
  void setFormula(const std::string& formula);
  std::string getFormula() const;

  int getChildrencount() const { return childs.size(); }
  int getParentCount() const { return m_parent.size(); }

  bool operator==(const Cell& cell) const;

  Cell operator+(const Cell& cell);
  Cell operator-(const Cell& cell);
  Cell operator*(const Cell& cell);
  Cell operator/(const Cell& cell);

  Cell clone() const;

  Cell* getChild(size_t index) const;
  Cell* getLastChild() const { return childs.back().get(); }

  bool checkForRepeatChild(Cell* cell) const;
  bool checkForRepeatParent(Cell* cell) const;

  void addChild(std::shared_ptr<Cell> cell);
  void addParent(std::shared_ptr<Cell> cell);

  void setVectorChilds(std::vector<std::shared_ptr<Cell>> childs) {
    this->childs = childs;
  }

  void setVectorParents(std::vector<std::shared_ptr<Cell>> parents) {
    this->m_parent = parents;
  }

  std::vector<std::shared_ptr<Cell>> getVectorChilds() const {
    return this->childs;
  }

  std::vector<std::shared_ptr<Cell>> getVectorParents() const {
    return this->m_parent;
  }

  void clearLastChild() { childs.pop_back(); }

  void clearChildrens() { childs.clear(); }
  void clearParents() { m_parent.clear(); }

 private:
  Object* m_object;
  std::string formula;
  std::vector<std::shared_ptr<Cell>> childs;
  std::vector<std::shared_ptr<Cell>> m_parent;
};
