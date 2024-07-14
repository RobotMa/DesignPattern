#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// open closed principle

// open for extension, closed for modification

enum class Color : uint8_t { red, green, blue };

enum class Size : uint8_t { small, medium, large };

struct Product {
  std::string name;
  Color color;
  Size size;
};

template <typename T> struct AndSpecification;

template <typename T> class Specification {
public:
  virtual ~Specification() = default;
  [[nodiscard]] virtual bool is_satisfied(const T &item) const = 0;

  // new: breaks OCP if you add it post-hoc
  /*AndSpecification<T> operator&&(Specification<T>&& other)
  {
    return AndSpecification<T>(*this, other);
  }*/
};

class ColorSpecification : public Specification<Product> {

public:
  explicit ColorSpecification(Color color) : color_(color) {}

  [[nodiscard]] bool is_satisfied(const Product &item) const override {
    return item.color == color_;
  }

private:
  Color color_;
};

class SizeSpecification : public Specification<Product> {

public:
  explicit SizeSpecification(const Size size) : size_{size} {}

  [[nodiscard]] bool is_satisfied(const Product &item) const override {
    return item.size == size_;
  }

private:
  Size size_;
};

// new:
template <typename T>
AndSpecification<T> operator&&(const Specification<T> &first,
                               const Specification<T> &second) {
  return {first, second};
}

using ProductRef = std::reference_wrapper<const Product>;
using ProductCollection = std::vector<ProductRef>;

template <typename T> struct Filter {
  [[nodiscard]] virtual auto
  filter(const ProductCollection &items,
         const Specification<T> &spec) const -> ProductCollection = 0;
  virtual ~Filter() = default;
};

struct BetterFilter : Filter<Product> {
  [[nodiscard]] auto filter(const ProductCollection &items,
                            const Specification<Product> &spec) const
      -> ProductCollection override {

    ProductCollection result;

    auto predicate = [&spec](const ProductRef &ref) {
      return spec.is_satisfied(ref.get());
    };

    std::copy_if(items.cbegin(), items.cend(), std::back_inserter(result),
                 predicate);

    return result;
  }
};

template <typename T> struct AndSpecification : Specification<T> {
  const Specification<T> &first_;
  const Specification<T> &second_;

  AndSpecification(const Specification<T> &first,
                   const Specification<T> &second)
      : first_(first), second_(second) {}

  [[nodiscard]] bool is_satisfied(const T &item) const override {
    return first_.is_satisfied(item) && second_.is_satisfied(item);
  }
};

// new:

int main() {
  const Product apple{"Apple", Color::green, Size::small};
  const Product tree{"Tree", Color::green, Size::large};
  const Product house{"House", Color::blue, Size::large};

  const std::vector<ProductRef> all{apple, tree, house};

  const BetterFilter bf;
  const ColorSpecification green(Color::green);
  const auto green_things = bf.filter(all, green);
  for (const auto &x : green_things) {
    std::cout << x.get().name << " is green\n";
  }

  const SizeSpecification large(Size::large);
  AndSpecification<Product> green_and_large(green, large);

  // auto big_green_things = bf.filter(all, green_and_large);

  // use the operator instead (same for || etc.)
  auto spec = green && large;
  for (auto &x : bf.filter(all, spec)) {
    std::cout << x.get().name << " is green and large\n";
  }

  // warning: the following will compile but will NOT work
  // auto spec2 = SizeSpecification{Size::large} &&
  //              ColorSpecification{Color::blue};

  return 0;
}