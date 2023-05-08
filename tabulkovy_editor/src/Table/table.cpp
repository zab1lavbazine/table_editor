#include "../include/table.h"

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

Table::Table() {
  this->m_rows = 0;
  this->m_columns = 0;
}

Table::~Table() {
  for (long int i = 0; i < this->m_rows; i++) {
    for (long int j = 0; j < this->m_columns; j++) {
      delete this->m_table[i][j];
    }
  }
}

Table::Table(const Table& table) {
  this->m_rows = table.m_rows;
  this->m_columns = table.m_columns;
  this->m_table = table.m_table;
}

void Table::setSize(const int& rows, const int& columns) {
  this->m_rows = rows + 1;
  this->m_columns = columns + 1;
  this->m_table.resize(m_rows);
  for (long int i = 0; i < m_rows; i++) {
    this->m_table[i].resize(m_columns);
  }
}

Table& Table::operator=(const Table& table) {
  this->m_rows = table.m_rows;
  this->m_columns = table.m_columns;
  this->m_table = table.m_table;
  return *this;
}

void Table::setValue(const int& row, const int& column, const Cell& cell) {
  if (row < 0 || column < 0) {
    throw std::out_of_range("Out of range");
  } else if (row >= this->m_rows || column >= this->m_columns) {
    setSize(row, column);
  }
  this->m_table[row][column] = new Cell(cell);
}

long int Table::getRows() const { return this->m_rows; }

long int Table::getColumns() const { return this->m_columns; }

std::ostream& operator<<(std::ostream& os, const Table& table) {
  return table.print(os);
}

std::ostream& Table::print(std::ostream& os) const {
  for (long int i = 0; i < this->m_rows; i++) {
    for (long int j = 0; j < this->m_columns; j++) {
      if (this->m_table[i][j] != nullptr) {
        os << std::setw(5) << *this->m_table[i][j];
      } else {
        os << std::setw(10) << "";
      }
    }
    os << std::endl;
  }
  return os;
}