#include <iostream>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#pragma once

#include "cell.h"

class Graph {
 private:
  std::unordered_map<std::shared_ptr<Cell>, std::vector<std::shared_ptr<Cell>>>
      m_graph;

  bool detectLoop(std::shared_ptr<Cell> currentCell,
                  std::unordered_set<std::shared_ptr<Cell>>& visited,
                  std::unordered_set<std::shared_ptr<Cell>>& memorized);

 public:
  void addEdge(std::shared_ptr<Cell> parent, std::shared_ptr<Cell> child);
  void removeEdge(std::shared_ptr<Cell> parent, std::shared_ptr<Cell> child);

  void determineRelations();
};