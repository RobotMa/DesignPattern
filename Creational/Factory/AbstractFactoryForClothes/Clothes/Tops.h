#pragma once
#include "Clothes.h"
#include <iostream>
#include <string>

enum class TopsType : uint8_t
{
    SHIRT = 0,
    SWEATER
};

class Tops : public Clothes
{
public:
    Tops(Color color, DressCode dressCode, std::string brand)
        : color_{color}
        , dressCode_{dressCode}
        , brand_(std::move(brand))
    {}

    [[nodiscard]] Color            getColor() const noexcept override { return color_; }
    [[nodiscard]] DressCode        getDressCode() const noexcept override { return dressCode_; }
    [[nodiscard]] std::string_view getBrand() const noexcept override { return brand_; }

private:
    const Color       color_;
    const DressCode   dressCode_;
    const std::string brand_;
};

class Shirt : public Tops
{
public:
    Shirt(Color color, DressCode dressCode, const std::string& brand)
        : Tops(color, dressCode, brand)
    {}
};

class Sweater : public Tops
{
public:
    Sweater(Color color, DressCode dressCode, const std::string& brand)
        : Tops(color, dressCode, brand)
    {}
};