//
// Created by roma on 11/4/21.
//

#include "EnumTrait.h"

#include <array>
#include <iostream>

/// use case
enum class MyEnum
{
    first,
    second,
    third
};

template <>
struct base::EnumTrait<MyEnum>
{
    static constexpr std::array namedEnumerators{
      base::Enumerator{MyEnum::first, "first"},
      base::Enumerator{MyEnum::first, "second"},
      base::Enumerator{MyEnum::first, "third"},
    };
};

int main()
{
    std::cout << base::EnumTrait<MyEnum>::namedEnumerators[static_cast<unsigned long>(MyEnum::first)] << '\n';
    return 0;
}