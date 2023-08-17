#include <stdbool.h>

#include <iostream>
#include <string>

#pragma once

#include "Empty.h"
#include "Number.h"
#include "Text.h"

class Visitor {
 public:
  // fuctions for addition
  static Object *addition(const Number &number, const Number &number2);
  static Object *addition(const Number &number, const Text &text, bool order);
  static Object *addition(const Text &text, const Text &text2);

  // functions for subtraction
  static Object *subtraction(const Number &number, const Number &number2);
  // functions for multiplication
  static Object *multiplication(const Number &number, const Number &number2);

  // functions for division

  static Object *division(const Number &number, const Number &number2,
                          bool order);

  static Object *sinus(const Number &number);
  static Object *cosinus(const Number &number);
};