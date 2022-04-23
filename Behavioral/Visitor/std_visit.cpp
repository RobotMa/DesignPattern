#include <iostream>
#include <string>
#include <variant>

struct AddressPrinter
{
    void operator()(const std::string& house_name) const { std::cout << "A house called " << house_name << "\n"; }

    void operator()(const int house_number) const { std::cout << "House number " << house_number << "\n"; }
};

int main()
{
    std::variant<std::string, int> house;
    // house = "Montefiore Castle";
    house = 221;

    AddressPrinter ap;
    std::visit(ap, house);

    // what if you want to create a visitor in-place?
    std::visit(
      [](auto& arg) {
          using T = std::decay_t<decltype(arg)>;

          if constexpr (std::is_same_v<T, std::string>) {
              std::cout << "A house called " << arg.c_str() << "\n";
          } else {
              std::cout << "House number " << arg << "\n";
          }
      },
      house);

    return 0;
}