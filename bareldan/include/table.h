#include <iostream>
#include <memory>
#include <string>
#include <vector>

#pragma once
#include "../include/ParseTreeForFormula.h"
#include "../include/graph_cell_relations.h"
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

 public:
  TABLE();
  ~TABLE();

  // set methods for table
  void setSize(const int& rows, const int& columns);
  void setValue(const std::string& position, const std::string& formula);

  // get method position of cell
  long int getRows() const;
  long int getColumns() const;
  POS get_position(const std::string& position) const;

  // show methods for cell from table
  void ShowCell(const int row, const int column) const;
  void ShowCell(const std::string position) const;

  TABLE& operator=(const TABLE& table);

  // print table
  friend std::ostream& operator<<(std::ostream& os, const TABLE& table);
  std::ostream& print(std::ostream& os) const;

  // get cell from table for operations with them
  std::shared_ptr<Cell> getCell(const std::string position) const;

  // evaluate cell with formula

  /// @brief function for processing formula and evaluating it
  /// @param expression
  /// @param toPut
  /// @return std::shared_ptr<Cell> to new cell with value
  std::shared_ptr<Cell> HandleOperands(
      const std::string& expression, std::vector<std::shared_ptr<Cell>>& toPut);
  Cell evaluate(const std::shared_ptr<Node>& node,
                std::vector<std::shared_ptr<Cell>>& toPut) const;

  Cell evaluateLeafNode(const std::string& token,
                        std::vector<std::shared_ptr<Cell>>& toPut) const;

  Cell evaluateOperation(const std::string& op, Cell& left, Cell& right) const;

  Cell evaluateFunction(const std::string& functionName) const;

  Cell evaluateNegativeNumber(const std::string& token,
                              std::vector<std::shared_ptr<Cell>>& toPut) const;

  // check if table is empty
  bool isEmpty() const;

  // add new edge to graph
  bool putChild(std::shared_ptr<Cell> new_cell,
                std::vector<std::shared_ptr<Cell>>& toPut);

  /// @brief function for changing childrens of cell in graph
  /// @param new_cell
  void changeChildrens(std::shared_ptr<Cell> new_cell);

  // erase Cell from table
  void eraseCell(const std::string& position);
  void eraseCell(const int& row, const int& column);

  // print all connections i graph
  void printConnections(std::shared_ptr<Cell> master) const {
    m_graph.printChildrens(master);
    m_graph.printParents(master);
  }

  // show formula from cell
  void showFormula(const std::string& position) const;

  // import and export from json file
  nlohmann::json toJSON() const;
  void importFromJSON(const nlohmann::json& j);

  // get Value from cell as string
  std::string getValue(const std::string& position) const;
};