

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../include/number.h"
#include "../include/table.h"
#include "../include/text.h"
#include "../libs/tabulate.hpp"

int main(void) {
  Table table;
  table.setSize(10, 10);
  // table.setValue(1, 1, Number(1));

  table.setValue("A1", "100");
  // table.setValue("A1", "\"ahoj\"");
  table.setValue("A2", "A1 + 1");
  table.changeValue("A1", "2 + 1 ");
  table.changeValue("A2", "100 ");
  table.setValue("A3", "30000");
  // table.changeValue("A1", "2 + 1 + A2 ");
  table.printConnections(table.getCell("A2"));
  // table.changeValue("A2", "A1 + 1");
  table.printConnections(table.getCell("A1"));

  table.printConnections(table.getCell("A3"));
  // table.setValue("A2", "3+2");
  // table.printConnections(table.getCell("A2"));
  // table.printConnections(table.getCell("A1"));
  // table.changeValue("A1", new Text("ahoj"));
  // table.printConnections(table.getCell("A1"));
  // table.ShowCell("A3");

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