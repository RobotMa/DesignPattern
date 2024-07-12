#pragma once
#include "HotDrinkFactory.h"

struct TeaFactory : HotDrinkFactory {
  auto make() -> std::unique_ptr<HotDrink> const override {
    return make_unique<Tea>();
  }
};