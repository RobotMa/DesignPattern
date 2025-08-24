// when to use CRTP?
template <class T> 
struct Base
{
    void interface()
    {
        // ...
        static_cast<T*>(this)->implementation();
        // ...
    }

    static void static_func()
    {
        // ...
        T::static_sub_func();
        // ...
    }
};

struct Derived : Base<Derived>
{
    void implementation();
    static void static_sub_func();
};

int main()
{
    Base<Derived>* base_ptr = new Derived();
    (void) base_ptr;
    return 0;
}