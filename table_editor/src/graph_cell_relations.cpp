
#include "../include/graph_cell_relations.h"

#include <algorithm>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "graph_cell_relations.h"

bool Graph::detectLoop(std::shared_ptr<Cell> currentCell,
                       std::unordered_set<std::shared_ptr<Cell>>& visited,
                       std::unordered_set<std::shared_ptr<Cell>>& memorized) {
  if (memorized.count(currentCell) > 0) {
    std::cout << "Loop detected" << std::endl;
    return true;  // loop detected
  }
  visited.insert(currentCell);

  for (const std::shared_ptr<Cell>& child : m_graph[currentCell]) {
    // if the child is already visited, then there is a loop
    if (visited.count(child) > 0 || detectLoop(child, visited, memorized)) {
      visited.erase(currentCell);
      memorized.insert(child);
      return true;
    }
  }
  return false;
}

// add edge to graph
void Graph::addEdge(std::shared_ptr<Cell> parent, std::shared_ptr<Cell> child) {
  m_graph[parent].push_back(child);
  std::unordered_set<std::shared_ptr<Cell>> visited;
  std::unordered_set<std::shared_ptr<Cell>> memorized;
  if (detectLoop(child, visited, memorized)) {
    m_graph[parent].pop_back();
    m_graph.erase(child);
    throw std::invalid_argument("Loop detected");
  }
}

// remove edge from graph
void Graph::removeEdge(std::shared_ptr<Cell> parent,
                       std::shared_ptr<Cell> child) {
  auto& children = m_graph[parent];
  children.erase(std::remove_if(children.begin(), children.end(),
                                [&child](const std::shared_ptr<Cell>& c) {
                                  return c.get() == child.get();
                                }),
                 children.end());
}

void Graph::determineRelations() {
  std::cout << "Graph: " << std::endl;
  for (const auto& entry : m_graph) {
    std::shared_ptr<Cell> parent = entry.first;
    const std::vector<std::shared_ptr<Cell>>& children = entry.second;

    std::cout << "Parent: " << parent->toString() << std::endl;
    std::cout << "Children: " << std::endl;
    for (const auto& child : children) {
      std::cout << child->toString() << std::endl;
    }
  }

  std::unordered_set<std::shared_ptr<Cell>> visited;
  std::unordered_set<std::shared_ptr<Cell>> memorized;

  for (const auto& entry : m_graph) {
    std::shared_ptr<Cell> cell = entry.first;
    if (detectLoop(cell, visited, memorized)) {
      throw std::invalid_argument("Loop detected");
    }
  }
}
