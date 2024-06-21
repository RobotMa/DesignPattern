#include <iostream>
#include <cstdlib>

template <typename T>
class SharedPtr {

public:
  explicit SharedPtr(T *ptr) : ptr_(ptr), refCount_(new size_t(1)) {}

  SharedPtr(const SharedPtr &other)
      : ptr_(other.ptr_), refCount_(other.refCount_) {
    ++(*refCount_);
  }

  SharedPtr& operator=(const SharedPtr &other) {
    if (this == &other) {
      return *this;
    }

    if (--(*refCount_) == 0) {
      delete ptr_;
      delete refCount_;
    }

    ptr_ = other.ptr_;
    refCount_ = other.refCount_;
    ++(*refCount_);

    return *this;
  }

  ~SharedPtr() {
    if (--(*refCount_) == 0) {
      delete ptr_;
      delete refCount_;
    }
  }

  T& operator*() const { return *ptr_; }
  T* operator->() const { return ptr_; }
  size_t use_count() const { return *refCount_; }

private:
  T* ptr_;
  size_t* refCount_;
};

int main() {
  SharedPtr<double> sp1(new double(3.14));
  SharedPtr<double> sp2{sp1};

  std::cout << sp1.use_count() << '\n';
  std::cout << sp2.use_count() << '\n';
  return 0;
}