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
  bool check_string = false;
  int check_quotes = 0;

  for (size_t i = 0; i < infix.length(); i++) {
    char ch = infix[i];
    std::cout << "ch: " << ch << std::endl;

    // take the string from the input
    if ((ch == '\"' && check_quotes < 2) || check_string == true) {
      check_string = true;
      if (ch == '\"') check_quotes++;
      if (check_quotes == 2) {
        postfix += ch;
        postfix += ' ';
        check_string = false;
      } else
        postfix += ch;
    } else if (check_string == false) {
      // take the letter from the input
      if (ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != ' ' &&
          ch != '(' && ch != ')' && !isdigit(ch) && !check_number &&
          !check_letter) {
        postfix += ch;
        check_letter = true;
      } else if (isdigit(ch) || ch == '.') {  // take the number of row
        postfix += ch;
        check_number = true;
      } else if ((ch == '+' || ch == '-' || ch == '*' ||
                  ch == '/')) {  // take the operator
        postfix += ' ';
        std::cout << "ch operand ==========" << ch << std::endl;
        check_letter = check_number = false;
        while (!operators.empty() && operators.top() != '(' &&
               getPrecedence(ch) <= getPrecedence(operators.top())) {
          postfix += operators.top();
          postfix += ' ';
          operators.pop();
        }
        operators.push(ch);
      } else if (ch == '(') {
        operators.push(ch);
      } else if (ch == ')') {
        while (!operators.empty() && operators.top() != '(') {
          postfix += ' ';
          postfix += operators.top();
          operators.pop();
        }
        operators.pop();
      }
    }
  }

  while (!operators.empty()) {
    postfix += ' ';
    postfix += operators.top();
    operators.pop();
  }

  std::cout << "postfix result: =======>>>> " << postfix << std::endl;

  return postfix;
}

// std::string MessHandler::infixToPostfix(const std::string& infix) {
//   std::string postfix;
//   std::stack<char> operators;
//   bool check_letter = false;
//   bool check_number = false;
//   bool check_string = false;
//   int check_quotes = 0;

//   for (size_t i = 0; i < infix.length(); i++) {
//     char ch = infix[i];
//     std::cout << "ch: " << ch << std::endl;

//     // take the string from the input
//     if ((ch == '\"' && check_quotes < 2) || check_string == true) {
//       check_string = true;
//       if (ch == '\"') check_quotes++;
//       if (check_quotes == 2) {
//         postfix += ch;
//         postfix += ' ';
//         check_string = false;
//       } else
//         postfix += ch;
//     } else if (check_string == false) {
//       // take the letter from the input
//       if (ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != ' ' &&
//           ch != '(' && ch != ')' && !isdigit(ch) && check_number == false) {
//         postfix += ch;
//         check_letter = true;
//       } else if (isdigit(ch) || ch == '.') {  // take the number of row
//         postfix += ch;
//         check_number = true;
//       } else if ((ch == '+' || ch == '-' || ch == '*' ||
//                   ch == '/')) {  // take the operator
//         std::cout << "ch operand ==========" << ch << std::endl;
//         check_letter = check_number = false;
//         while (!operators.empty() && operators.top() != '(' &&
//                getPrecedence(ch) <= getPrecedence(operators.top())) {
//           postfix += operators.top();
//           operators.pop();
//         }
//         postfix += ' ';
//         operators.push(ch);
//       } else if (ch == '(') {
//         operators.push(ch);
//       } else if (ch == ')') {
//         while (!operators.empty() && operators.top() != '(') {
//           postfix += ' ';
//           postfix += operators.top();
//           operators.pop();
//         }
//         operators.pop();
//       }
//     }
//   }

//   while (!operators.empty()) {
//     postfix += ' ';
//     postfix += operators.top();
//     std::cout << postfix << std::endl;
//     operators.pop();
//   }

//   std::cout << "postfix result: =======>>>> " << postfix << std::endl;

//   return postfix;
// }