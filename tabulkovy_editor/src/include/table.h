#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "../include/cell.h"

class Table {
 private:
  std::vector<std::vector<Cell*>> m_table;
  long int m_rows;
  long int m_columns;

 public:
  Table();
  Table(const Table& table);
  void setSize(const int& rows, const int& columns);
  void setValue(const int& row, const int& column, const Cell& cell);
  long int getRows() const;
  long int getColumns() const;
  ~Table();
  Table& operator=(const Table& table);
  friend std::ostream& operator<<(std::ostream& os, const Table& table);
  std::ostream& print(std::ostream& os) const;
};