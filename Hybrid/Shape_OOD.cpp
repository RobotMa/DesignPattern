#include <memory>
#include <utility>
#include <iostream>
#include <vector>
#include <fstream>

// Draw Strategy
template <typename T>
class DrawStrategy
{
public:
    virtual ~DrawStrategy() = default;
    virtual void draw(const T& shape) const = 0;
};

// Base class
class Shape
{
public:
    virtual ~Shape() = default;

    virtual void draw() const = 0;
    // ... several other virtual functions
};

// Derived class
class Circle : public Shape
{
public:
    Circle(double rad, std::unique_ptr<DrawStrategy<Circle>>&& ds)
        : radius{ rad }
        // ... Remaining data members
        , drawer{ std::move(ds) }
    {}

    double getRadius() const {
        return radius;
    };
    // getCenter(), getRotation(), ...

    void draw() const override {
        drawer->draw(*this);
    };
    // ... several other virtual functions

private:
    double radius;
    // ... Remaining data members
    std::unique_ptr<DrawStrategy<Circle>> drawer;
};

class Square : public Shape
{
public:
    Square(double side, std::unique_ptr<DrawStrategy<Square>>&& ds)
        : sideLength{ side }, drawer{ std::move(ds) }
    {}

    double getSideLength() const {
        return sideLength;
    }

    void draw() const override {
        drawer->draw(*this);
    }

private:
    double sideLength;
    std::unique_ptr<DrawStrategy<Square>> drawer;
};

class OpenGLDrawer : public DrawStrategy<Circle>,
                     public DrawStrategy<Square>
{
public:
    void draw(const Circle& circle) const override {
        // OpenGL specific implementation for drawing a circle
        std::cout << "OpenGL: Drawing a circle with radius: " << circle.getRadius() << '\n';
    }

    void draw(const Square& square) const override {
        // OpenGL specific implementation for drawing a square
        std::cout << "OpenGL: Drawing a square with side length: " << square.getSideLength() << '\n';
    }
};

using Shapes = std::vector<std::unique_ptr<Shape>>;

class ShapeFactory
{
public:
    virtual ~ShapeFactory() = default;

    virtual Shapes createShapes(std::string_view filenames) const = 0;
};

void drawAllShapes(const Shapes& shapes)
{
    for (const auto& shape : shapes)
    {
        shape->draw();
    }
}

void createAndDrawShapes(const ShapeFactory& factory, std::string_view filenames)
{
    auto shapes = factory.createShapes(filenames);
    drawAllShapes(shapes);
}

// High Level
// ---------------------------------------------------------------------------- Architectual Boundary
// Low Level

class YourShapeFactory : public ShapeFactory
{
public:
    Shapes createShapes(std::string_view filenames) const override
    {
        Shapes shapes;
        std::string shape{};
        std::ifstream shapesFile{ filenames.data() };

        while (std::getline(shapesFile, shape))
        {
            // Logic to create shapes based on the input
            // For simplicity, let's assume the input is just the shape type
            if (shape == "circle")
            {
                shapes.push_back(std::make_unique<Circle>(5.0, std::make_unique<OpenGLDrawer>()));
            }
            else if (shape == "square")
            {
                shapes.push_back(std::make_unique<Square>(4.0, std::make_unique<OpenGLDrawer>()));
            }
        }

        return shapes;
    }
};

int main()
{
    YourShapeFactory factory;
    createAndDrawShapes(factory, "shapes.txt");

    return 0;
}
