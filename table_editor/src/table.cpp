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
  int maxDigits = 0;
  if (rows > 0) maxDigits = std::to_string(rows).length() + 1;
  return maxDigits;
}

std::ostream& Table::print(std::ostream& os) const {
  int colWidth = 11;
  int firstColumn = get_max_length(m_rows);
  std::cout << "first column: " << firstColumn << std::endl;

  // Print column numbers
  os << std::setw(firstColumn) << "|";
  for (long int i = 0; i < m_columns; i++) {
    std::string identifier = get_cell_id(i);
    os << std::setw(colWidth - identifier.length()) << std::setfill(' ')
       << identifier << "|";
  }
  os << std::endl;

  // Print horizontal separator
  os << std::setw(firstColumn) << "+";
  for (long int i = 0; i < m_columns; i++) {
    os << std::setw(colWidth) << std::setfill('-') << "+";
  }
  os << std::setfill(' ') << std::endl;

  // Print table
  for (long int i = 0; i < m_rows; i++) {
    // Print row number
    os << std::setw(firstColumn - 1) << std::setfill(' ') << i + 1 << "|";

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

    // Print horizontal separator
    os << "-" << std::setw(firstColumn - 1) << std::setfill('-') << "+";
    for (long int i = 0; i < m_columns; i++) {
      os << std::setw(colWidth) << std::setfill('-') << "+";
    }
    os << std::endl;
  }

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

std::string outLetters(std::string line, int& shift) {
  std::string letters;
  for (size_t i = 0; i < line.length(); i++) {
    char ch = line[i];
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
      throw std::invalid_argument("Invalid argument");
    }
    if (isdigit(line[i])) {
      shift = i;
      break;
    }
    letters += ch;
  }
  return letters;
}

Cell* Table::getCell(const std::string position) const {
  // input can be A1 take the first letter and convert it to number
  int shift = 0;
  std::string letters;

  if (position.length() == 0) return nullptr;

  letters = outLetters(position, shift);

  int column = get_column_index(letters);
  int row = std::stoi(position.substr(shift));
  std::cout << " i take the position\n";
  if (column > this->m_columns || row > this->m_rows || column <= 0 ||
      row <= 0) {
    throw std::out_of_range("Out of range");
  }

  return this->m_table[row - 1][column - 1] == nullptr
             ? nullptr
             : this->m_table[row - 1][column - 1];
}

bool check_if_number(std::string number) {
  std::cout << "check for this number: " << number
            << " length: " << number.length() << std::endl;
  for (char c : number) {
    if (!isdigit(c) && c != '.') {
      return false;
    }
  }
  std::cout << " check_number -----------true number: " << number << std::endl;
  return true;
}

Cell Table::evaluate(const std::string& postfix) const {
  std::stack<Cell> operands;
  std::stringstream ss(postfix);
  std::string cell_token;
  std::string text;

  while (ss >> cell_token) {
    std::cout << "cell token: " << cell_token << std::endl;
    if (cell_token == "+" || cell_token == "-" || cell_token == "*" ||
        cell_token == "/") {
      Cell operand2 = operands.top();
      operands.pop();
      Cell operand1 = operands.top();
      operands.pop();

      switch (cell_token[0]) {
        case '+':
          operands.push(Cell(operand1 + operand2));
          std::cout << "operatoion +" << std::endl;
          break;
        case '-':
          operands.push(Cell(operand1 - operand2));
          std::cout << "operatoion -" << std::endl;
          break;
        case '*':
          operands.push(Cell(operand1 * operand2));
          std::cout << "operatoion *" << std::endl;
          break;
        case '/':
          operands.push(Cell(operand1 / operand2));
          std::cout << "operatoion /" << std::endl;
          break;
      }
    } else {
      if (check_if_number(
              cell_token)) {  // check if number------------------------------
        operands.push(Cell(Number(std::stod(cell_token))));
        std::cout << "Push number:-------- " << cell_token << std::endl;
      } else if (cell_token[0] == '\"' ||
                 cell_token[cell_token.length() - 1] ==
                     '\"') {  // check if text----------------
        std::cout << "cell_token: " << cell_token << std::endl;
        if (cell_token[0] == '\"' && cell_token[cell_token.length() - 1] ==
                                         '\"') {  // first situation "hello"
          std::cout << "first situation" << std::endl;
          text = cell_token.substr(1, cell_token.length() - 2);
          operands.push(Cell(Text(text)));
        } else if (cell_token[0] == '\"') {  // second situation "hello ..."
          text = cell_token.substr(1, cell_token.length());
        } else if (cell_token[cell_token.length() - 1] ==
                   '\"') {  // third situation "... hello"
          text += cell_token.substr(0, cell_token.length() - 1);
          operands.push(Cell(Text(text)));
        }
      } else {  // check if cell----------------
        Cell* cell = getCell(cell_token);
        if (cell == nullptr) {
          operands.push(Cell(Text("")));
        } else {
          operands.push(*cell);

          std::cout << "Push cell:-------- " << *cell << std::endl;
        }
      }
    }
  }
  std::cout << "===========KONEC FOR CYKLU====================" << std::endl;

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

void Table::setCell(Cell* cell, std::string position, std::string formula) {
  int shift = 0;
  std::string letters = outLetters(position, shift);

  cell->setFormula(formula);

  int column = get_column_index(letters);
  int row = std::stoi(position.substr(shift));

  if (column > this->m_columns || row > this->m_rows || column <= 0 ||
      row <= 0) {
    throw std::out_of_range("Out of range");
  }

  if (this->m_table[row - 1][column - 1] != nullptr) {
    delete this->m_table[row - 1][column - 1];
  }

  this->m_table[row - 1][column - 1] = cell;
}