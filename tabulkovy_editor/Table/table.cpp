#include "table.h"

#include <iostream>
#include <string>
#include <vector>

Table::Table() {}

Table::Table(const Table& table) : m_table(table.m_table) {}

Table::~Table() {}

Table& Table::operator=(const Table& table) {
  if (this != &table) {
    this->m_table = table.m_table;
  }
  return *this;
}

std::ostream& operator<<(std::ostream& os, const Table& table) {
  return table.print(os);
}

void Table::addCell(const Cell& cell) {
  if (this->m_table.empty()) {
    this->m_table.push_back(std::vector<Cell>());
  }
  this->m_table.back().push_back(cell);
}

std::ostream& Table::print(std::ostream& os) const {
  for (auto& row : this->m_table) {
    for (auto& cell : row) {
      if (cell.getObject() != nullptr)
        os << cell << " | ";
      else
        os << " NULL "
           << " | ";
    }
    os << std::endl;
  }

  return os;
}

void Table::setSize(const int& rows, const int& columns) {
  this->m_rows = rows + 1;
  this->m_columns = columns + 1;
  this->m_table.resize(m_rows, std::vector<Cell>(m_columns, Cell()));
}

void Table::setValue(const int& row, const int& column, const Cell& cell) {
  if (row < 0 || column < 0) {
    throw std::out_of_range("Row or column is out of range");
  }
  if (size_t(row) >= this->m_rows || size_t(column) >= this->m_columns) {
    setSize(row, column);
  }
  this->m_table[row][column] = cell;
}

size_t Table::getRows() const { return this->m_rows; }

size_t Table::getColumns() const { return this->m_columns; }