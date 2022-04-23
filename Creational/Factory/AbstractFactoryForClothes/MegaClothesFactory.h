#pragma once
#include "Clothes/Tops.h"
#include "ShirtFactory.h"
#include "SweaterFactory.h"

#include <memory>
#include <string>
#include <unordered_map>

struct Tops;

class MegaClothesFactory
{
public:
    MegaClothesFactory();

    [[nodiscard]] auto makeClothes(TopsType topsType, Color color, DressCode dressCode, const std::string& brand)
      -> std::unique_ptr<Tops>;

private:
    std::unordered_map<TopsType, std::unique_ptr<const ClothesFactory>> clothesFactories_;
};