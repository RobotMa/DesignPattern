#pragma once
#include "CoffeeFactory.h"
#include "HotDrink.h"
#include "TeaFactory.h"
#include <functional>
#include <map>
#include <string>

struct HotDrink;

class DrinkFactory
{
private:
    map<DrinkType, unique_ptr<HotDrinkFactory>> hotFactories_;

public:
    DrinkFactory()
    {
        hotFactories_[DrinkType::COFFEE] = make_unique<CoffeeFactory>();
        hotFactories_[DrinkType::TEA]    = make_unique<TeaFactory>();
    }

    unique_ptr<HotDrink> make_drink(DrinkType drinkType)
    {
        auto drink = hotFactories_[drinkType]->make();
        drink->prepare(200); // oops!
        return drink;
    }
};

class DrinkWithVolumeFactory
{
    map<string, function<unique_ptr<HotDrink>()>> factories;

public:
    DrinkWithVolumeFactory()
    {
        factories["tea"] = [] {
            auto tea = make_unique<Tea>();
            tea->prepare(200);
            return tea;
        };
    }

    unique_ptr<HotDrink> make_drink(const string& name);
};

inline unique_ptr<HotDrink> DrinkWithVolumeFactory::make_drink(const string& name)
{
    return factories[name]();
}
