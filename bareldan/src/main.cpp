
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

  table.setValue("A1", "5");
  table.setValue("A2", "10 + A1");

  table.setValue("A3", "A2 + A1");
  table.ShowCell("A3");
  table.setValue("A1", "\"Hello\"");

  // table.setValue("A1", "10");
  // TABLE table2;
  // table2.importFromJSON(file);
  // std::cout << table2 << std::endl;

  std::cout << table << std::endl;
  return 0;
}