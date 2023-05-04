#include <iostream>
#include <string>

class Object {
 public:
  virtual ~Object() {}
  Object() {}
  friend std::ostream& operator<<(std::ostream& os, const Object& obj) {
    return obj.print(os);
  }
  virtual std::ostream& print(std::ostream& os) const = 0;
  virtual Object* clone() const = 0;
};