#include "operand_handler.h"

#include <iostream>

int MessHandler::getPrecedence(char op) {
  if (op == '+' || op == '-') {
    return 1;
  } else if (op == '*' || op == '/') {
    return 2;
  } else {
    return 0;
  }
}

std::string MessHandler::infixToPostfix(const std::string& infix) {
  std::string postfix;
  std::stack<char> operators;
  bool check_letter = false;
  bool check_number = false;

  for (size_t i = 0; i < infix.length(); i++) {
    char ch = infix[i];
    // take the letter column
    if (ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != ' ' &&
        ch != '(' && ch != ')' && !isdigit(ch) && check_number == false) {
      postfix += ch;
      check_letter = true;
    } else if (check_letter == true && isdigit(ch)) {  // take the number of row
      postfix += ch;
      check_number = true;
    } else if ((ch == '+' || ch == '-' || ch == '*' || ch == '/') &&
               check_number == true &&
               check_letter == true) {  // take the operator
      check_letter = check_number = false;
      while (!operators.empty() && operators.top() != '(' &&
             getPrecedence(ch) <= getPrecedence(operators.top())) {
        postfix += operators.top();
        operators.pop();
      }
      operators.push(ch);
    } else if (ch == '(') {
      operators.push(ch);
    } else if (ch == ')') {
      while (!operators.empty() && operators.top() != '(') {
        postfix += operators.top();
        operators.pop();
      }
      operators.pop();
    }
  }
  while (!operators.empty()) {
    postfix += operators.top();
    std::cout << postfix << std::endl;
    operators.pop();
  }

  std::cout << "postfix: " << postfix << std::endl;

  return postfix;
}