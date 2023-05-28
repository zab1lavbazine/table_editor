

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../include/client_message.h"
#include "../include/number.h"
#include "../include/table.h"
#include "../include/text.h"
#include "../libs/tabulate.hpp"

int main(void) {
  Table table;
  // ClientMessage message;
  // message.getCommand();
  table.setSize(10, 10);

  table.setValue("A1", " A2 + 23 ");
  // table.ShowCell("A1");
  table.setValue("A2", "23 + \"hello my name is\"");
  table.setValue("A3", "23 / 34 + A2");
  table.ShowCell("A3");
  table.setValue("A3", "123 + 23 / 67");
  table.ShowCell("A3");
  table.setValue("A2", "123");
  table.showFormula("A3");
  // try {
  //   table.setValue("A3", "A1");
  // } catch (const std::exception& e) {
  //   std::cout << "error" << std::endl;
  // }
  // table.setValue("A2", "10");
  // table.setValue("A3", "1000");
  // table.setValueFormula("A1", table.HandleOperands("A3 + L10 "));
  // input text
  // table.setValue(1, 1, Text("ahoj"));
  // table.setValue(1, 2, Text("svete"));
  // table.setValue(1, 3, Text("jak"));
  // table.setValue(1, 4, Number(12));
  // // std::string line = "A1 + B1+C1+J10";

  // std::string line2 = "1 + A1+ 2 + D1";
  // std::string line3 = "A1 + D3 + 3";
  // // Cell* new_cell = table.HandleOperands(line);
  // // std::cout << *new_cell << std::endl;

  // std::string position = "D3";

  // std::string formula = line2;
  // table.setValue(position, Number(1));
  // table.setValue("A1", Number(2));
  // table.setValueFormula(position, table.HandleOperands(formula));
  // table.setValueFormula("A4", table.HandleOperands(line3));
  // // std::cout << *new_cell2 << std::endl;

  // std::cout << "======================" << std::endl;
  // table.ShowCell("D1");
  // table.ShowCell("A1");
  // table.ShowCell("D3");
  // std::cout << "======================" << std::endl;
  // std::cout << table << std::endl;
  // table.changeValue("A1", new Text("ahoj"));
  // std::cout << "======================" << std::endl;
  // table.ShowCell("D3");
  // table.changeValue("D1", new Text("svete"));
  // table.setValue("A4", Number(2));
  // table.ShowCell("A4");

  std::cout << table << std::endl;

  return 0;
}