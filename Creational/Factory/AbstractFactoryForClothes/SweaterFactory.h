#pragma once
#include "TopsFactory.h"
#include <memory>

struct Tops;

struct SweaterFactory final : TopsFactory
{
    [[nodiscard]] auto make(Color color, DressCode dressCode, const std::string& brand) const
      -> std::unique_ptr<Tops> override
    {
        return std::make_unique<Sweater>(color, dressCode, brand);
    }
};