#include "MyClass.hpp"

struct MyClass::ImplMyClass
{
    explicit ImplMyClass(const int a_in) : a(a_in) {}
    int a;
    void print()
    {
        std::cout << " ImplMyClass is printing \n";
    }
};

MyClass::MyClass(const int a) : impl_(std::make_unique<ImplMyClass>(a)) {}

MyClass::~MyClass() = default;

void MyClass::print()
{
    impl_->print();
}

void MyClass::printThis()
{
    std::cout << "privately print this \n";
}
