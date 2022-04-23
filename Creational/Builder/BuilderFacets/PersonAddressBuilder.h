#pragma once

#include "PersonBuilder.h"

#include <string>

class PersonAddressBuilder : public PersonBuilderBase
{
private:
    using Self = PersonAddressBuilder;

public:
    explicit PersonAddressBuilder(Person& person)
        : PersonBuilderBase{person}
    {}

    Self& at(std::string street_address)
    {
        person_.street_address_ = street_address;
        return *this;
    }

    Self& with_postcode(std::string post_code)
    {
        person_.post_code = post_code;
        return *this;
    }

    Self& in(std::string city)
    {
        person_.city_ = city;
        return *this;
    }
};