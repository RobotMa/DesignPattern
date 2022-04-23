#pragma once
#include "HotDrink.h"

struct HotDrinkFactory
{
  [[nodiscard]] virtual unique_ptr<HotDrink> make() const = 0;
  virtual ~HotDrinkFactory() = default;
};