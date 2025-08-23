#include <memory>

template<typename T>
class Pimpl final
{
private:
    std::unique_ptr<T> impl_;

public:
    Pimpl();
    ~Pimpl() = default;

    template<typename... Args>
    explicit Pimpl(Args&&... args);

    T* operator->();
    T& operator*();
};

#include "Pimpl.tpp"