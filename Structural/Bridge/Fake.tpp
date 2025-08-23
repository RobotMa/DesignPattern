#include <iostream>
#include "Fake.h"

template<typename T>
Fake<T>::Fake(T data) : data_{data} {}

template<typename T>
void Fake<T>::print() const
{
    std::cout << data_ << '\n';
}
