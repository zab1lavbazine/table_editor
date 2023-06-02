#include <iostream>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#pragma once
#include "cell.h"
#include "empty.h"
#include "number.h"
#include "object.h"
#include "text.h"

class Graph {
 private:
  std::unordered_map<std::shared_ptr<Cell>, std::vector<std::shared_ptr<Cell>>>
      m_graph_childs;
  std::unordered_map<std::shared_ptr<Cell>, std::vector<std::shared_ptr<Cell>>>
      m_graph_parents;

  bool detectLoop(std::shared_ptr<Cell> currentCell,
                  std::unordered_set<std::shared_ptr<Cell>>& visited,
                  std::unordered_set<std::shared_ptr<Cell>>& memorized);

 public:
  bool addEdge(std::shared_ptr<Cell> parent, std::shared_ptr<Cell> child);
  void removeEdge(std::shared_ptr<Cell> parent, std::shared_ptr<Cell> child);
  void removeFromAll(std::shared_ptr<Cell> cell);
  void removeChildrens(std::shared_ptr<Cell> parent);
  void removeParents(std::shared_ptr<Cell> child);
  void removeChild(std::shared_ptr<Cell> parent, std::shared_ptr<Cell> child);
  void removeParent(std::shared_ptr<Cell> child, std::shared_ptr<Cell> parent);
  void determineRelations();

  std::vector<std::shared_ptr<Cell>> getChildrens(
      std::shared_ptr<Cell> parent) {
    return m_graph_childs[parent];
  }
  std::vector<std::shared_ptr<Cell>> getParents(std::shared_ptr<Cell> child) {
    return m_graph_parents[child];
  }

  void printChildrens(std::shared_ptr<Cell> master) const;
  void printParents(std::shared_ptr<Cell> master) const;
};