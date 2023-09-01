
#include "../include/ClientMessage.h"

// output for all commands for info command
std::string COMMAND::CommandToString(const COMMAND_TYPE& command) const {
  switch (command) {
    case COMMAND_TYPE::EXIT:
      return "exit";
    case COMMAND_TYPE::SH_TAB:
      return "show table";
    case COMMAND_TYPE::SH_CELL:
      return "show cell \"...\" | sh ce \"...\"";
    case COMMAND_TYPE::SET:
      return "set value into cell";
    case COMMAND_TYPE::SETSIZE:
      return "set table size (int) (int)";
    case COMMAND_TYPE::DEL:
      return "delete (cell) \"...\"";
    case COMMAND_TYPE::INFO:
      return "get info about all commands";
    case COMMAND_TYPE::SAVE:
      return "save current table into file";
    case COMMAND_TYPE::IMPORT:
      return "import table from file";
    case COMMAND_TYPE::EMP:
    case COMMAND_TYPE::UNKNOWN:
      return "unknown command";
  }
  return "";
}

// print function for command
void COMMAND::print(std::ostream& out) const {
  out << "command: " << CommandToString(command) << std::endl;
}

// get last substring from string for some operations like show cell / delete
// cell
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

// remove spaces from string for the correct position
void removeSpaces(std::string& str) {
  bool check = false;
  for (size_t i = 0; i < str.length(); i++) {
    // do not remove spaces in quotes in text
    if (str[i] == '"') check = true;
    if (str[i] == ' ' && !check) {
      str.erase(i, 1);
      i--;
    }
  }
}

// checking if string is number
bool isNumber(const std::string& s) {
  return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

// checking if position is valid or not
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

// check if table is saved after all operations after exit command
void ClientMessage::checkIfSaved(bool& saved, bool& importFromFile,
                                 std::string& filename) const {
  if (!saved) {
    std::cout << "Do you want to save changes? (y/n)" << std::endl;
    std::string answer;
    std::cin >> answer;
    if (answer == "y") {
      saveIntoFile(saved, importFromFile, filename);
    }
  }
}

// save function for table
void ClientMessage::saveIntoFile(bool& saved, bool& importFromFile,
                                 std::string& filename) const {
  if (importFromFile) {
    std::string answer;
    while (true) {
      std::cout << "Save in file \"" << filename << "\"? (y/n)" << std::endl;
      std::cin >> answer;
      std::transform(answer.begin(), answer.end(), answer.begin(),
                     [](unsigned char c) { return std::tolower(c); });
      if (answer == "y" || answer == "n") break;
    }
    if (answer == "n") {
      std::cout << "Enter file name: ";
      std::cin >> filename;
      std::string file = filename + ".json";
    }
  }

  // std::cout << "Enter file name: ";

  // std::string fileName;
  // std::cin >> fileName;
  // std::string file = fileName + ".json";

  int check = parseToJSON(filename);
  if (check == 0) {
    saved = true;
  } else {
    std::cout << "error: save" << std::endl;
  }
}

void ClientMessage::importFromFile(std::string& filename) {
  std::cout << "Enter file name: ";
  std::cin >> filename;
  int check = fromJSON(filename);
  if (check == 0) std::cout << "file imported" << std::endl;
}

void ClientMessage::getCommand() {
  bool saved = true;
  bool importedFromFile = false;
  std::string filename;
  std::cout << "-----Welcome to table editor-----" << std::endl;
  std::cout << "print \"info\" for commands" << std::endl;
  while (true) {
    std::string command;
    std::getline(std::cin, command);

    if (std::cin.eof()) {
      automaticSave(saved);
      return;
    }

    TODO todo = checkWithRegex(command);

    // switch for all commands

    switch (todo.command) {
      case COMMAND_TYPE::INFO:
        printAllCommands(std::cout);
        break;
      case COMMAND_TYPE::SAVE:
        saveIntoFile(saved, importedFromFile, filename);
        break;
      case COMMAND_TYPE::IMPORT:
        importFromFile(filename);
        importedFromFile = true;
        break;
      case COMMAND_TYPE::SETSIZE:
        setTableSize(todo.formula);
        saved = false;
        break;
      case COMMAND_TYPE::SET:
        setValue(todo.formula);
        saved = false;
        break;
      case COMMAND_TYPE::SH_TAB:
        std::cout << m_table << std::endl;
        break;
      case COMMAND_TYPE::SH_CELL:
        showCell(todo.formula);
        break;
      case COMMAND_TYPE::EXIT:
        checkIfSaved(saved, importedFromFile, filename);
        return;
      case COMMAND_TYPE::EMP:
        std::cout << "empty command" << std::endl;
        break;
      case COMMAND_TYPE::DEL:
        deleteCell(todo.formula);
        break;
      case COMMAND_TYPE::UNKNOWN:
        break;
    }
  }
}

// deleting cell from table
void ClientMessage::deleteCell(const std::string& formula) {
  std::string position = getLastSubstring(formula);
  if (checkIfPosition(position)) {
    try {
      m_table.eraseCell(position);
    } catch (const std::exception& e) {
      std::cout << "error: delete table" << std::endl;
    }
  } else {
    std::cout << "wrong position" << std::endl;
  }
}

// show cell from table
void ClientMessage::showCell(const std::string& formula) {
  std::string position = getLastSubstring(formula);

  if (checkIfPosition(position)) {
    try {
      m_table.ShowCell(position);
    } catch (const std::exception& e) {
      std::cout << "error: show cell" << std::endl;
    }
  } else {
    std::cout << "wrong position" << std::endl;
  }
}

void ClientMessage::setValue(const std::string& todo) {
  std::string position = todo.substr(0, todo.find("="));
  std::string formula = todo.substr(todo.find("=") + 1, todo.length());

  // remove spaces from string for correct position and formula
  removeSpaces(position);

  if (checkIfPosition(position)) {  // check if position is valid

    try {
      m_table.setValue(position, formula);
    } catch (const std::exception& e) {
      std::cout << "error: " << e.what() << std::endl;
    }
  } else {
    std::cout << "wrong position" << std::endl;
  }
}

// check if command is valid and is known
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

// regex for all commands that program can do
const std::vector<COMMAND> ClientMessage::commands = {
    {std::regex(R"(^\s*exit\s*$)"), COMMAND_TYPE::EXIT, "exit"},
    {std::regex(R"(^\s*(?:show\s+table|sh\s+tb)\s*$)"), COMMAND_TYPE::SH_TAB,
     "show table | sh tb"},
    {std::regex(R"(^\s*(?:sh\s+ce|show\s+cell)\s+([A-Z]+[0-9]+)\s*$)"),
     COMMAND_TYPE::SH_CELL, "show cell A1 | sh ce A1"},
    {std::regex(R"(^([A-Z][0-9]+)\s*=\s*(.*))"), COMMAND_TYPE::SET, "A1 = 1+2"},
    {std::regex(R"(^set\s+size\s+(\d+)\s+(\d+)\s*$)"), COMMAND_TYPE::SETSIZE,
     "set size 10 10"},
    {std::regex(R"(^(?:delete|del)\s+([A-Z]+[0-9]+)\s*$)"), COMMAND_TYPE::DEL,
     "delete A1 | del A1"},
    {std::regex(R"(^\s*info\s*$)"), COMMAND_TYPE::INFO, "info"},
    {std::regex(R"(^\s*save\s*$)"), COMMAND_TYPE::SAVE, "save"},
    {std::regex(R"(^\s*import\s*$)"), COMMAND_TYPE::IMPORT, "import"},
    {std::regex(R"(^\s*\S+\s*$)"), COMMAND_TYPE::EMP, "wrong command"}};

// set table size from command
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
        m_table.setSize(x, y);
        break;
      }
    }
  }
  m_table.setSize(x, y);
}

