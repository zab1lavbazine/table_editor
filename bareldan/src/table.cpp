#include "../include/table.h"

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

POS TABLE::get_position(const std::string& position) const {
  int shift = 0;
  std::string letters = outLetters(position, shift);

  int column = get_column_index(letters);
  int row = get_row_index(position.substr(shift, position.length()));

  if (column <= 0 || row <= 0) throw std::out_of_range("get position error");

  if (column > this->m_columns || row > this->m_rows) {
    throw std::out_of_range("too big position");
  }

  POS pos;
  pos.row = row;
  pos.column = column;
  return pos;
}

// help functions for evaluations

bool is_text_token(const std::string& token) {
  return token.size() >= 2 && token.front() == '\"' && token.back() == '\"';
}

bool is_function(const std::string& token) {
  return token == "sin" || token == "cos";
}

bool is_negative_number(const std::string& token) {
  return token.size() > 1 && token[0] == '-';
}

// -----------------------------

TABLE::TABLE() {
  this->m_rows = 0;
  this->m_columns = 0;
}

TABLE::~TABLE() {}

void TABLE::setSize(const int& rows, const int& columns) {
  if (rows <= 0 || columns <= 0) {
    throw std::out_of_range("set size error");
  }

  if (rows != this->m_rows) {
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

  if (columns != this->m_columns) {
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

TABLE& TABLE::operator=(const TABLE& table) {
  this->m_rows = table.m_rows;
  this->m_columns = table.m_columns;
  for (int i = 0; i < m_rows; i++) {
    for (int j = 0; j < m_columns; j++) {
      this->m_table[i][j] = table.m_table[i][j];
    }
  }
  return *this;
}

void TABLE::setValue(const std::string& position, const std::string& formula) {
  std::vector<std::shared_ptr<Cell>> toPut;
  POS pos;
  try {
    pos = get_position(position);
  } catch (const std::out_of_range& e) {
    std::cout << "error: " << e.what() << std::endl;
    return;
  }

  // creating new cell with formula
  std::shared_ptr<Cell> new_cell = HandleOperands(formula, toPut);

  // getting current cell from table if it is empty
  std::shared_ptr<Cell> current_cell =
      this->m_table[pos.row - 1][pos.column - 1];

  // insert new cell to graph (parents and childrens)
  if (toPut.size() > 0) {
    // insert new cell to graph (parents and childrens)
    bool putted = putChild(current_cell, toPut);

    if (!putted) {
      return;
    }  // if there is a loop return and dont put inside
  } else {
    m_graph.removeParentsFromChildren(
        current_cell);  // delete parents if there are no
  }

  current_cell.get()->setObject(
      new_cell.get()->getObject()->clone());  // set new oject to current cell
  current_cell.get()->setFormula(
      new_cell.get()->getFormula());  // set formula to current cell

  changeChildrens(current_cell);  // rewrite all childrens
}

long int TABLE::getRows() const { return this->m_rows; }

long int TABLE::getColumns() const { return this->m_columns; }

std::ostream& operator<<(std::ostream& os, const TABLE& table) {
  return table.print(os);
}

void TABLE::ShowCell(const int row, const int column) const {
  if (row <= 0 || column <= 0) {
    throw std::out_of_range("show cell error");
  } else if (row > this->m_rows || column > this->m_columns) {
    throw std::out_of_range("show cell error");
  }
  std::cout << "Cell: " << this->m_table[row - 1][column - 1]->toString()
            << std::endl;
}

void TABLE::ShowCell(const std::string position) const {
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

std::ostream& TABLE::print(std::ostream& os) const {
  tabulate::Table table;
  std::vector<std::string> identifier;
  identifier.push_back(" ");
  // taking the first row with letters for columns
  for (int i = 0; i < m_columns; i++) {
    identifier.push_back(get_cell_id(i));
  }
  // loading the first row
  table.add_row(tabulate::Table::Row_t(identifier.begin(), identifier.end()));
  // coloring the first row
  for (int i = 0; i < m_columns; i++) {
    table[0][i + 1]
        .format()
        .font_color(tabulate::Color::yellow)
        .font_align(tabulate::FontAlign::center);
  }

  // loading the rest of the table
  for (int i = 0; i < m_rows; i++) {
    std::vector<std::string> row;
    row.push_back(std::to_string(i + 1));
    for (int j = 0; j < m_columns; j++) {
      // row.push_back(std::to_string(rowDigit));
      row.push_back(this->m_table[i][j]->toString());
    }
    table.add_row(tabulate::Table::Row_t{row.begin(), row.end()});
  }

  os << table << std::endl;
  return os;
}

std::shared_ptr<Cell> TABLE::getCell(const std::string position) const {
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

///
Cell TABLE::evaluate(const std::shared_ptr<Node>& node,
                     std::vector<std::shared_ptr<Cell>>& toPut) const {
  if (node == nullptr) {
    return Cell();
  }

  if (node->left == nullptr && node->right == nullptr) {
    return evaluateLeafNode(node->value, toPut);
  }

  Cell left = evaluate(node->left, toPut);
  Cell right = evaluate(node->right, toPut);

  return evaluateOperation(node->value, left, right);
}

Cell TABLE::evaluateLeafNode(const std::string& token,
                             std::vector<std::shared_ptr<Cell>>& toPut) const {
  if (check_if_number(token)) {
    return Cell(Number(std::stod(token)));
  } else if (is_text_token(token)) {
    return Cell(Text(token.substr(1, token.length() - 2)));
  } else if (is_function(token)) {
    return evaluateFunction(token);
  } else if (is_negative_number(token)) {
    return evaluateNegativeNumber(token, toPut);
  } else {
    std::shared_ptr<Cell> cell = getCell(token);
    toPut.push_back(cell);
    return *cell;
  }
}

Cell TABLE::evaluateOperation(const std::string& op, Cell& left,
                              Cell& right) const {
  if (op == "+") {
    return left + right;
  } else if (op == "-") {
    return left - right;
  } else if (op == "*") {
    return left * right;
  } else if (op == "/") {
    return left / right;
  } else if (op == "sin") {
    return left.getObject()->collide(*left.getObject(),
                                     Object::OPERATIONS::SIN);
  } else if (op == "cos") {
    return left.getObject()->collide(*left.getObject(),
                                     Object::OPERATIONS::COS);
  } else {
    return Cell();
  }
}

Cell TABLE::evaluateFunction(const std::string& functionName) const {
  if (functionName == "sin" || functionName == "cos") {
    throw std::invalid_argument(functionName + " error");
  }
  // Additional function evaluations if needed
  return Cell();
}

Cell TABLE::evaluateNegativeNumber(
    const std::string& token, std::vector<std::shared_ptr<Cell>>& toPut) const {
  std::shared_ptr<Cell> cell = getCell(token.substr(1));
  Cell newCell = *cell * Cell(Number(-1));
  toPut.push_back(cell);
  return newCell;
}

///

// Cell TABLE::evaluate(const std::shared_ptr<Node>& node,
//                      std::vector<std::shared_ptr<Cell>>& toPut) const {
//   if (node == nullptr) {  // check for null pointers
//     return Cell();
//   }

//   if (node->left == nullptr && node->right == nullptr) {
//     // Leaf node
//     std::string token = node->value;

//     if (check_if_number(token)) {  // check if the last is number
//       return Cell(Number(std::stod(token)));
//     } else if (token[0] == '\"' && token[token.length() - 1] ==
//                                        '\"') {  // check if the last is text

//       return Cell(Text(token.substr(1, token.length() - 2)));
//     } else if (token == "sin") {
//       throw std::invalid_argument("sin error");
//     } else if (token == "cos") {
//       throw std::invalid_argument("cos error");
//     } else {
//       bool minus = false;
//       if (token[0] == '-') {
//         minus = true;
//         token = token.substr(1, token.length() - 1);
//       }

//       std::shared_ptr<Cell> cell = getCell(token);
//       if (minus == true) {
//         std::cout << "cell with -1" << std::endl;
//         Cell new_cell = *cell * Cell(Number(-1));
//         return new_cell;
//       }

//       toPut.push_back(cell);
//       return *cell;
//     }
//   }

//   Cell left = evaluate(node->left, toPut);
//   Cell right = evaluate(node->right, toPut);

//   std::string op = node->value;

//   // check for null pointers

//   // if (op == "sin" || op == "cos") return Cell(Text(op)) * left;

//   if (op == "sin")
//     return left.getObject()->collide(*(left.getObject()),
//                                      Object::OPERATIONS::SIN);
//   if (op == "cos")
//     return left.getObject()->collide(*(left.getObject()),
//                                      Object::OPERATIONS::COS);

//   if (op == "-" && right.getObject() != nullptr && left.getObject() ==
//   nullptr)
//     return right * Cell(Number(-1));

//   if (left.getObject() == nullptr || right.getObject() == nullptr) {
//     return Cell();
//   }

//   if (op == "+") {
//     return left + right;
//   } else if (op == "-") {
//     return left - right;
//   } else if (op == "*") {
//     return left * right;
//   } else if (op == "/") {
//     return left / right;
//   }

//   return Cell();
// }

std::shared_ptr<Cell> TABLE::HandleOperands(
    const std::string& expression, std::vector<std::shared_ptr<Cell>>& toPut) {
  // creating parse tree and building it with the formula
  ParseTreeForFormula parseTree(expression);

  std::shared_ptr<Node> root = parseTree.buildParseTree();  // build parse tree
  if (root == nullptr) {
    throw std::invalid_argument("root for formula is null");
  }

  Cell new_cell = evaluate(root, toPut);  // evaluate expression
  if (new_cell.getObject() == nullptr) {
    throw std::invalid_argument("new cell is null");
  }

  new_cell.setFormula(root);  // set formula to cell

  std::shared_ptr<Cell> cell =
      std::make_shared<Cell>(new_cell);  // make cell and pointer to it

  return cell;
}

void TABLE::eraseCell(const std::string& position) {
  POS pos = get_position(position);
  // delete from all connections

  m_graph.removeChildrensFromParent(this->m_table[pos.row - 1][pos.column - 1]);
  m_graph.removeParentsFromChildren(this->m_table[pos.row - 1][pos.column - 1]);

  // delete from table
  std::shared_ptr<Cell> new_cell(new Cell(EMPTY()));
  this->m_table[pos.row - 1][pos.column - 1] = new_cell;
}

void TABLE::eraseCell(const int& x, const int& y) {
  if (x > this->m_columns || y > this->m_rows || x <= 0 || y <= 0) {
    throw std::out_of_range("erase error");
  }

  // delete from all connections
  m_graph.removeChildrensFromParent(this->m_table[y - 1][x - 1]);
  m_graph.removeParentsFromChildren(this->m_table[y - 1][x - 1]);

  // delete from table
  std::shared_ptr<Cell> new_cell(new Cell(EMPTY()));
  this->m_table[y - 1][x - 1] = new_cell;
}

// change childrens of cell
void TABLE::changeChildrens(std::shared_ptr<Cell> cell) {
  std::vector<std::shared_ptr<Cell>> toPut;
  for (auto& child : m_graph.getChildrens(cell)) {
    Cell new_cell = evaluate(child->getFormula(), toPut);
    child.get()->changeObject(new_cell.getObject()->clone());
    changeChildrens(child);
  }
}

// add new edge to graph
bool TABLE::putChild(std::shared_ptr<Cell> new_cell,
                     std::vector<std::shared_ptr<Cell>>& toPut) {
  for (std::shared_ptr<Cell> master : toPut) {
    bool putted = m_graph.addEdge(master, new_cell);
    if (!putted) return false;
  }
  toPut.clear();
  return true;
}

// show formula of cell
void TABLE::showFormula(const std::string& position) const {
  POS pos = get_position(position);
  std::cout << "formula: "
            << this->m_table[pos.row - 1][pos.column - 1]->toStringFormula()
            << std::endl;
}

// export to json file
nlohmann::json TABLE::toJSON() const {
  nlohmann::json json;
  json += {{"rows", m_rows}, {"columns", m_columns}};
  for (int i = 0; i < m_rows; i++) {
    for (int j = 0; j < m_columns; j++) {
      // check if cell is empty
      if (m_table[i][j]->getObject()->toString() == "")
        continue;
      else {
        // save the position of the cells
        json += {{"position", get_cell_id(j) + std::to_string(i + 1)},
                 {"Cell", m_table[i][j]->toJSON()}};
      }
    }
  }
  return json;
}

// import from json file
void TABLE::importFromJSON(const nlohmann::json& j) {
  bool first = true;
  for (auto& element : j) {
    if (first) {
      int rows = element.at("rows");
      int columns = element.at("columns");
      setSize(rows, columns);
      first = false;
      continue;
    }
    std::string position = element.at("position");
    std::string formula = element.at("Cell").at("formula");
    setValue(position, formula);
  }
}

bool TABLE::isEmpty() const {
  if (m_rows == 0 && m_columns == 0) return true;

  for (int i = 0; i < m_rows; i++) {
    for (int j = 0; j < m_columns; j++) {
      if (m_table[i][j]->getObject()->toString() != "") return false;
    }
  }
  return false;
}

std::string TABLE::getValue(const std::string& position) const {
  POS pos = get_position(position);
  return this->m_table[pos.row - 1][pos.column - 1].get()->toStringFormula();
}
