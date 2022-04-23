#include <iostream>
#include <string>
#include <vector>

// open closed principle

// open for extension, closed for modification

using namespace std;

enum class Color : uint8_t
{
    red,
    green,
    blue
};

enum class Size : uint8_t
{
    small,
    medium,
    large
};

struct Product
{
    string name;
    Color  color;
    Size   size;
};

template<typename T>
struct AndSpecification;

template<typename T>
struct Specification
{
    virtual ~Specification()                 = default;
    virtual bool is_satisfied(T* item) const = 0;

    // new: breaks OCP if you add it post-hoc
    /*AndSpecification<T> operator&&(Specification<T>&& other)
    {
      return AndSpecification<T>(*this, other);
    }*/
};

// new:
template<typename T>
AndSpecification<T> operator&&(const Specification<T>& first, const Specification<T>& second)
{
    return {first, second};
}

template<typename T>
struct Filter
{
    virtual vector<T*> filter(vector<T*> items, const Specification<T>& spec) const = 0;
    virtual ~Filter()                                                               = default;
};

struct BetterFilter : Filter<Product>
{
    vector<Product*> filter(vector<Product*> items, const Specification<Product>& spec) const override
    {
        vector<Product*> result;
        for (auto& p : items)
            if (spec.is_satisfied(p))
                result.push_back(p);
        return result;
    }
};

struct ColorSpecification : Specification<Product>
{
    Color color_;

    explicit ColorSpecification(Color color)
        : color_(color)
    {}

    bool is_satisfied(Product* item) const override { return item->color == color_; }
};

struct SizeSpecification : Specification<Product>
{
    Size size_;

    explicit SizeSpecification(const Size size)
        : size_{size}
    {}

    bool is_satisfied(Product* item) const override { return item->size == size_; }
};

template<typename T>
struct AndSpecification : Specification<T>
{
    const Specification<T>& first_;
    const Specification<T>& second_;

    AndSpecification(const Specification<T>& first, const Specification<T>& second)
        : first_(first)
        , second_(second)
    {}

    bool is_satisfied(T* item) const override { return first_.is_satisfied(item) && second_.is_satisfied(item); }
};

// new:

int main()
{
    Product apple{"Apple", Color::green, Size::small};
    Product tree{"Tree", Color::green, Size::large};
    Product house{"House", Color::blue, Size::large};

    const vector<Product*> all{&apple, &tree, &house};

    BetterFilter       bf;
    ColorSpecification green(Color::green);
    auto               green_things = bf.filter(all, green);
    for (auto& x : green_things)
        cout << x->name << " is green\n";

    SizeSpecification         large(Size::large);
    AndSpecification<Product> green_and_large(green, large);

    // auto big_green_things = bf.filter(all, green_and_large);

    // use the operator instead (same for || etc.)
    auto spec = green && large;
    for (auto& x : bf.filter(all, spec))
        cout << x->name << " is green and large\n";

    // warning: the following will compile but will NOT work
    // auto spec2 = SizeSpecification{Size::large} &&
    //              ColorSpecification{Color::blue};

    return 0;
}