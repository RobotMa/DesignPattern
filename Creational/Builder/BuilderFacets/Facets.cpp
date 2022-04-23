#include <iostream>

#include "Person.h"
#include "PersonAddressBuilder.h"
#include "PersonBuilder.h"
#include "PersonJobBuilder.h"

int main()
{
    const Person p = Person::create()
                       .lives()
                       .at("123 London Road")
                       .with_postcode("SW1 1GB")
                       .in("London")
                       .works()
                       .at("PragmaSoft")
                       .as_a("Consultant")
                       .earning(10e6);

    std::cout << p << '\n';

    const Person        p2 = Person::create();
    const PersonBuilder b2 = Person::create();
    const auto          a2 = Person::create();

    return 0;
}