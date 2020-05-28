#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

#include <utility>
#include <memory>

template<class T>
class UniquePtr {
  private:
    T *ptr;
  public:
    UniquePtr() : ptr(nullptr) {}
    explicit UniquePtr(T *other_ptr);
    UniquePtr(const UniquePtr &other) = delete;
    UniquePtr &operator=(const UniquePtr &other) = delete;
    UniquePtr(UniquePtr &&other) noexcept;
    UniquePtr<T> &operator=(UniquePtr &&other) noexcept;
    T *Release();
    void Reset(T *new_ptr = nullptr);
    void Swap(UniquePtr<T> &other);
    T *Get() const;
    T operator*() const;
    T *operator->() const;
    explicit operator bool() const;
    ~UniquePtr();
};

template<class T>
UniquePtr<T>::UniquePtr(UniquePtr &&other) noexcept {
    if (other.ptr != nullptr) {
        ptr = other.ptr;
        other.ptr = nullptr;
    } else {
        ptr = nullptr;
    }
}

template<class T>
UniquePtr<T> &UniquePtr<T>::operator=(UniquePtr &&other) noexcept {
    if (this == &other) {
        return *this;
    }
    delete ptr;
    ptr = other.ptr;
    other.ptr = nullptr;
    return *this;
}

template<class T>
T *UniquePtr<T>::Release() {
    auto res = ptr;
    ptr = nullptr;
    return res;
}

template<class T>
void UniquePtr<T>::Reset(T *new_ptr) {
    delete ptr;
    ptr = new_ptr;
}

template<class T>
void UniquePtr<T>::Swap(UniquePtr<T> &other) {
    if (this != &other) {
        std::swap(*this, other);
    }
}

template<class T>
T *UniquePtr<T>::Get() const {
    return ptr;
}

template<class T>
T UniquePtr<T>::operator*() const {
    return *ptr;
}

template<class T>
T *UniquePtr<T>::operator->() const {
    return ptr;
}

template<class T>
UniquePtr<T>::operator bool() const {
    return ptr != nullptr;
}

template<class T>
UniquePtr<T>::~UniquePtr() {
    delete ptr;
}

template<class T>
UniquePtr<T>::UniquePtr(T *other_ptr) {
    ptr = other_ptr;
}

//#define MAKE_UNIQUE_IMPLEMENTED

#endif // UNIQUE_PTR_H
