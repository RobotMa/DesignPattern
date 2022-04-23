#pragma once
#include "Clothes/Tops.h"
#include "TopsFactory.h"
#include <memory>

struct ShirtFactory final : TopsFactory
{
    [[nodiscard]] auto make(Color color, DressCode dressCode, const std::string& brand) const
      -> std::unique_ptr<Tops> override
    {
        return std::make_unique<Shirt>(color, dressCode, brand);
    }
};