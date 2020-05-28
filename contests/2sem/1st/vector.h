//
// Created by Vladimir on 22.03.2020.
//

#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>

using namespace std;

template<class T>
class Vector {
  private:
    T *array;
    size_t size;
    size_t capacity;

    void Realloc() {
        T *new_array = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            new_array[i] = array[i];
        }
        delete[] array;
        array = new_array;
    }

  public:
    Vector() : size(0), capacity(0), array(nullptr) {}
    explicit Vector(const size_t &size) : size(size), capacity(size), array(new T[size]) {}
    explicit Vector(const size_t &size, const T &value) :
            Vector(size) {
        for (size_t i = 0; i < size; ++i) {
            array[i] = value;
        }
    }

    Vector(const Vector &old_vector) {
        if (old_vector.array != nullptr) {
            size = old_vector.size;
            capacity = old_vector.capacity;
            array = new T[capacity];
            for (size_t i = 0; i < size; ++i) {
                array[i] = old_vector.array[i];
            }
        } else {
            size = capacity = 0;
            array = nullptr;
        }
    }

    bool Empty() const {
        return size == 0;
    }

    size_t Size() const {
        return size;
    }

    size_t Capacity() const {
        return capacity;
    }

    T *Data() {
        return array;
    }

    const T *Data() const {
        return array;
    }

    Vector &operator=(const Vector &vector) {
        if (vector.array == nullptr) {
            delete[] array;
            size = capacity = 0;
            array = nullptr;
        } else if (this != &vector) {
            if (vector.Capacity() > capacity) {
                delete[] array;
                capacity = vector.Capacity();
                array = new T[capacity];
            }
            size = vector.Size();
            for (size_t i = 0; i < vector.Size(); ++i) {
                array[i] = vector.array[i];
            }
        }
        return *this;
    }

    ~Vector() {
        size = capacity = 0;
        delete[] array;
    }

    void Clear() {
        size = 0;
    }

    void PushBack(const T &value) {
        if (capacity == 0) {
            capacity = 1;
            array = new T[capacity];
        } else if (size == capacity) {
            capacity *= 2;
            Realloc();
        }
        array[size++] = value;
    }

    void PopBack() {
        if (size == 0) {
            return;
        }
        --size;
    }

    void Resize(const size_t &new_size) {
        if (new_size > capacity) {
            capacity = new_size;
            Realloc();
        }
        size = new_size;
    }

    void Resize(const size_t &new_size, const T &value) {
        const size_t old_size = size;
        Resize(new_size);
        if (new_size > old_size) {
            for (size_t i = old_size; i < new_size; ++i) {
                array[i] = value;
            }
        }
    }

    void Reserve(const size_t &new_cap) {
        if (new_cap <= capacity) {
            return;
        }
        capacity = new_cap;
        Realloc();
    }

    void ShrinkToFit() {
        capacity = size;
        Realloc();
    }

    void Swap(Vector &other) {
        swap(*this, other);
    }

    T &operator[](const size_t &index) {
        return array[index];
    }

    const T &operator[](const size_t &index) const {
        return array[index];
    }

    T &Front() {
        return array[0];
    }

    const T &Front() const {
        return array[0];
    }

    T &Back() {
        return array[size - 1];
    }

    const T &Back() const {
        return array[size - 1];
    }

    template<class V>
    friend bool operator==(const Vector<V> &lhs, const Vector<V> &rhs);

    template<class V>
    friend bool operator!=(const Vector<V> &lhs, const Vector<V> &rhs);

    template<class V>
    friend bool operator<(const Vector<V> &lhs, const Vector<V> &rhs);

    template<class V>
    friend bool operator<=(const Vector<V> &lhs, const Vector<V> &rhs);

    template<class V>
    friend bool operator>(const Vector<V> &lhs, const Vector<V> &rhs);

    template<class V>
    friend bool operator>=(const Vector<V> &lhs, const Vector<V> &rhs);
};

template<class V>
bool operator<(const Vector<V> &lhs, const Vector<V> &rhs) {
    size_t i, j;
    i = j = 0;
    while (i != lhs.Size()) {
        if (j == rhs.Size() || rhs[j] < lhs[i]) {
            return false;
        } else if (lhs[i] < rhs[j]) {
            return true;
        }
        ++i;
        ++j;
    }
    return (j != rhs.Size());
}

template<class V>
bool operator==(const Vector<V> &lhs, const Vector<V> &rhs) {
    return !(lhs < rhs) && !(rhs < lhs);
}

template<class V>
bool operator!=(const Vector<V> &lhs, const Vector<V> &rhs) {
    return !(lhs == rhs);
}

template<class V>
bool operator<=(const Vector<V> &lhs, const Vector<V> &rhs) {
    return (lhs == rhs || lhs < rhs);
}

template<class V>
bool operator>(const Vector<V> &lhs, const Vector<V> &rhs) {
    return !(lhs <= rhs);
}

template<class V>
bool operator>=(const Vector<V> &lhs, const Vector<V> &rhs) {
    return (lhs == rhs || lhs > rhs);
}

//Arthur thx 4 all