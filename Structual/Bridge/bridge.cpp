#include "Animal.h"
#include "Fake.h"
#include "Person.h"
#include "Pimpl.h"
#include <iostream>
#include <string>

using namespace std;

// two classes of objects

// Renderers - determine how an object is drawn
// Shapes - determine what to draw

struct Renderer
{
    virtual void render_circle(float x, float y, float radius) const = 0;
    virtual ~Renderer()                                              = default;
};

struct VectorRenderer : Renderer
{
    void render_circle(float x, float y, float radius) const override
    {
        cout << "Rasterizing circle of radius_ " << radius << endl;
        cout << "Rasterizing circle of x and y" << x << " " << y << endl;
    }
};

struct RasterRenderer : Renderer
{
    void render_circle(float x, float y, float radius) const override
    {
        cout << "Drawing a vector circle of radius_ " << radius << endl;
        cout << "Drawing a vecotr circle of x and y" << x << " " << y << endl;
    }
};

class Shape
{
protected:
    explicit Shape(const Renderer& renderer)
        : renderer_{renderer}
    {}

public:
    virtual ~Shape()                  = default;
    virtual void draw()               = 0; // implementation specific
    virtual void resize(float factor) = 0; // abstraction specific
protected:
    const Renderer& renderer_;
};

class Circle : public Shape
{
public:
    Circle(const Renderer& renderer, float x, float y, float radius)
        : Shape{renderer}
        , x_{x}
        , y_{y}
        , radius_{radius}
    {}

    void draw() override { renderer_.render_circle(x_, y_, radius_); }

    void resize(float factor) override { radius_ *= factor; }

private:
    float x_, y_, radius_;
};

void bridge()
{
    // Core idea is to switch from inheritance to composition by having one class have a data member as a reference to
    // the other class, hence the bridge
    const RasterRenderer rr;
    Circle         raster_circle{rr, 5, 5, 5};
    raster_circle.draw();
    raster_circle.resize(2);
    raster_circle.draw();
}

int main()
{
    // Pimpl
    // binary interfaces are fragile; this removes most of the internals to a separate class
    // prevents recompilation of sources reliant on the header
    bridge();

    // Toy example of not include tpp inside hpp for class template
    Fake<double> fake(1.0);
    fake.print();

    Pimpl<Animal> pAnimal(Animal{3.0, 4});
    std::cout << "Animal height is " << pAnimal->height << '\n';

    // Pimpl inside the normal class
    Person p;
    p.greet();

    return 0;
}
