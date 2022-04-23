#pragma once
#include <string>

template<typename T>
struct Observer
{
    virtual ~Observer()                                                       = default;
    virtual void fieldChanged(T& source, const std::string& field_name) = 0;
};
