#include <cmath>

class Point {
private:
  // use a factory method
  Point(double x, double y) : x_(x), y_(y) {}
  double x_;
  double y_;

public:
  friend class PointFactory;
};

class PointFactory {
public:
  static Point NewCartesian(double x, double y) { return Point{x, y}; }

  static Point NewPolar(double r, double theta) {
    return Point{r * cos(theta), r * sin(theta)};
  }
};

int main() {
  auto pointCart = PointFactory::NewCartesian(1.0, 2.0);
  auto pointPolar = PointFactory::NewPolar(1.0, 20);

  (void)pointCart;
  (void)pointPolar;

  return 0;
}
