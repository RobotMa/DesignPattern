#pragma once
#include <memory>
#include <string>

class Person
{
public:
    Person();
    ~Person();
    void greet();

private:
    std::string name_;

    class PersonImpl;
    std::unique_ptr<PersonImpl> impl_;
};
