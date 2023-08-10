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
  /// @brief graph for storing relations between cells
  std::unordered_map<std::shared_ptr<Cell>, std::vector<std::shared_ptr<Cell>>>
      m_graph_childs;

  /// @brief  graph for storing relations between cells
  std::unordered_map<std::shared_ptr<Cell>, std::vector<std::shared_ptr<Cell>>>
      m_graph_parents;

  /// @brief function for detecting loop in graph
  bool detectLoop(std::shared_ptr<Cell> currentCell,
                  std::unordered_set<std::shared_ptr<Cell>>& visited,
                  std::unordered_set<std::shared_ptr<Cell>>& memorized);

 public:
  /// @brief all functions for manipulating with graph
  /// @param parent shared_ptr<Cell>
  /// @param child shared_ptr<Cell>
  bool addEdge(std::shared_ptr<Cell> parent, std::shared_ptr<Cell> child);
  void removeEdge(std::shared_ptr<Cell> parent, std::shared_ptr<Cell> child);
  void removeFromAll(std::shared_ptr<Cell> cell);
  void removeChildrensFromParent(std::shared_ptr<Cell> parent);
  void removeParentsFromChildren(std::shared_ptr<Cell> child);
  void removeChild(std::shared_ptr<Cell> parent, std::shared_ptr<Cell> child);
  void removeParent(std::shared_ptr<Cell> child, std::shared_ptr<Cell> parent);
  void determineRelations();

  // get functions from graph
  std::vector<std::shared_ptr<Cell>> getChildrens(
      std::shared_ptr<Cell> parent) {
    return m_graph_childs[parent];
  }
  std::vector<std::shared_ptr<Cell>> getParents(std::shared_ptr<Cell> child) {
    return m_graph_parents[child];
  }

  // print functions
  void printChildrens(std::shared_ptr<Cell> master) const;
  void printParents(std::shared_ptr<Cell> master) const;
};