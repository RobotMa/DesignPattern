#include "MegaClothesFactory.h"

#include <memory>

MegaClothesFactory::MegaClothesFactory()
{
    clothesFactories_[TopsType::SWEATER] = std::make_unique<const SweaterFactory>();
    clothesFactories_[TopsType::SHIRT]   = std::make_unique<const ShirtFactory>();
}

auto MegaClothesFactory::makeClothes(TopsType topsType, Color color, DressCode dressCode, const std::string& brand)
  -> std::unique_ptr<Tops>
{
    auto topsPtr = clothesFactories_[topsType]->make(color, dressCode, brand);
    return topsPtr;
}
