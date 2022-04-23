#pragma once

#include "../Clothes/Tops.h"
#include "ClothesVisualizer.h"

class TopsVisualizer : public ClothesVisualizer
{
public:
    explicit TopsVisualizer(Tops tops);

    void printClothesInfo() const override;
    void displayClothesPicture() const override;

private:
    Tops tops_;
};