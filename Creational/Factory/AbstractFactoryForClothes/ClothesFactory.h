#pragma once
#include <memory>

enum class Color : uint8_t;
enum class DressCode : uint8_t;
class Clothes;

struct ClothesFactory
{
    [[nodiscard]] virtual auto make(Color color, DressCode dressCode, const std::string& brand) const
      -> std::unique_ptr<Tops> = 0;
    virtual ~ClothesFactory()  = default;
};
