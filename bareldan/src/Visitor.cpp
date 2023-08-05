

#include "../include/Visitor.h"

// help functions
bool checkInt(const double& number) {
  if (number == (int)number) return true;
  return false;
}

bool checkSinCos(const std::string& text) {
  if (text == "sin" || text == "cos") return true;
  return false;
}

// functions for addition
Object* Visitor::addition(const Number& number, const Number& number2) {
  double result = number.getNumber() + number2.getNumber();
  if (checkInt(result)) {
    return new Number((int)result);
  }
  return new Number(result);
}

Object* Visitor::addition(const Number& number, const Text& text, bool order) {
  bool isInt = checkInt(number.getNumber());
  std::string convertedNumber = isInt ? std::to_string((int)number.getNumber())
                                      : std::to_string(number.getNumber());
  std::string result = order ? text.getText() + convertedNumber
                             : convertedNumber + text.getText();
  return new Text(result);
}

Object* Visitor::addition(const Text& text, const Text& text2) {
  std::string result = text.getText() + text2.getText();
  return new Text(result);
}

// functions for subtraction

Object* Visitor::subtraction(const Number& number, const Number& number2) {
  double result = number.getNumber() - number2.getNumber();
  return new Number(result);
}





// functions for multiplication
Object* Visitor::multiplication(const Number& number, const Number& number2) {
  double result = number.getNumber() * number2.getNumber();
  return new Number(result);
}





// functions for division
Object* Visitor::division(const Number& number, const Number& number2,
                          bool order) {
  // check for division by zero
  if (order) {
    if (number2.getNumber() == 0) {
      throw std::invalid_argument("cant divide by zero");
    }
  } else {
    if (number.getNumber() == 0) {
      throw std::invalid_argument("cant divide by zero");
    }
  }

  double result = number.getNumber() / number2.getNumber();
  return new Number(result);
}





Object* Visitor::sinus(const Number& number) {
  double result = std::sin(number.getNumber());
  return new Number(result);
}

Object* Visitor::cosinus(const Number& number) {
  double result = std::cos(number.getNumber());
  return new Number(result);
}
