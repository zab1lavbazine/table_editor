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
  Cell cell1 = Cell(Text("ahoj"));
  Cell cell2 = Cell(Number(5));
  Cell cell3 = Cell(Number(10));
  Cell cell4(cell3 + cell2 - cell2 * cell3 / cell2);
  std::cout << cell4 << std::endl;
  return 0;
}