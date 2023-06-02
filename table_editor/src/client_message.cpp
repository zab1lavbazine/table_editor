
#include "../include/client_message.h"

#include <iostream>
#include <regex>
#include <sstream>

std::string COMMAND::CommandToString(const COMMAND_TYPE& command) const {
  switch (command) {
    case COMMAND_TYPE::EXIT:
      return "exit";
    case COMMAND_TYPE::SH_TAB:
      return "show table | sh tb";
    case COMMAND_TYPE::SH_CELL:
      return "show cell \"...\" | sh ce \"...\"";
    case COMMAND_TYPE::SET:
      return "set";
    case COMMAND_TYPE::SETSIZE:
      return "set size (int) (int)";
    case COMMAND_TYPE::DEL:
      return "delete (cell) \"...\"";
    case COMMAND_TYPE::INFO:
      return "info";
    case COMMAND_TYPE::EMP:
      return "empty";
    case COMMAND_TYPE::UNKNOWN:
      return "unknown";
  }
  return "";
}

void COMMAND::print(std::ostream& out) const {
  out << "command: " << CommandToString(command) << std::endl;
}

std::string getLastSubstring(const std::string& str) {
  size_t lastNonSpaceIndex = str.find_last_not_of(' ');

  if (lastNonSpaceIndex == std::string::npos) {
    return "";
  }

  size_t lastSpaceIndex = str.find_last_of(' ', lastNonSpaceIndex);

  if (lastSpaceIndex == std::string::npos) {
    return str.substr(0, lastNonSpaceIndex + 1);
  }

  return str.substr(lastSpaceIndex + 1, lastNonSpaceIndex - lastSpaceIndex);
}

void removeSpaces(std::string& str) {
  bool check = false;
  for (size_t i = 0; i < str.length(); i++) {
    if (str[i] == '"') check = true;
    if (str[i] == ' ' && !check) {
      str.erase(i, 1);
      i--;
    }
  }
}

bool isNumber(const std::string& s) {
  return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

bool checkIfPosition(const std::string& position) {
  if (position.length() < 2) return false;

  bool letter = false;
  bool number = false;
  for (size_t i = 0; i < position.length(); i++) {
    if (position[i] >= 'A' && position[i] <= 'Z' && !number) {
      letter = true;
    } else if (position[i] >= '0' && position[i] <= '9' && letter) {
      number = true;
    } else {
      return false;
    }
  }
  return true;
}

void checkIfSaved(bool saved) {
  if (!saved) {
    std::cout << "Do you want to save changes? (y/n)" << std::endl;
    std::string answer;
    std::cin >> answer;
    if (answer == "y") {
      // save
      std::cout << "saved" << std::endl;
    }
  }
}

void ClientMessage::getCommand() {
  std::string command = "";
  bool saved = false;
  std::cout << "-------Welcome to table editor------" << std::endl;
  while (std::getline(std::cin, command)) {
    TODO todo = checkWithRegex(command);

    if (todo.command == COMMAND_TYPE::INFO) {
      // cout all commands
      print(std::cout);
    } else if (todo.command ==
               COMMAND_TYPE::SETSIZE) {  // set size command for table
      setTableSize(todo.formula);
    } else if (todo.command ==
               COMMAND_TYPE::SET) {  // set value command for cell
      removeSpaces(todo.formula);
      std::string position = todo.formula.substr(0, todo.formula.find("="));
      std::string formula = todo.formula.substr(todo.formula.find("=") + 1);
      if (checkIfPosition(position)) {  // check if position is valid
        table.setValue(position, formula);
      } else {
        std::cout << "wrong position" << std::endl;
      }
    } else if (todo.command == COMMAND_TYPE::SH_TAB) {
      std::cout << table << std::endl;
    } else if (todo.command == COMMAND_TYPE::SH_CELL ||
               todo.command == COMMAND_TYPE::SH_CELL) {  // show cell command
      // take the third substring from command

      std::string position = getLastSubstring(todo.formula);

      if (checkIfPosition(position)) {  // check if position is valid
        try {                           // show cell
          table.ShowCell(position);
        } catch (const std::exception& e) {
          std::cout << "error: show cell" << std::endl;
        }
      } else {
        std::cout << "wrong position" << std::endl;
      }
    } else if (todo.command == COMMAND_TYPE::EXIT) {  // exit command
      checkIfSaved(saved);
      break;
    } else if (todo.command == COMMAND_TYPE::EMP) {  // empty command
      std::cout << "empty command" << std::endl;
    } else if (todo.command == COMMAND_TYPE::DEL) {  // delete command
      // take the last substring from command
      std::string position = getLastSubstring(todo.formula);
      if (checkIfPosition(position)) {
        try {
          table.eraseCell(position);
        } catch (const std::exception& e) {
          std::cout << "error: delete table" << std::endl;
        }
      } else {
        std::cout << "wrong position" << std::endl;
      }
    } else if (todo.command == COMMAND_TYPE::UNKNOWN) {  // unknown command
      std::cout << "I don't know this command" << std::endl;
    }
  }
  // check for EOF
  if (std::cin.eof()) {
    checkIfSaved(saved);
  }
}

TODO ClientMessage::checkWithRegex(const std::string& comm) {
  for (auto& command : commands) {
    std::smatch match;
    if (std::regex_match(comm, match, command.pattern)) {
      TODO todo;
      todo.command = command.command;
      todo.formula = comm;
      return todo;
    }
  }
  return {COMMAND_TYPE::UNKNOWN, ""};
}

const std::vector<COMMAND> ClientMessage::commands = {
    {std::regex(R"(^\s*exit\s*$)"), COMMAND_TYPE::EXIT},
    {std::regex(R"(^\s*(?:show\s+table|sh\s+tb)\s*$)"), COMMAND_TYPE::SH_TAB},
    {std::regex(R"(^\s*(?:sh\s+ce|show\s+cell)\s+([A-Z]+[0-9]+)\s*$)"),
     COMMAND_TYPE::SH_CELL},
    {std::regex(R"(^([A-Z][0-9]+)\s*=\s*(.*))"), COMMAND_TYPE::SET},
    {std::regex(R"(^set\s+size\s+(\d+)\s+(\d+)\s*$)"), COMMAND_TYPE::SETSIZE},
    {std::regex(R"(^(?:delete|del)\s+([A-Z]+[0-9]+)\s*$)"), COMMAND_TYPE::DEL},
    {std::regex(R"(^\s*info\s*$)"), COMMAND_TYPE::INFO},
    {std::regex(R"(^\s*\S+\s*$)"), COMMAND_TYPE::EMP}};

void ClientMessage::setTableSize(const std::string& formula) {
  std::stringstream ss(formula);
  std::string token;
  int x, y;
  while (ss >> token) {
    if (isNumber(token)) {
      x = std::stoi(token);
      ss >> token;
      if (isNumber(token)) {
        y = std::stoi(token);
        table.setSize(x, y);
        break;
      }
    }
  }
  table.setSize(x, y);
}

void ClientMessage::setCellValue(const std::string& position,
                                 const std::string& formula) {
  if (checkIfPosition(position)) {  // check if position is valid
    try {
      table.setValue(position, formula);
    } catch (const std::exception& e) {
      std::cout << "error: " << e.what() << std::endl;
    }
  } else {
    std::cout << "wrong position" << std::endl;
  }
}

void ClientMessage::print(std::ostream& out) const {
  // load in ostream all commands
  out << "Commands: " << std::endl;
  for (auto& command : commands) {
    command.print(out);
  }
}
