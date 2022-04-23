#pragma once

#include <string_view>

enum class Color : uint8_t;
enum class DressCode : uint8_t;

class Clothes
{
public:
    virtual ~Clothes() = default;

    virtual Color            getColor() const noexcept     = 0;
    virtual DressCode        getDressCode() const noexcept = 0;
    virtual std::string_view getBrand() const noexcept     = 0;
};
