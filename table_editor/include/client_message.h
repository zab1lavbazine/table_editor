#include <iostream>
#include <regex>
#include <vector>

#pragma once
#include "COMMAND_TYPE.h"
#include "table.h"

struct TODO {
  COMMAND_TYPE command;
  std::string formula;
};

struct COMMAND {
  std::regex pattern;
  COMMAND_TYPE command;

  void print(std::ostream& out) const;
  std::string CommandToString(const COMMAND_TYPE& command) const;
};

class ClientMessage {
 public:
  ClientMessage() = default;
  ~ClientMessage() = default;
  void getCommand();
  TODO checkWithRegex(const std::string& comm);

  // commands for table
  void setTableSize(const std::string& formula);
  void setCellValue(const std::string& position, const std::string& formula);
  friend void operator<<(std::ostream& out, const ClientMessage& c) {
    c.print(out);
  }
  void print(std::ostream& out) const;

 private:
  static const std::vector<COMMAND> commands;
  Table table;
};
