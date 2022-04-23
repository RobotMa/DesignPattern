#include <iostream>
#include <memory>

class MyClass
{
    public:
        MyClass (const int a); 
        void print();
        ~MyClass();
    private:
        friend class TestMyClass;
        void printThis();
        struct ImplMyClass;
        std::unique_ptr<ImplMyClass> impl_;
};
