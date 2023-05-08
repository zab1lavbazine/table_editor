#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "cell.h"

class Table {
 private:
  std::vector<std::vector<Cell>> m_table;
  size_t m_rows;
  size_t m_columns;

 public:
  Table();
  Table(const Table& table);
  void setSize(const int& rows, const int& columns);
  void changeSize(const int& rows, const int& columns);
  void setValue(const int& row, const int& column, const Cell& cell);
  size_t getRows() const;
  size_t getColumns() const;
  ~Table();
  Table& operator=(const Table& table);
  friend std::ostream& operator<<(std::ostream& os, const Table& table);
  std::ostream& print(std::ostream& os) const;
  void addCell(const Cell& cell);
};