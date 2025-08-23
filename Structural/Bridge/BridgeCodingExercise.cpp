#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <string_view>

using namespace std;

struct Renderer
{
    [[nodiscard]] virtual std::string_view what_to_render_as() const = 0;
    virtual ~Renderer()                                              = default;
};

struct Shape
{
    std::string_view name_;
    const Renderer&  renderer_;

    explicit Shape(const Renderer& renderer)
        : renderer_{renderer}
    {}

    [[nodiscard]] string str() const
    {
        ostringstream oss;
        oss << "Drawing " << name_ << " as " << renderer_.what_to_render_as();
        return oss.str();
    }
};

struct Triangle : Shape
{
    explicit Triangle(const Renderer& renderer)
        : Shape{renderer}
    {
        name_ = "Triangle";
    }
};

struct Square : Shape
{
    explicit Square(const Renderer& renderer)
        : Shape{renderer}
    {
        name_ = "Square";
    }
};

struct RasterRenderer : Renderer
{
    [[nodiscard]] std::string_view what_to_render_as() const override { return "pixels"; }
};

struct VectorRenderer : Renderer
{
    [[nodiscard]] std::string_view what_to_render_as() const override { return "lines"; }
};

class Evaluate : public testing::Test
{};

TEST_F(Evaluate, SimpleTest)
{
    ASSERT_EQ("Drawing Square as lines", Square{VectorRenderer{}}.str());
}

int main(int ac, char* av[])
{
    testing::InitGoogleTest(&ac, av);
    return RUN_ALL_TESTS();
}