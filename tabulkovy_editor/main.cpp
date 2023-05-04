#include <iostream>
#include <string>
#include <vector>

#include "number.h"
#include "text.h"
#ifdef "object.h"
#define "object.h"

int main(void) {
  Object* obj2 = new Number(5);
  std::cout << *obj2 << std::endl;
  delete obj2;
  Object* obj = new Text("ahoj");
  std::cout << *obj << std::endl;
  delete obj;
  return 0;
}

#endif  // "object.h"