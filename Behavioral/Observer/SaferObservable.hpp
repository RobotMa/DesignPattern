#pragma once

#include <algorithm>
#include <mutex>
#include <string>
#include <vector>

template<typename>
struct Observer;

template<typename T>
class SaferObservable
{
protected:
    std::vector<Observer<T>*> observers_{};
    using mutex_t = std::recursive_mutex;
    mutex_t mtx_;

public:
    void notify(T& source, const std::string& fieldName)
    {
        std::scoped_lock<mutex_t> lock{mtx_};
        for (auto observer : observers_) {
            if (observer) {
                observer->fieldChanged(source, fieldName);
            }
        }
    }

    void subscribe(Observer<T>& observer)
    {
        std::scoped_lock<mutex_t> lock{mtx_};
        observers_.push_back(&observer);
        std::cout << "Subscribed to observer No." << observers_.size() << '\n';
    }

    void unsubscribe(Observer<T>& observer)
    {
        // Option1 : The following code works with simple non-recursive mutex
        //        auto it = std::find(begin(observers_), end(observers_), &observer);
        //        if (it != end(observers_)) {
        //            *it = nullptr;
        //            std::cout << "Unsubscribed from another observer \n";
        //        }

        // Optoin 2 : The following lock is possible when using recursive_mutex
        std::scoped_lock<mutex_t> lock{mtx_};
        // Erase-remove idiom
        observers_.erase(remove(observers_.begin(), observers_.end(), &observer), observers_.end());
    }
};
