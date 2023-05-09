#include "../include/table.h"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <memory>
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
  if (rows > this->m_rows) {
    this->m_rows = rows;
    this->m_table.resize(m_rows);
    for (long int i = 0; i < m_rows; i++) {
      this->m_table[i].resize(m_columns);
    }
  }
  if (columns > this->m_columns) {
    this->m_columns = columns;
    for (long int i = 0; i < m_rows; i++) {
      this->m_table[i].resize(m_columns);
    }
  }
}

Table& Table::operator=(const Table& table) {
  this->m_rows = table.m_rows;
  this->m_columns = table.m_columns;
  this->m_table = table.m_table;
  return *this;
}

void Table::setValue(const int& row, const int& column, const Cell& cell) {
  if (cell.getObject() == nullptr) {
    throw std::invalid_argument("Invalid argument");
  }
  // check table int this sell for Object and delete it

  if (row <= 0 || column <= 0) {
    throw std::out_of_range("Out of range");
  } else if (row > this->m_rows || column > this->m_columns) {
    setSize(row, column);
  }
  if (this->m_table[row - 1][column - 1] != nullptr) {
    delete this->m_table[row - 1][column - 1];
  }
  this->m_table[row - 1][column - 1] = new Cell(cell);
}

long int Table::getRows() const { return this->m_rows; }

long int Table::getColumns() const { return this->m_columns; }

std::ostream& operator<<(std::ostream& os, const Table& table) {
  return table.print(os);
}

void Table::ShowCell(const int row, const int column) const {
  if (row <= 0 || column <= 0) {
    throw std::out_of_range("Out of range");
  } else if (row > this->m_rows || column > this->m_columns) {
    throw std::out_of_range("Out of range");
  }
  std::cout << "Cell: " << this->m_table[row - 1][column - 1]->toString()
            << std::endl;
}

std::string get_cell_id(int column) {
  std::string identifier = "";
  int number = column / 26;
  if (number == 0) {
    identifier += 'A' + column;
  } else {
    identifier += 'A' + number - 1;
    identifier += 'A' + column % 26;
  }
  return identifier;
}

int get_max_length(const int& rows) {
  int FirtsColumn = 0;
  int number = rows / 26;
  if (number == 0)
    FirtsColumn = 2;
  else {
    if (number / 100 == 0) {
      FirtsColumn = 3;
    } else {
      FirtsColumn = 4;
    }
  }
  return FirtsColumn;
}

std::ostream& Table::print(std::ostream& os) const {
  int colWidth = 11;
  int FirtsColumn = get_max_length(m_rows);

  // print column numbers
  os << std::setw(FirtsColumn) << "|";
  for (long int i = 0; i < m_columns; i++) {
    std::string identifier = get_cell_id(i);
    os << std::setw(colWidth - 1) << std::setfill(' ') << identifier << "|";
  }
  os << std::endl;

  os << std::setw(FirtsColumn) << "+";
  for (long int i = 0; i < m_columns; i++) {
    os << std::setw(colWidth) << std::setfill('-') << "+";
  }
  os << std::setfill(' ') << std::endl;

  // print table
  for (long int i = 0; i < m_rows; i++) {
    // print letter for each row

    int shift = 0;
    // make shift larger if number is larger
    if (i / 100 == 0) {
      shift = 2;
    } else {
      shift = 3;
    }
    os << i + 1 << std::setw(FirtsColumn - shift) << std::setfill(' ') << "|";
    for (long int j = 0; j < m_columns; j++) {
      if (this->m_table[i][j] == nullptr) {
        os << std::setw(colWidth) << std::setfill(' ') << "|";
      } else {
        std::string output = this->m_table[i][j]->toString();
        if (int(output.length()) > colWidth - 1) {
          output = output.substr(0, colWidth - 4) + "...";
        }
        os << std::setw(colWidth - 1) << std::setfill(' ') << output << "|";
      }
    }
    os << std::endl;
    // make the border
    if (i == m_rows - 1) break;
    os << "-" << std::setw(FirtsColumn - 1) << std::setfill('-') << "+";
    for (long int i = 0; i < m_columns; i++) {
      os << std::setw(colWidth) << std::setfill('-') << "+";
    }

    os << std::endl;
  }

  // print last row
  os << std::setw(FirtsColumn) << "+";
  for (long int i = 0; i < m_columns; i++) {
    os << std::setw(colWidth) << std::setfill('-') << "+";
  }
  os << std::setfill(' ') << std::endl;

  return os;
}

