// Objects in a program should be replaceable with instances of their subtypes
// w/o altering the correctness of the program

#include <iostream>

// Liskov substitution principle

class Rectangle
{
protected:
    int width_;
    int height_;

public:
    Rectangle(const int width, const int height)
        : width_{width}
        , height_{height}
    {}

    virtual ~Rectangle() = default;

    [[nodiscard]] int get_width() const { return width_; }
    [[nodiscard]] int get_height() const { return height_; }

    virtual void set_width(const int width) { this->width_ = width; }
    virtual void set_height(const int height) { this->height_ = height; }

    [[nodiscard]] int area() const { return width_ * height_; }
};

class Square : public Rectangle
{
public:
    explicit Square(int size)
        : Rectangle(size, size)
    {}
    void set_width(const int width) override { width_ = height_ = width; }
    void set_height(const int height) override { height_ = width_ = height; }
};

void process(Rectangle& r)
{
    int w = r.get_width();
    r.set_height(10);

    std::cout << "expected area = " << (w * 10) << ", got " << r.area() << std::endl;
}

int main()
{
    Rectangle r{5, 5};
    process(r);

    Square s{5};
    process(s);

    getchar();
    return 0;
}