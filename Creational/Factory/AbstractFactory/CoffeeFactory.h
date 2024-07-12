#pragma once
#include "HotDrink.h"
#include "HotDrinkFactory.h"
#include <memory>

struct HotDrink;

struct CoffeeFactory : HotDrinkFactory {
  [[nodiscard]] auto make() -> std::unique_ptr<HotDrink> const override {
    return make_unique<Coffee>();
  }
};