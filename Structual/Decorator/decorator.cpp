#include <iostream>
#include <string>
#include <utility>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;

struct Shape
{
    [[nodiscard]] virtual string str() const = 0;
    virtual ~Shape()                         = default;
};

struct Circle : Shape
{
    float radius_{};

    Circle() = default;

    explicit Circle(const float radius)
        : radius_{radius}
    {}

    void resize(float factor) { radius_ *= factor; }

    [[nodiscard]] string str() const override
    {
        ostringstream oss;
        oss << "A circle of radius_ " << radius_;
        return oss.str();
    }
};

struct Square : Shape
{
    float side_{};

    Square() = default;

    explicit Square(const float side)
        : side_{side}
    {}

    [[nodiscard]] string str() const override
    {
        ostringstream oss;
        oss << "A square of with side_ " << side_;
        return oss.str();
    }
};

// we are not changing the base class of existing
// objects

// cannot make, e.g., ColoredSquare, ColoredCircle, etc.

struct ColoredShape : Shape
{
    Shape& shape_;
    string color_;

    ColoredShape(Shape& shape, string color)
        : shape_{shape}
        , color_{std::move(color)}
    {}

    [[nodiscard]] string str() const override
    {
        ostringstream oss;
        oss << shape_.str() << " has the color_ " << color_;
        return oss.str();
    }
};

struct TransparentShape : Shape
{
    Shape&  shape_;
    uint8_t transparency_;

    TransparentShape(Shape& shape, const uint8_t transparency)
        : shape_{shape}
        , transparency_{transparency}
    {}

    [[nodiscard]] string str() const override
    {
        ostringstream oss;
        oss << shape_.str() << " has " << static_cast<float>(transparency_) / 255.f * 100.f << "% transparency_";
        return oss.str();
    }
};

// mixin inheritance

// note: class, not typename
template<typename T>
struct ColoredShape2 : T
{
    static_assert(is_base_of<Shape, T>::value, "Template argument must be a Shape");

    string color_;

    // need this (or not!)
    ColoredShape2() = default;

    template<typename... Args>
    explicit ColoredShape2(string color, Args... args)
        : T(std::forward<Args>(args)...)
        , color_{std::move(color)}
    // you cannot call base class ctor here
    // b/c you have no idea what it is
    {}

    [[nodiscard]] string str() const override
    {
        ostringstream oss;
        oss << T::str() << " has the color_ " << color_;
        return oss.str();
    }
};

template<typename T>
struct TransparentShape2 : T
{
    uint8_t transparency_;

    template<typename... Args>
    explicit TransparentShape2(const uint8_t transparency, Args... args)
        : T(std::forward<Args>(args)...)
        , transparency_{transparency}
    {}

    [[nodiscard]] string str() const override
    {
        ostringstream oss;
        oss << T::str() << " has " << static_cast<float>(transparency_) / 255.f * 100.f << "% transparency_";
        return oss.str();
    }
};

void wrapper()
{
    Circle circle{5};
    cout << circle.str() << endl;

    ColoredShape red_circle{circle, "red"};
    cout << red_circle.str() << endl;

    // red_circle.resize(); // oops

    TransparentShape red_half_visible_circle{red_circle, 128};
    cout << red_half_visible_circle.str() << endl;
}

void mixin_inheritance()
{
    // won't work without a default constructor
    ColoredShape2<Circle> green_circle{"green"};
    green_circle.radius_ = 123;
    cout << green_circle.str() << endl;

    TransparentShape2<ColoredShape2<Square>> blue_invisible_square{0};
    blue_invisible_square.color_ = "blue";
    blue_invisible_square.side_  = 321;
    cout << blue_invisible_square.str() << endl;
}

struct Logger
{
    function<void()> func_;
    string           name_;

    [[maybe_unused]] Logger(const function<void()>& func, string name)
        : func_{func}
        , name_{std::move(name)}
    {}

    void operator()() const
    {
        cout << "Entering " << name_ << endl;
        func_();
        cout << "Exiting " << name_ << endl;
    }
};

template<typename Func>
struct Logger2
{
    Func   func_;
    string name_;

    Logger2(const Func& func, string name)
        : func_{func}
        , name_{std::move(name)}
    {}

    void operator()() const
    {
        cout << "Entering " << name_ << endl;
        func_();
        cout << "Exiting " << name_ << endl;
    }
};

template<typename Func>
auto make_logger2(Func func, const string& name)
{
    return Logger2<Func>{func, name};
}

// need partial specialization for this to work
template<typename>
struct Logger3;

// return type and argument list
template<typename R, typename... Args>
struct Logger3<R(Args...)>
{
    Logger3(function<R(Args...)> func, string name)
        : func_{std::move(func)}
        , name_{std::move(name)}
    {}

    R operator()(Args... args)
    {
        cout << "Entering " << name_ << endl;
        R result = func_(args...);
        cout << "Exiting " << name_ << endl;
        return result;
    }

    function<R(Args...)> func_;
    string               name_;
};

template<typename R, typename... Args>
 auto make_logger3(R (*func)(Args...), const string& name)
{
    return Logger3<R(Args...)>(std::function<R(Args...)>(func), name);
}

double add(double a, double b)
{
    cout << a << "+" << b << "=" << (a + b) << endl;
    return a + b;
}

void function_decorator()
{
    // Logger([]() {cout << "Hello" << endl; }, "HelloFunction")();

    // cannot do this
    // make_logger2([]() {cout << "Hello" << endl; }, "HelloFunction")();
    auto call = make_logger2([]() { cout << "Hello!" << endl; }, "HelloFunction");
    call();

    auto logged_add = make_logger3(add, "Add");
    auto result     = logged_add(2, 3);
    (void)result;
}

void constructor_forwarding()
{
    struct [[maybe_unused]] NotAShape
    {
        [[nodiscard]] virtual string str() const { return string{}; }
        virtual ~NotAShape() = default;
    };

    // we don't want this to be legal, thus a static_assert above
    // ColoredShape2<NotAShape> legal;

    // no code completion for this case
    // can comment out argument, too! (default constructor)
    constexpr float           side1 = 2.0;
    TransparentShape2<Square> hidden_square{1, side1};
    cout << hidden_square.str() << endl;

    constexpr uint8_t                        transparency = 51;
    constexpr float                          side2        = 2.0;
    ColoredShape2<TransparentShape2<Square>> sq{"red", transparency, side2};
    cout << sq.str() << endl;
}

int main()
{
    wrapper();
    mixin_inheritance();
    constructor_forwarding();
    function_decorator();

    getchar();
    return 0;
}
