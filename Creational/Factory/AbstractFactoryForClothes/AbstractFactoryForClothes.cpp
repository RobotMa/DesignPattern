#include "Clothes/Color.h"
#include "Clothes/DressCode.h"
#include "Clothes/Tops.h"
#include "ClothesVisualizer/TopsVisualizer.h"
#include "MegaClothesFactory.h"

int main()
{
    MegaClothesFactory df;

    auto sweaterPtr = df.makeClothes(TopsType::SWEATER, Color::BLACK, DressCode::CASUAL, "BOSS");
    auto shirtPtr   = df.makeClothes(TopsType::SHIRT, Color::WHITE, DressCode::CASUAL, "THEORY");

    const TopsVisualizer sweaterViz{*sweaterPtr};
    sweaterViz.printClothesInfo();

    const TopsVisualizer topViz{*shirtPtr};
    topViz.printClothesInfo();

    return 0;
}