#include "../include/table.h"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// support functions

struct POS {
  int row;
  int column;
};

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

POS get_position(std::string position) {
  int shift = 0;
  std::string letters = outLetters(position, shift);

  int column = get_column_index(letters);
  int row = std::stoi(position.substr(shift));
  if (column <= 0 || row <= 0) {
    throw std::out_of_range("get position error");
  }

  POS pos;
  pos.row = row;
  pos.column = column;
  return pos;
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

  // delete from m_graph
  std::unordered_set<std::shared_ptr<Cell>> parents =
      this->m_table[row - 1][column - 1]->getSetParents();
  for (auto& parent_ptr : parents) {
    m_graph.removeEdge(parent_ptr, this->m_table[row - 1][column - 1]);
    parent_ptr->removeChild(this->m_table[row - 1][column - 1]);
  }
  for (auto& child_ptr : this->m_table[row - 1][column - 1]->getSetChilds()) {
    m_graph.removeEdge(this->m_table[row - 1][column - 1], child_ptr);
    child_ptr->removeParent(this->m_table[row - 1][column - 1]);
  }

  this->m_table[row - 1][column - 1] = new_cell;
}

void Table::setValue(const std::string& position,
                     const Cell& cell) {  // delete the prev data from the cell
  // with formula and vector of childs

  POS pos = get_position(position);

  std::unordered_set<std::shared_ptr<Cell>> parents =
      this->m_table[pos.row - 1][pos.column - 1]->getSetParents();
  std::unordered_set<std::shared_ptr<Cell>> childs =
      this->m_table[pos.row - 1][pos.column - 1]->getSetChilds();

  for (auto& parent_ptr : parents) {
    m_graph.removeEdge(parent_ptr, this->m_table[pos.row - 1][pos.column - 1]);
    parent_ptr->removeChild(this->m_table[pos.row - 1][pos.column - 1]);
  }
  for (auto& child_ptr : childs) {
    m_graph.removeEdge(this->m_table[pos.row - 1][pos.column - 1], child_ptr);
    child_ptr->removeParent(this->m_table[pos.row - 1][pos.column - 1]);
  }
  std::shared_ptr<Cell> new_cell(new Cell(cell));  // new cell
  this->m_table[pos.row - 1][pos.column - 1] = new_cell;
}

void Table::setValueFormula(const std::string& position,
                            std::shared_ptr<Cell> cell) {
  POS pos = get_position(position);

  std::unordered_set<std::shared_ptr<Cell>> parents = cell->getSetParents();

  std::unordered_set<std::shared_ptr<Cell>> childs =
      this->m_table[pos.row - 1][pos.column - 1]->getSetChilds();  // childs

  for (auto& child : childs) {
    m_graph.addEdge(cell, child);
  }

  this->m_table[pos.row - 1][pos.column - 1] = cell;
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

std::shared_ptr<Cell> Table::getCell(const std::string position) const {
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

  return this->m_table[row - 1][column - 1];
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
                     std::vector<std::shared_ptr<Cell>>& toPut) const {
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
        std::shared_ptr<Cell> cell = getCell(cell_token);
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

std::shared_ptr<Cell> Table::HandleOperands(const std::string& expression) {
  std::string postfix = MessHandler::infixToPostfix(expression);
  std::vector<std::shared_ptr<Cell>> toPut;
  Cell new_cell = evaluate(postfix, toPut);

  //
  std::shared_ptr<Cell> cell = std::make_shared<Cell>(new_cell);
  cell->setFormula(postfix);  // save formula for the next operations

  if (toPut.size() > 0 && toPut[0] != nullptr) {
    putChild(cell, toPut);  // put child into taken cells
  }
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
  POS pos = get_position(position);

  Cell* current_cell = this->m_table[pos.row - 1][pos.column - 1].get();
  current_cell->setObject(new_value);

  // create here method for changing value in childrens
  if (current_cell->getChildrencount() != 0) {
    changeChildrens(current_cell);
  }
}

void Table::changeValue(const std::string& position,
                        const std::string& formula) {
  std::shared_ptr<Cell> cell = HandleOperands(formula);

  POS pos = get_position(position);
  Cell* current_cell = this->m_table[pos.row - 1][pos.column - 1].get();
  current_cell->setObject(cell->getObject()->clone());
  current_cell->setFormula(cell->getFormula());

  // rewrite childs
  if (current_cell->getChildrencount() != 0) {
    changeChildrens(current_cell);
  }
}

void Table::changeChildrens(Cell* cell) {
  std::vector<std::shared_ptr<Cell>> toPut;
  for (auto& child : cell->getSetChilds()) {
    Cell new_cell = evaluate(child.get()->getFormula(), toPut);
    Cell* child_ptr = child.get();
    child->changeObject(new_cell.getObject()->clone());
    child->setSetParents(new_cell.getSetParents());
    changeChildrens(child_ptr);
  }
}

void Table::putChild(std::shared_ptr<Cell> new_cell,
                     std::vector<std::shared_ptr<Cell>>& toPut) {
  for (std::shared_ptr<Cell> master : toPut) {
    master->addChild(new_cell);
    m_graph.addEdge(master, new_cell);
  }
  toPut.clear();
}