#include <cmath>

class Point
{
private:
    // use a factory method
    Point(double x, double y)
        : x_(x)
        , y_(y)
    {}

    class PointFactory
    {
    private:
        PointFactory() = default;

    public:
        static Point NewCartesian(double x, double y) { return {x, y}; }
        [[maybe_unused]] static Point NewPolar(double r, double theta) { return {r * cos(theta), r * sin(theta)}; }
    };

    double x_, y_;

public:
    static PointFactory Factory;
};

int main()
{
    // if factory is public, then
    // auto p = Point::PointFactory::NewCartesian(3, 4);

    // at any rate, use this
    auto pp = Point::Factory.NewCartesian(2, 3);
    (void)pp;

    return 0;
}