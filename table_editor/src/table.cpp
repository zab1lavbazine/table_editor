#include "../include/table.h"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// support functions

int get_column_index(std::string& column) {
  int columnIndex = 0;
  int base = 26;
  for (size_t i = 0; i < column.length(); i++) {
    // check for all capital letters
    if (column[i] < 'A' || column[i] > 'Z') {
      throw std::invalid_argument("Invalid letter for column");
    }
    int digitValue = column[i] - 'A' + 1;
    columnIndex += digitValue * pow(base, column.length() - i - 1);
  }
  return columnIndex;
}

int get_row_index(std::string row) {
  // check for all numbers
  for (size_t i = 0; i < row.length(); i++) {
    if (row[i] < '0' || row[i] > '9') {
      throw std::invalid_argument("Invalid number for row");
    }
  }
  return std::stoi(row);
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

POS Table::get_position(const std::string& position) const {
  int shift = 0;
  std::string letters = outLetters(position, shift);

  int column = get_column_index(letters);
  int row = get_row_index(position.substr(shift, position.length()));

  if (column <= 0 || row <= 0) throw std::out_of_range("get position error");

  if (column > this->m_columns || row >= this->m_rows) {
    throw std::out_of_range("too big position");
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

void Table::setValue(const std::string& position, const std::string& formula) {
  std::vector<std::shared_ptr<Cell>> toPut;
  std::cout << "position: >" << position << "< formula: " << formula
            << std::endl;

  std::shared_ptr<Cell> new_cell = HandleOperands(formula, toPut);
  POS pos;
  try {
    pos = get_position(position);
  } catch (const std::exception& e) {
    std::cout << "error" << std::endl;
    return;
  }
  std::shared_ptr<Cell> current_cell =
      this->m_table[pos.row - 1][pos.column - 1];

  current_cell.get()->setObject(new_cell.get()->getObject()->clone());
  current_cell.get()->setFormula(new_cell.get()->getFormula());

  if (toPut.size() > 0)
    putChild(current_cell, toPut);
  else
    m_graph.removeParents(current_cell);
  changeChildrens(current_cell);
}

void Table::setValueFormula(const std::string& position,
                            std::shared_ptr<Cell> cell) {
  POS pos = get_position(position);
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
  POS pos = get_position(position);

  std::cout << position << "\n"
            << this->m_table[pos.row - 1][pos.column - 1]->getCharacteistics()
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
  POS pos = get_position(position);
  return this->m_table[pos.row - 1][pos.column - 1];
}

bool check_if_number(std::string number) {
  for (char c : number) {
    if (!isdigit(c) && c != '.' && c != '-') {
      return false;
    }
  }
  return true;
}

Cell Table::evaluate(const std::shared_ptr<Node>& node,
                     std::vector<std::shared_ptr<Cell>>& toPut) const {
  if (node == nullptr) {
    return Cell();
  }

  if (node->left == nullptr && node->right == nullptr) {
    // Leaf node
    std::string token = node->value;
    if (check_if_number(token)) {
      return Cell(Number(std::stod(token)));
    } else if (token[0] == '\"' && token[token.length() - 1] == '\"') {
      return Cell(Text(token.substr(1, token.length() - 2)));
    } else {
      bool minus = false;
      if (token[0] == '-') {
        minus = true;
        token = token.substr(1, token.length() - 1);
      }

      std::shared_ptr<Cell> cell = getCell(token);
      if (minus == true) {
        std::cout << "cell with -1" << std::endl;
        Cell new_cell = *cell * Cell(Number(-1));
        return new_cell;
      }

      toPut.push_back(cell);
      return *cell;
    }
  }

  Cell left = evaluate(node->left, toPut);
  Cell right = evaluate(node->right, toPut);

  std::string op = node->value;

  // check for null pointers

  if (left.getObject() == nullptr || right.getObject() == nullptr) {
    return Cell();
  }

  if (op == "+") {
    return left + right;
  } else if (op == "-") {
    return left - right;
  } else if (op == "*") {
    return left * right;
  } else if (op == "/") {
    return left / right;
  }

  return Cell();
}

std::shared_ptr<Cell> Table::HandleOperands(
    const std::string& expression, std::vector<std::shared_ptr<Cell>>& toPut) {
  std::shared_ptr<Node> root = m_handler.buildParseTree(expression);
  // m_handler.printParseTree(root);

  Cell new_cell = evaluate(root, toPut);  // evaluate expression
  new_cell.setFormula(root);              // set formula to cell

  std::shared_ptr<Cell> cell =
      std::make_shared<Cell>(new_cell);  // make cell and pointer to it

  return cell;
}

void Table::eraseCell(const std::string& position) {
  POS pos = get_position(position);
  // delete from all connections

  m_graph.removeChildrens(this->m_table[pos.row - 1][pos.column - 1]);
  m_graph.removeParents(this->m_table[pos.row - 1][pos.column - 1]);

  // delete from table
  std::shared_ptr<Cell> new_cell(new Cell(EMPTY()));
  this->m_table[pos.row - 1][pos.column - 1] = new_cell;
}

void Table::eraseCell(const int& x, const int& y) {
  if (x > this->m_columns || y > this->m_rows || x <= 0 || y <= 0) {
    throw std::out_of_range("erase error");
  }

  // delete from all connections
  m_graph.removeChildrens(this->m_table[y - 1][x - 1]);
  m_graph.removeParents(this->m_table[y - 1][x - 1]);

  // delete from table
  std::shared_ptr<Cell> new_cell(new Cell(EMPTY()));
  this->m_table[y - 1][x - 1] = new_cell;
}

void Table::changeValue(const std::string& position, Object* new_value) {
  POS pos = get_position(position);

  std::shared_ptr<Cell> current_cell =
      this->m_table[pos.row - 1][pos.column - 1];
  current_cell.get()->setObject(new_value);  // set object delete also formula

  // delete parents
  m_graph.removeParents(current_cell);

  // rewrite childs
  changeChildrens(current_cell);
}

void Table::changeValue(const std::string& position,
                        const std::string& formula) {
  std::vector<std::shared_ptr<Cell>> toPut;

  std::shared_ptr<Cell> new_cell = HandleOperands(formula, toPut);
  POS pos = get_position(position);
  std::shared_ptr<Cell> current_cell =
      this->m_table[pos.row - 1][pos.column - 1];
  current_cell.get()->setObject(new_cell.get()->getObject()->clone());
  current_cell.get()->setFormula(new_cell.get()->getFormula());

  if (toPut.size() > 0) {
    putChild(current_cell, toPut);
  }

  m_graph.removeParents(current_cell);

  // rewrite childs
  changeChildrens(current_cell);
}

void Table::changeChildrens(std::shared_ptr<Cell> cell) {
  std::vector<std::shared_ptr<Cell>> toPut;
  for (auto& child : m_graph.getChildrens(cell)) {
    Cell new_cell = evaluate(child->getFormula(), toPut);
    child.get()->changeObject(new_cell.getObject()->clone());
    changeChildrens(child);
  }
}

void Table::putChild(std::shared_ptr<Cell> new_cell,
                     std::vector<std::shared_ptr<Cell>>& toPut) {
  for (std::shared_ptr<Cell> master : toPut) {
    m_graph.addEdge(master, new_cell);
  }
  toPut.clear();
}

void Table::showFormula(const std::string& position) const {
  POS pos = get_position(position);
  std::cout << "formula: "
            << this->m_table[pos.row - 1][pos.column - 1]->toStringFormula()
            << std::endl;
}
