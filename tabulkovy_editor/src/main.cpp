#include <iostream>
#include <string>
#include <vector>

#include "include/number.h"
#include "include/table.h"
#include "include/text.h"

#define SUM "SUM"
#define DIV "DIV"
#define MUL "MUL"
#define SUB "SUB"

int main(void) {
  Table table;

  table.setValue(10, 10, Cell(Number(10)));

  std::cout << table << std::endl;
  table.setValue(3, 5, Cell(Text("ahoj")));
  std::cout << "table-----------------------------  " << std::endl;
  std::cout << table << std::endl;
  table.setValue(11, 11, Cell(Text("ahoj")));
  std::cout << table << std::endl;
  return 0;
}