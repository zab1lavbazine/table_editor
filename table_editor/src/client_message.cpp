
#include "../include/client_message.h"

#include <iostream>

std::string ClientMessage::getCommand() const {
  std::string command = "";
  while (true) {
    std::getline(std::cin, command);
    std::cout << "Your command>" << command << "<" << std::endl;
    if (command == "exit") break;
  }
  std::cout << "command: >" << command << "<" << std::endl;
  return command;
}