
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

  for (const std::shared_ptr<Cell>& child : m_graph_childs[currentCell]) {
    // if the child is already visited, then there is a loop
    if (visited.count(child) > 0 || detectLoop(child, visited, memorized)) {
      visited.erase(currentCell);
      memorized.insert(child);
      std::cout << "Loop detected" << std::endl;
      return true;
    }
  }
  return false;
}

// add edge to graph with new connection
void Graph::addEdge(std::shared_ptr<Cell> parent, std::shared_ptr<Cell> child) {
  m_graph_childs[parent].push_back(child);
  std::unordered_set<std::shared_ptr<Cell>> visited;    // visited cells
  std::unordered_set<std::shared_ptr<Cell>> memorized;  // memorized cells
  if (detectLoop(child, visited,
                 memorized)) {  // if loop detected delete edge from graph
    m_graph_childs[parent].pop_back();
    m_graph_childs.erase(child);
    throw std::invalid_argument("Loop detected");
  }
  m_graph_parents[child].push_back(parent);
}

// remove edge from graph
void Graph::removeEdge(std::shared_ptr<Cell> parent,
                       std::shared_ptr<Cell> child) {
  m_graph_childs[parent].erase(std::remove(m_graph_childs[parent].begin(),
                                           m_graph_childs[parent].end(), child),
                               m_graph_childs[parent].end());
  m_graph_parents[child].erase(
      std::remove(m_graph_parents[child].begin(), m_graph_parents[child].end(),
                  parent),
      m_graph_parents[child].end());
}

void Graph::determineRelations() {
  std::cout << "Graph: " << std::endl;
  for (const auto& entry : m_graph_childs) {
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

  for (const auto& entry : m_graph_childs) {
    std::shared_ptr<Cell> cell = entry.first;
    if (detectLoop(cell, visited, memorized)) {
      throw std::invalid_argument("Loop detected");
    }
  }
}

void Graph::removeChild(
    std::shared_ptr<Cell> parent,
    std::shared_ptr<Cell> child) {  // remove one specific child
  m_graph_childs[parent].erase(std::remove(m_graph_childs[parent].begin(),
                                           m_graph_childs[parent].end(), child),
                               m_graph_childs[parent].end());
}

void Graph::removeParent(std::shared_ptr<Cell> child,
                         std::shared_ptr<Cell> parent) {  // remove one specific
                                                          // parent
  m_graph_parents[child].erase(
      std::remove(m_graph_parents[child].begin(), m_graph_parents[child].end(),
                  parent),
      m_graph_parents[child].end());
}

void Graph::printChildrens(std::shared_ptr<Cell> master) const {
  std::cout << "========================" << std::endl;
  std::cout << "Graph: " << *master.get() << std::endl;
  if (m_graph_childs.count(master) == 0) {
    std::cout << "No children" << std::endl;
    return;
  }
  std::vector<std::shared_ptr<Cell>> children = m_graph_childs.at(master);
  std::cout << "Children: " << std::endl;
  for (const auto& child : children) {
    std::cout << *child.get() << std::endl;
  }
  std::cout << "========================" << std::endl;
}

void Graph::printParents(std::shared_ptr<Cell> master) const {
  std::cout << "========================" << std::endl;
  std::cout << "Graph: " << *master.get() << std::endl;
  if (m_graph_parents.count(master) == 0) {
    std::cout << "No parents" << std::endl;
    return;
  }
  std::vector<std::shared_ptr<Cell>> parents = m_graph_parents.at(master);
  std::cout << "Parents: " << std::endl;
  for (const auto& parent : parents) {
    std::cout << *parent.get() << std::endl;
  }
  std::cout << "========================" << std::endl;
}

void Graph::removeFromAll(std::shared_ptr<Cell> cell) {
  for (const auto& entry : m_graph_childs) {
    std::shared_ptr<Cell> parent = entry.first;
    removeChild(parent, cell);
  }
  for (const auto& entry : m_graph_parents) {
    std::shared_ptr<Cell> child = entry.first;
    removeParent(child, cell);
  }
}

void Graph::removeChildrens(std::shared_ptr<Cell> parent) {
  for (const auto& child : m_graph_childs[parent]) {
    removeParent(child, parent);
  }
  m_graph_childs.erase(parent);
}

void Graph::removeParents(std::shared_ptr<Cell> child) {
  for (const auto& parent : m_graph_parents[child]) {
    removeChild(parent, child);
  }
  m_graph_parents.erase(child);
}