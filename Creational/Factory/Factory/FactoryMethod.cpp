#include <cmath>
#include <iostream>

class Point {
  // use a factory method : private constructor
private:
  Point(double x, double y) : x_{x}, y_{y} {}
  double x_;
  double y_;

public:
  ~Point() = default;

  // static factory method
  static Point NewCartesian(double x, double y) { return {x, y}; }
  static Point NewPolar(double r, double theta) {
    return {r * cos(theta), r * sin(theta)};
  }

  friend std::ostream &operator<<(std::ostream &os, const Point &obj) {
    return os << "x: " << obj.x_ << " y: " << obj.y_;
  }
};

int main() {
  const auto pPolar = Point::NewPolar(5, M_PI_4);
  const auto pCart = Point::NewCartesian(5, M_PI_4);
  std::cout << pPolar << '\n';
  std::cout << pCart << '\n';

  return 0;
}