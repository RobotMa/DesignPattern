#pragma once
#include <iostream>
#include <memory>
#include <string>

using namespace std;

enum class DrinkType : uint8_t { TEA = 0, COFFEE };

struct HotDrink {
  virtual ~HotDrink() = default;

  virtual void prepare(int volume) const = 0;
};

struct Tea : HotDrink {

  void prepare(int volume) const override {
    cout << "Take tea bag, boil water, pour " << volume << "ml, add some lemon"
         << endl;
  }
};

struct Coffee : HotDrink {
  void prepare(int volume) const override {
    cout << "Grind some beans, boil water, pour " << volume
         << "ml, add cream, enjoy!" << endl;
  }
};