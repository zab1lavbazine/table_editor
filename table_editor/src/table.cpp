#include "../include/table.h"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// support functions

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

// -----------------------------

Table::Table() {
  this->m_rows = 0;
  this->m_columns = 0;
}

Table::~Table() {}

Table::Table(const Table& table) {
  this->m_rows = table.m_rows;
  this->m_columns = table.m_columns;
  this->m_table = table.m_table;
}

void Table::setSize(const int& rows, const int& columns) {
  if (rows > this->m_rows) {
    this->m_table.resize(rows);

    for (int i = this->m_rows; i < rows; i++) {
      this->m_table[i].resize(columns);

      for (int j = 0; j < columns; j++) {
        if (this->m_table[i][j] == nullptr) {
          std::shared_ptr<Cell> new_cell(new Cell(EMPTY()));
          this->m_table[i][j] = new_cell;
        }
      }
    }

    this->m_rows = rows;
  }

  if (columns > this->m_columns) {
    for (int i = 0; i < this->m_rows; i++) {
      this->m_table[i].resize(columns);

      for (int j = this->m_columns; j < columns; j++) {
        if (this->m_table[i][j] == nullptr) {
          std::shared_ptr<Cell> new_cell(new Cell(EMPTY()));
          this->m_table[i][j] = new_cell;
        }
      }
    }

    this->m_columns = columns;
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
    throw std::out_of_range("set value error");
  } else if (row > this->m_rows || column > this->m_columns) {
    setSize(row, column);
  }

  // clear vector and formula
  this->m_table[row - 1][column - 1]->clearChildrens();
  this->m_table[row - 1][column - 1]->clearParents();
  this->m_table[row - 1][column - 1]->setFormula("");

  std::shared_ptr<Cell> new_cell(new Cell(cell));  // new cell

  // check if this cell has something in it and delete

  this->m_table[row - 1][column - 1] = new_cell;
}

void Table::setValue(const std::string& position,
                     const Cell& cell) {  // delete the prev data from the cell
                                          // with formula and vector of childs
  int shift = 0;
  std::string letters = outLetters(position, shift);

  int column = get_column_index(letters);
  int row = std::stoi(position.substr(shift));

  if (column > this->m_columns || row > this->m_rows || column <= 0 ||
      row <= 0) {
    throw std::out_of_range("set value error");
  }

  std::shared_ptr<Cell> new_cell(new Cell(cell));  // new cell

  this->m_table[row - 1][column - 1] = new_cell;
}

void Table::setValueFormula(const std::string& position,
                            std::shared_ptr<Cell> cell) {
  int shift = 0;
  std::string letters = outLetters(position, shift);

  int column = get_column_index(letters);
  int row = std::stoi(position.substr(shift));

  if (column > this->m_columns || row > this->m_rows || column <= 0 ||
      row <= 0) {
    throw std::out_of_range("set value formula error");
  }

  std::vector<std::shared_ptr<Cell>> parents = cell->getVectorParents();

  std::vector<std::shared_ptr<Cell>> childs =
      this->m_table[row - 1][column - 1]->getVectorChilds();  // childs

  if (parents.size() != 0 && childs.size() != 0) {
    std::cout << "checking for cycle" << std::endl;
    for (auto& parent_ptr : parents) {
      for (auto& child_ptr : childs) {
        Cell *parent = parent_ptr.get(), *child = child_ptr.get();
        if (*parent == *child) {
          throw std::invalid_argument("cycle error");
        }
      }
    }
  }

  std::cout << "without cycle" << std::endl;

  if (childs.size() != 0) {
    cell->setVectorChilds(childs);
    changeChildrens(cell.get());
  }

  this->m_table[row - 1][column - 1] = cell;
}

long int Table::getRows() const { return this->m_rows; }

long int Table::getColumns() const { return this->m_columns; }

std::ostream& operator<<(std::ostream& os, const Table& table) {
  return table.print(os);
}

void Table::ShowCell(const int row, const int column) const {
  if (row <= 0 || column <= 0) {
    throw std::out_of_range("show cell error");
  } else if (row > this->m_rows || column > this->m_columns) {
    throw std::out_of_range("show cell error");
  }
  std::cout << "Cell: " << this->m_table[row - 1][column - 1]->toString()
            << std::endl;
}

