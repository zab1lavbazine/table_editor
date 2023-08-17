
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../include/ClientMessage.h"
#include "../include/Number.h"
#include "../include/Table.h"
#include "../include/Text.h"
#include "../libs/json.hpp"
#include "../libs/tabulate.hpp"

int main(void) {
  ClientMessage message;
  message.getCommand();
  return 0;
}
