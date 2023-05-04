#include <iostream>
#include <string>

#include "object.h"

class Text : public Object {
 public:
  Text();
  Text(const std::string& text);
  ~Text();
  std::string getText() const;
  void setText(const std::string& text);
  std::ostream& print(std::ostream& os) const override;
  Object* clone() const override;

 private:
  std::string m_text;
};