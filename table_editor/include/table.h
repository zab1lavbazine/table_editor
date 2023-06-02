#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "../include/graph_cell_relations.h"
#include "../include/operand_handler.h"
#include "../libs/json.hpp"
#include "../libs/tabulate.hpp"

struct POS {
  int row;
  int column;
};

class TABLE {
 private:
  std::vector<std::vector<std::shared_ptr<Cell>>> m_table;
  long int m_rows;
  long int m_columns;
  Graph m_graph;
  MessHandler m_handler;

 public:
  TABLE();
  TABLE(const TABLE& table);
  void setSize(const int& rows, const int& columns);
  // void setValue(const std::string& position, const Cell& cell);
  void setValue(const std::string& position, const std::string& formula);
  void setValueFormula(const std::string& position, std::shared_ptr<Cell> cell);
  long int getRows() const;
  long int getColumns() const;
  void ShowCell(const int row, const int column) const;
  void ShowCell(const std::string position) const;
  ~TABLE();
  TABLE& operator=(const TABLE& table);
  friend std::ostream& operator<<(std::ostream& os, const TABLE& table);
  std::ostream& print(std::ostream& os) const;
  std::shared_ptr<Cell> getCell(const std::string position) const;
  Cell evaluate(const std::shared_ptr<Node>& node,
                std::vector<std::shared_ptr<Cell>>& toPut) const;
  void changeValue(const std::string& position, Object* cell);
  void changeValue(const std::string& position, const std::string& formula);

  bool putChild(std::shared_ptr<Cell> new_cell,
                std::vector<std::shared_ptr<Cell>>& toPut);
  void changeChildrens(std::shared_ptr<Cell> new_cell);

  void eraseCell(const std::string& position);
  void eraseCell(const int& row, const int& column);

  void printConnections(std::shared_ptr<Cell> master) const {
    m_graph.printChildrens(master);
    m_graph.printParents(master);
  }

  POS get_position(const std::string& position) const;

  void showFormula(const std::string& position) const;

  std::shared_ptr<Cell> HandleOperands(
      const std::string& expression, std::vector<std::shared_ptr<Cell>>& toPut);

  nlohmann::json toJSON() const;
};