// print function for all commands
void ClientMessage::printAllCommands(std::ostream& out) const {
  // load in ostream all commands
  out << "Commands: " << std::endl;
  tabulate::Table table;

  for (size_t i = 0; i < commands.size(); i++) {
    table.add_row({commands[i].CommandToString(commands[i].command),
                   commands[i].example});
  }
  std::cout << table << std::endl;
}

// parse table to json
int ClientMessage::parseToJSON(const std::string& fileName) const {
  std::string file = fileName + ".json";
  std::fstream out{file, std::ios::out | out.binary};

  // check for file opening
  if (!out.is_open()) {
    std::cout << "error opening file" << std::endl;
    return 1;
  }

  nlohmann::json j = m_table.toJSON();
  out << j.dump(4);
  out.close();
  std::cout << "file saved" << std::endl;

  return 0;
}

int ClientMessage::fromJsonToTable(const nlohmann::json& j) {
  if (m_table.isEmpty())
    m_table.importFromJSON(j);
  else {
    // if table is not empty, create new table and import from json
    TABLE new_table;
    new_table.importFromJSON(j);
    m_table = new_table;
  }
  return 0;
}

// import table from json
int ClientMessage::fromJSON(const std::string& fileName) {
  std::string file = fileName;

  // add .json to file if it is not there
  if (file.find(".json") == std::string::npos) {
    file += ".json";
  }
  // remove spaces from string for correct file name
  removeSpaces(file);

  std::fstream in{file, std::ios::in | in.binary};
  // check for file opening
  if (!in.is_open()) {
    std::cout << "error opening file" << std::endl;
    return 1;
  }

  nlohmann::json j;

  try {
    j = nlohmann::json::parse(in);
  } catch (const std::exception& e) {
    // bad file format, return error
    std::cout << "error: import" << std::endl;
    in.close();
    return 1;
  }
  // closing file
  in.close();
  // check if closed correctly
  if (!in.good()) {
    std::cout << "error: closing file" << std::endl;
    return 1;
  }

  int inTable = fromJsonToTable(j);

  return inTable;
}

void ClientMessage::automaticSave(bool& saved) const {
  if (!saved) {
    std::string fileName = "untitled";
    std::string file = fileName + ".json";
    int check = parseToJSON(fileName);
    if (check == 0) {
      saved = true;
    } else {
      std::cout << "error: save" << std::endl;
    }
  }
}