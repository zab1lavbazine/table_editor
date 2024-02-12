#include <iostream>
#include <memory>
#include <string>

#pragma once

/// @brief Node for tree in formula class
struct Node {
  std::string value;
  std::shared_ptr<Node> left;
  std::shared_ptr<Node> right;

  Node(const std::string& value)
      : value(value), left(nullptr), right(nullptr) {}

  // print function for node
  friend std::ostream& operator<<(std::ostream& os, const Node& node) {
    os << node.value;
    return os;
  }
  std::ostream& print(std::ostream& os) const {
    os << this->value;
    return os;
  }
};