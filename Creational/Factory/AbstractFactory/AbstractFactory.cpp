#include "DrinkFactory.h"
#include "HotDrink.h"
#include <memory>

unique_ptr<HotDrink> make_drink(DrinkType drinkType) {
  unique_ptr<HotDrink> drink;

  switch (drinkType) {
  case DrinkType::TEA: {
    drink = std::make_unique<Tea>();
    drink->prepare(200);
    break;
  }
  case DrinkType::COFFEE: {
    drink = std::make_unique<Coffee>();
    drink->prepare(50);
    break;
  }
  }

  return drink;
}

int main() {
  auto d = make_drink(DrinkType::TEA);

  DrinkFactory df;
  const auto coffee = df.make_drink(DrinkType::COFFEE);

  return 0;
}