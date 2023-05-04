#include <iostream>
#include <string>

class Cell {
 public:
  Cell();
  template <typename T>
  Cell(const T& object);
  Cell(const Cell& cell);
  Cell& operator=(const Cell& cell);
  ~Cell();
  Cell(Object* object);
  Object* getObject() const;
  void setObject(Object* object);
  std::ostream& print(std::ostream& os) const;
  friend std::ostream& operator<<(std::ostream& os, const Cell& cell) {
    return cell.print(os);
  }

 private:
  Object* m_object;
};