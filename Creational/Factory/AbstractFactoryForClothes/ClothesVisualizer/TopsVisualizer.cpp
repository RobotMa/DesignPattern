#include "TopsVisualizer.h"

#include <utility>

TopsVisualizer::TopsVisualizer(Tops tops)
    : tops_(std::move(tops))
{}

void TopsVisualizer::printClothesInfo() const
{
    std::cout << "Dress code is " << static_cast<int>(tops_.getDressCode()) << '\n';
    std::cout << "Color is " << static_cast<int>(tops_.getColor()) << '\n';
    std::cout << "Dress code is " << tops_.getBrand() << '\n';
    std::cout << '\n';
}

void TopsVisualizer::displayClothesPicture() const {}