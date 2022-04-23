#include "MyClass.hpp"

class TestMyClass
{
    public:
        explicit TestMyClass(const int a) : myClass(a) {}
        void print()
        {
            myClass.impl_;
            /* myClass.impl_->print(); */
            myClass.printThis();
        };

    private:
        MyClass myClass;
};

int main()
{
    TestMyClass testMyClass(3);
    testMyClass.print();
    return 0;
}