void Table::ShowCell(const std::string position) const {
  std::cout << "position: " << position << std::endl;
  int shift = 0;
  std::string letters = outLetters(position, shift);

  int column = get_column_index(letters);
  int row = std::stoi(position.substr(shift));

  if (column > this->m_columns || row > this->m_rows || column <= 0 ||
      row <= 0) {
    throw std::out_of_range("show cell error");
  }

  std::cout << position << "\n"
            << this->m_table[row - 1][column - 1]->getCharacteistics()
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

Cell* Table::getCell(const std::string position) const {
  // input can be A1 take the first letter and convert it to number
  int shift = 0;
  std::string letters;

  if (position.length() == 0) return nullptr;

  letters = outLetters(position, shift);

  int column = get_column_index(letters);
  int row = std::stoi(position.substr(shift));
  if (column > this->m_columns || row > this->m_rows || column <= 0 ||
      row <= 0) {
    throw std::out_of_range("get cell error");
  }

  return this->m_table[row - 1][column - 1].get();
}

bool check_if_number(std::string number) {
  for (char c : number) {
    if (!isdigit(c) && c != '.') {
      return false;
    }
  }
  return true;
}

Cell Table::evaluate(const std::string& postfix,
                     std::vector<Cell*>& toPut) const {
  std::stack<Cell> operands;
  std::stringstream ss(postfix);
  std::string cell_token;
  std::string text;

  while (ss >> cell_token) {
    if (cell_token == "+" || cell_token == "-" || cell_token == "*" ||
        cell_token == "/") {
      Cell operand2 = operands.top();
      operands.pop();
      Cell operand1 = operands.top();
      operands.pop();

      switch (cell_token[0]) {
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
    } else {
      if (check_if_number(
              cell_token)) {  // check if number------------------------------
        operands.push(Cell(Number(std::stod(cell_token))));
      } else if (cell_token[0] == '\"' ||
                 cell_token[cell_token.length() - 1] ==
                     '\"') {  // check if text----------------
        if (cell_token[0] == '\"' && cell_token[cell_token.length() - 1] ==
                                         '\"') {  // first situation "hello"
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
        toPut.push_back(cell);
        operands.push(*cell);
      }
    }
  }

  if (operands.size() <= 0) {
    return Cell();
  }
  return operands.top();
}

std::shared_ptr<Cell> Table::HandleOperands(
    const std::string& expression) const {
  std::string postfix = MessHandler::infixToPostfix(expression);
  std::vector<Cell*> toPut;
  Cell new_cell = evaluate(postfix, toPut);

  //
  std::shared_ptr<Cell> cell(new Cell(new_cell));
  cell->setFormula(postfix);  // save formula for the next operations

  putChild(cell, toPut);  // put child into taken cells
  return cell;
}

void Table::eraseCell(const std::string& position) {
  int shift = 0;
  std::string letters = outLetters(position, shift);

  int column = get_column_index(letters);
  int row = std::stoi(position.substr(shift));

  if (column > this->m_columns || row > this->m_rows || column <= 0 ||
      row <= 0) {
    throw std::out_of_range("erase error");
  }

  this->m_table[row - 1][column - 1] = nullptr;
}

void Table::eraseCell(const int& x, const int& y) {
  if (x > this->m_columns || y > this->m_rows || x <= 0 || y <= 0) {
    throw std::out_of_range("erase error");
  }

  this->m_table[y - 1][x - 1] = nullptr;
}

void Table::changeValue(const std::string& position, Object* new_value) {
  int shift = 0;
  std::string letters = outLetters(position, shift);

  int column = get_column_index(letters);
  int row = std::stoi(position.substr(shift));

  if (column > this->m_columns || row > this->m_rows || column <= 0 ||
      row <= 0) {
    throw std::out_of_range("change value error");
  }

  Cell* current_cell = this->m_table[row - 1][column - 1].get();
  current_cell->setObject(new_value);

  // create here method for changing value in childrens
  if (current_cell->getChildrencount() != 0) {
    changeChildrens(current_cell);
  }
}

void Table::changeChildrens(Cell* cell) {
  std::vector<Cell*> toPut;
  for (int i = 0; i < cell->getChildrencount(); i++) {
    std::cout << "change childrens-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- "
                 "-- -- -- -- -- --"
              << std::endl;
    std::string formula = cell->getChild(i)->getFormula();
    Cell* new_cell = new Cell(evaluate(formula, toPut));
    Cell* child = cell->getChild(i);
    child->changeObject(new_cell->getObject()->clone());
    std::cout << "new child: " << child->getCharacteistics() << std::endl;
    child->setVectorParents(new_cell->getVectorParents());
    changeChildrens(child);
    delete new_cell;
  }
}

void Table::putChild(std::shared_ptr<Cell> new_cell,
                     std::vector<Cell*>& toPut) const {
  for (Cell* master : toPut) {
    std::shared_ptr<Cell> new_parent = std::make_shared<Cell>(*new_cell);
    new_cell->addParent(new_parent);
    std::cout << "parent: " << new_parent->getCharacteistics() << std::endl;
    master->addChild(new_cell);  // child save into parent
  }
  toPut.clear();
}