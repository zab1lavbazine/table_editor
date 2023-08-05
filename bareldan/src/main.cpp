
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
  ClientMessage message;
  message.getCommand();
  return 0;
}
