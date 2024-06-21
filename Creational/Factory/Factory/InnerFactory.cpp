#include <cmath>
#include <iostream>

class Point {
private:
  // use a factory method
  Point(double x, double y) : x_(x), y_(y) {}

  class PointFactory {
  private:
    PointFactory() = default;

  public:
    static Point NewCartesian(double x, double y) { return {x, y}; }
    [[maybe_unused]] static Point NewPolar(double r, double theta) {
      return {r * cos(theta), r * sin(theta)};
    }
  };

  double x_;
  double y_;

public:
  static PointFactory Factory;

  friend std::ostream &operator<<(std::ostream &os, const Point &obj) {
    return os << "x: " << obj.x_ << " y: " << obj.y_;
  }
};

int main() {
  // if factory is public, then
  // auto p = Point::PointFactory::NewCartesian(3, 4);

  // at any rate, use this
  const auto pp = Point::Factory.NewCartesian(2, 3);
  std::cout << pp << '\n';

  return 0;
}