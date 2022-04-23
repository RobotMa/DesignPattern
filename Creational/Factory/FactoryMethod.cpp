#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

class Point
{
    Point(const double x, const double y)
        : x_{x}
        , y_{y}
    {}

public:
    double x_, y_;

    friend std::ostream& operator<<(std::ostream& os, const Point& obj)
    {
        return os << "x: " << obj.x_ << " y: " << obj.y_;
    }

    static Point NewCartesian(double x, double y) { return {x, y}; }
    static Point NewPolar(double r, double theta) { return {r * cos(theta), r * sin(theta)}; }
};

int main()
{
    auto p = Point::NewPolar(5, M_PI_4);
    std::cout << p << std::endl;

    getchar();
    return 0;
}