

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
  // TABLE table;
  // table.setSize(10, 10);
  // table.setValue("A1", "1 + 2");
  // table.setValue("A2", "A1 + 3");
  // table.setValue("A3", "A2 + 4 + \"hello my friend\"");
  // table.setValue("A4", "(-(cos(0)))");
  ClientMessage message;
  message.getCommand();
  // std::cout << table << std::endl;

  return 0;
}