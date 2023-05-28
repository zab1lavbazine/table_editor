#include <iostream>
#include <vector>

#pragma once
#include "table.h"

class ClientMessage {
 public:
  ClientMessage() = default;
  ~ClientMessage() = default;
  std::string getCommand() const;
};