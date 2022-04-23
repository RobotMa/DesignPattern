template<typename T>
Pimpl<T>::Pimpl()
    : impl_{new T{}}
{}

template<typename T>
// The parameter pack here makes it impossible to employ the template instantiation trick as in Fake.cpp
template<typename... Args>
Pimpl<T>::Pimpl(Args&&... args)
    : impl_{new T{std::forward<Args>(args)...}}
{}

template<typename T>
T* Pimpl<T>::operator->()
{
    return impl_.get();
}

template<typename T>
T& Pimpl<T>::operator*()
{
    return *impl_.get();
}