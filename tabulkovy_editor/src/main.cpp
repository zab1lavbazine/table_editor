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
  // input text
  table.setValue(1, 1, Text("ahoj"));
  table.setValue(1, 2, Text("svete"));
  table.setValue(1, 3, Text("jak"));
  std::cout << table << std::endl;
  std::string line = "B1 + L9 + A1";
  Cell* cell = table.HandleOperands(line);
  table.setValue(1, 4, *cell);
  std::cout << table << std::endl;
  std::cout << table.getCell("D1")->toString() << std::endl;
  delete cell;

  line = "A2 + F5 + B1";
  Cell* cell1 = table.HandleOperands(line);

  table.setValue(2, 1, *cell1);
  delete cell1;
  std::cout << table << std::endl;

  return 0;
}