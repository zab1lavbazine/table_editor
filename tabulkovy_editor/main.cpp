#include <iostream>
#include <string>
#include <vector>

#include "cell.h"
#include "number.h"
#include "table.h"
#include "text.h"

#define SUM "SUM"
#define DIV "DIV"
#define MUL "MUL"
#define SUB "SUB"

int main(void) {
  Object* o1 = new Number(12);
  Object* o2 = new Number(103.4);

  try {
    Object* o3 = o1->collide(*o2, SUB);
    std::cout << *o3 << std::endl;
    delete o3;
  } catch (std::invalid_argument& e) {
    std::cout << e.what() << std::endl;
  }

  delete o1;
  delete o2;

  return 0;
}