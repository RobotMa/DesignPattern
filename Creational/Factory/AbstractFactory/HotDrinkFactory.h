#pragma once
#include "HotDrink.h"

struct HotDrinkFactory {
  // Benefit of trailing return type
  // [1] it allows to use the return type in the
  // In template programming and generic coding, sometimes the return type
  // of a function depends on its parameter types.Trailing return types
  // allow the return type to be specified using the function’s parameters,
  // which can only be named after they have been declared.

  //
  [[nodiscard]] virtual auto make() -> std::unique_ptr<HotDrink> const = 0;
  virtual ~HotDrinkFactory() = default;
};