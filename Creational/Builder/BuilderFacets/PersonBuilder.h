#pragma once
#include "Person.h"

class PersonAddressBuilder;
class PersonJobBuilder;

class PersonBuilderBase
{
protected:
    Person& person_;
    explicit PersonBuilderBase(Person& person)
        : person_{person}
    {}

public:
    operator Person() const { return std::move(person_); }

    // builder facets

    [[nodiscard]] PersonAddressBuilder lives() const;
    [[nodiscard]] PersonJobBuilder     works() const;
};

class PersonBuilder : public PersonBuilderBase
{
private:
    Person p_;

public:
    PersonBuilder()
        : PersonBuilderBase{p_}
    {}
};