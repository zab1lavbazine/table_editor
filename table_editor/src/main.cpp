

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../include/number.h"
#include "../include/table.h"
#include "../include/text.h"
#include "../libs/tabulate.hpp"

int main(void) {
  Table table;
  table.setSize(2, 10);
  // table.setValue(1, 1, Number(1));

  table.setValue(10, 12, Number(100));

  // input text
  // table.setValue(1, 1, Text("ahoj"));
  // table.setValue(1, 2, Text("svete"));
  // table.setValue(1, 3, Text("jak"));
  table.setValue(1, 4, Number(12));
  // std::string line = "A1 + B1+C1+J10";

  std::string line2 = "(1 + D1)/D1 +  \"hello\" + (D1 + 3 * D1)";
  // Cell* new_cell = table.HandleOperands(line);
  // std::cout << *new_cell << std::endl;

  // std::string position = "D3";
  // std::string formula = line2;
  // table.setCell(table.HandleOperands(line2), position, formula);
  Cell* new_cell2 = table.HandleOperands(line2);
  std::cout << *new_cell2 << std::endl;

  delete new_cell2;
  // delete new_cell;

  std::cout << table << std::endl;

  return 0;
}