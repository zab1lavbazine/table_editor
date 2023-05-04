#include <iostream>
#include <string>

#include "object.h"

class Number : public Object {
 public:
  Number();
  Number(const int& number);
  ~Number();
  int getNumber() const;
  void setNumber(const int& number);
  std::ostream& print(std::ostream& os) const override;
  Object* clone() const override;

 private:
  int m_number;
};