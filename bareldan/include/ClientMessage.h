#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

#pragma once
#include "../libs/json.hpp"
#include "CommandType.h"
#include "Table.h"

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

  // operator for output
  friend void operator<<(std::ostream& out, const ClientMessage& c) {
    c.printAllCommands(out);
  }
  void printAllCommands(std::ostream& out) const;

  // parser for json
  int parseToJSON(const std::string& fileName) const;

  // all commands for table
  void setValue(const std::string& formula);
  void showCell(const std::string& formula);
  void deleteCell(const std::string& formula);

  // all fucntions for saving and loading
  /// @brief function for saving table into json file
  int fromJSON(const std::string& fileName);
  void importFromFile(std::string& filename);
  void saveIntoFile(bool& saved, bool& importFromFile,
                    std::string& filename) const;
  int fromJsonToTable(const nlohmann::json& j);
  void checkIfSaved(bool& saved, bool& importedFromFile,
                    std::string& filename) const;
  void automaticSave(bool& saved) const;
  //------------------------
 private:
  static const std::vector<COMMAND> commands;
  TABLE m_table;
};
