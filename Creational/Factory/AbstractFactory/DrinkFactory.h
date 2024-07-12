#pragma once
#include "CoffeeFactory.h"
#include "HotDrink.h"
#include "TeaFactory.h"
#include <functional>
#include <map>
#include <string>

struct HotDrink;

class DrinkFactory {
public:
  DrinkFactory() {
    hotFactories_[DrinkType::COFFEE] = std::make_unique<CoffeeFactory>();
    hotFactories_[DrinkType::TEA] = std::make_unique<TeaFactory>();
  }

  unique_ptr<HotDrink> make_drink(DrinkType drinkType) {
    auto drink = hotFactories_[drinkType]->make();
    drink->prepare(200); // oops!
    return drink;
  }

private:
  std::unordered_map<DrinkType, std::unique_ptr<HotDrinkFactory>> hotFactories_;
};

class DrinkWithVolumeFactory {
public:
  DrinkWithVolumeFactory() {
    factories["tea"] = [] {
      auto tea = make_unique<Tea>();
      tea->prepare(200);
      return tea;
    };
  }

  std::unique_ptr<HotDrink> make_drink(const std::string &name);

private:
  std::unordered_map<std::string, std::function<std::unique_ptr<HotDrink>()>>
      factories;
};

inline unique_ptr<HotDrink>
DrinkWithVolumeFactory::make_drink(const std::string &name) {
  return factories[name]();
}
