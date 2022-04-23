//
// Created by roma on 10/29/21.
//

#pragma once

#include <string_view>
#include <type_traits>

namespace base {

template<class EnumType>
struct Enumerator {
    using Type = EnumType;
    EnumType value{};
    std::string_view name{};
};

template<class EnumType>
Enumerator(EnumType, std::string_view) -> Enumerator<EnumType>;

template<class T>
struct EnumTrait{};
}

