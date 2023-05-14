#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../include/number.h"
#include "../include/table.h"
#include "../include/text.h"

#define SUM "SUM"
#define DIV "DIV"
#define MUL "MUL"
#define SUB "SUB"

int main(void) {
  Table table;
  table.setSize(2, 10);
  // table.setValue(1, 1, Number(1));

  table.setValue(10, 10, Number(100));
  table.setValue(9, 12, Number(144));
  table.setValue(100, 17, Number(169));
  // input text
  table.setValue(1, 1, Text("ahoj"));
  table.setValue(1, 2, Text("svete"));
  table.setValue(1, 3, Text("jak"));

  std::string line = "A1 + B1 + C1 + D1";

  Cell* new_cell = table.HandleOperands(line);
  std::cout << *new_cell << std::endl;

  delete new_cell;

  std::cout << table << std::endl;

  return 0;
}