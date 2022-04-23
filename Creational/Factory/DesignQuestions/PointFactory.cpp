#include <vector>
#include <cstdint>
#include <stdexcept>
#include <math.h>
#include <iostream>

// Design Pattern Question:
// Please fix the design below

using namespace std;

enum class PointType : uint8_t
{
    cartesian,
    polar
};

class Point
{
    public:
        Point(const double x, const double y, const PointType& pointType)
        {

            switch (pointType) {
                case PointType::cartesian: 
                    x_ = x;
                    y_ = y;
                    break;
                case PointType::polar:
                    // x : radius 
                    // y : angle_rad
                    x_ = x * cos(y);
                    y_ = x * sin(y);
                    break;
                default:
                    throw std::runtime_error("The provided point type is not valid");

            }
        }

        friend ostream& operator<<(ostream& os, const Point& point) {
            os << point.x_ << " " << point.y_ << '\n';
            return os;
        }

        ~Point() = default;

    private:
        double x_;
        double y_;
};


int main() {

    Point cartesianPoint(0.0, 1.0, PointType::cartesian);
    Point polarPoint(0.0, 1.0, PointType::polar);

    cout << cartesianPoint << '\n';
    cout << polarPoint << '\n';

    return 0;
}
