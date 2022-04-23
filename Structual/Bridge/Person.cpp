#include "Person.h"

class Person::PersonImpl
{
public:
    void greet(Person* p);
};

void Person::PersonImpl::greet(Person* p)
{
    printf("hello %s", p->name_.c_str());
}

Person::Person()
    : impl_(new PersonImpl)
{}

Person::~Person() {}

void Person::greet()
{
    impl_->greet(this);
}