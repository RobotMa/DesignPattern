#include <iostream>

template<typename T>
class Fake
{
public:
    Fake(T data);

    void print() const;

private:
    T data_;
};