int get_column_index(std::string column) {
  int columnIndex = 0;
  int base = 26;
  for (size_t i = 0; i < column.length(); i++) {
    int digitValue = column[i] - 'A' + 1;
    columnIndex += digitValue * pow(base, column.length() - i - 1);
  }
  return columnIndex;
}

Cell* Table::getCell(const std::string position) const {
  // input can be A1 take the first letter and convert it to number
  int shift = 0;
  std::string letters;

  if (position.length() == 0) throw std::invalid_argument("Invalid argument");

  for (size_t i = 0; i < position.length(); i++) {
    char ch = position[i];
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
      throw std::invalid_argument("Invalid argument");
    }
    if (isdigit(position[i])) {
      shift = i;
      break;
    }
    letters += ch;
  }

  int column = get_column_index(letters);
  int row = std::stoi(position.substr(shift));
  if (column > this->m_columns || row > this->m_rows || column <= 0 ||
      row <= 0) {
    throw std::out_of_range("Out of range");
  }

  return this->m_table[row - 1][column - 1] == nullptr
             ? nullptr
             : this->m_table[row - 1][column - 1];
}

Cell Table::evaluate(const std::string& postfix) const {
  std::stack<Cell> operands;
  bool letter_check = 0;
  bool number_check = 0;
  std::string cell_token;
  for (size_t i = 0; i < postfix.length(); i++) {
    char ch = postfix[i];
    // taking letter or letters
    if (!isdigit(ch) && ch != '+' && ch != '-' && ch != '*' && ch != '/') {
      if (cell_token.length() != 0) {  // upload cell to stack
        Cell* cell = getCell(cell_token);
        if (cell == nullptr) {
          operands.push(Cell(Text("empty")));
        } else {
          operands.push(*cell);
        }
        std::cout << "cell token: " << cell_token << std::endl;
        cell_token = "";
        letter_check = number_check = false;
      }
      cell_token += ch;
      letter_check = true;
    } else if (isdigit(ch)) {  // taking number
      number_check = true;
      cell_token += ch;
    } else if (number_check == true && letter_check == true &&
               (ch == '+' || ch == '-' || ch == '*' ||
                ch == '/')) {          // taking operator
      if (cell_token.length() != 0) {  // upload cell to stack
        Cell* cell = getCell(cell_token);
        if (cell == nullptr) {
          operands.push(Cell(Text("empty")));
        } else {
          operands.push(*cell);
        }
        std::cout << "cell token: " << cell_token << std::endl;
        cell_token = "";
        letter_check = number_check = false;
      }
      number_check = letter_check = false;
      Cell operand2 = operands.top();
      operands.pop();
      Cell operand1 = operands.top();
      operands.pop();

      switch (ch) {
        case '+':
          operands.push(Cell(operand1 + operand2));
          break;
        case '-':
          operands.push(Cell(operand1 - operand2));
          break;
        case '*':
          operands.push(Cell(operand1 * operand2));
          break;
        case '/':
          operands.push(Cell(operand1 / operand2));
          break;
      }
    }
  }
  if (operands.size() <= 0) {
    return Cell();
  }
  return operands.top();
}

Cell* Table::HandleOperands(const std::string& expression) const {
  std::string postfix = MessHandler::infixToPostfix(expression);
  Cell new_cell = evaluate(postfix);
  if (new_cell.getObject() == nullptr) {
    return nullptr;
  }
  std::cout << "new cell: " << new_cell.toString() << std::endl;
  return new Cell(new_cell);
}