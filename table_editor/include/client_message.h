#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

#pragma once
#include "../libs/json.hpp"
#include "COMMAND_TYPE.h"
#include "table.h"

// struct for TODO
struct TODO {
  COMMAND_TYPE command;
  std::string formula;
};

// struct for all commands
struct COMMAND {
  std::regex pattern;
  COMMAND_TYPE command;
  std::string example;

  void print(std::ostream& out) const;
  std::string CommandToString(const COMMAND_TYPE& command) const;
};

class ClientMessage {
 public:
  ClientMessage() = default;
  ~ClientMessage() = default;
  void getCommand();
  // checking for match commands
  TODO checkWithRegex(const std::string& comm);

  // commands for table
  // set size
  void setTableSize(const std::string& formula);
  // set value
  void setCellValue(const std::string& position, const std::string& formula);

  // operator for output
  friend void operator<<(std::ostream& out, const ClientMessage& c) {
    c.print(out);
  }
  void print(std::ostream& out) const;

  int parseToJSON(const std::string& fileName) const;

  void saveIntoFile(bool& saved) const;

 private:
  static const std::vector<COMMAND> commands;
  TABLE m_table;
};
