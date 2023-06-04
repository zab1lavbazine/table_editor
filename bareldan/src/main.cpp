
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
  // check sin and cos
  table.setValue("A2", "sin(A1)");
  table.setValue("A3", "cos(A1)");
  // check sum
  table.setValue("A4", "A1+A2");
  // check text
  table.setValue("A5", "\"test text\" + A1");
  // check empty

  std::cout << table << std::endl;
  return 0;
}