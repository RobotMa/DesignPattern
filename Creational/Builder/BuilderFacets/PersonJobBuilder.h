#pragma once
#include "PersonBuilder.h"

class PersonJobBuilder : public PersonBuilderBase
{
private:
    using Self = PersonJobBuilder;

public:
    explicit PersonJobBuilder(Person& person)
        : PersonBuilderBase{person}
    {}

    Self& at(std::string company_name)
    {
        person_.company_name_ = company_name;
        return *this;
    }

    Self& as_a(std::string position)
    {
        person_.position_ = position;
        return *this;
    }

    Self& earning(int annual_income)
    {
        person_.annual_income_ = annual_income;
        return *this;
    }
};