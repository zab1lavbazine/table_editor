

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../include/client_message.h"
#include "../include/number.h"
#include "../include/table.h"
#include "../include/text.h"
#include "../libs/json.hpp"
#include "../libs/tabulate.hpp"

int main(void) {
  // ClientMessage message;
  // message.getCommand();
  TABLE table;
  table.setSize(5, 5);

  table.setValue("A1", "sin (1 + 2)");
  table.setValue("A2", "A1 + 1");
  table.setValue("A3", "A2 + 1");
  table.setValue("A4", "A2 + \"hello\" + sin(32 / 5)");
  table.setValue("A5", "A4 + \"another + me\"");
  table.setValue("B1", "A1 + 1");
  table.setValue("B2", "B1 + 1");
  table.setValue("B3", "B2 + 1");

  // Verify table size after setting values
  assert(table.getRows() == 5);
  assert(table.getColumns() == 5);

  // Verify the values of specific cells
  std::cout << table.getValue("A1") << std::endl;
  assert(table.getValue("A1") == "sin(1 + 2)");
  assert(table.getValue("A2") == "(A1 + 1)");
  assert(table.getValue("A3") == "(A2 + 1)");
  assert(table.getValue("B1") == "(A1 + 1)");
  assert(table.getValue("B2") == "(B1 + 1)");
  assert(table.getValue("B3") == "(B2 + 1)");

  std::cout << table << std::endl;
  return 0;
}