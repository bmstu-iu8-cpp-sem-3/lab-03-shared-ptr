#pragma once

#include <atomic>
#include <iostream>


class Counter {

    std::atomic_uint cnt;
public:

    Counter() : cnt(1)
    {}

    ~Counter() = default;

    explicit Counter(const std::atomic_uint& num) {
        cnt.store(num);
    }

    Counter& Increase() {
        ++cnt;
        return *this;
    }

    Counter& Decrease() {
        --cnt;
        return *this;
    }

    std::atomic_uint& Get() {
        return cnt;
    }
};


template <typename T>
class SharedPtr {
    T* _data;
    Counter* count;
public:

    SharedPtr() {
        _data = new T;
        count = new Counter();
    }

    ~SharedPtr() {
        reset();
    }

    SharedPtr(const SharedPtr& ptr) : _data(ptr._data), count(ptr.count) {
        if (count != nullptr)
            count->Increase();
    }

    SharedPtr(SharedPtr&& ptr) noexcept {
        _data = ptr._data;
        count = ptr.count;
        ptr.count = nullptr;
        ptr._data = nullptr;
    }

    SharedPtr& operator=(const SharedPtr& ptr) {
        if (this != &ptr) {
            reset();
            _data = ptr._data;
            count = ptr.count;
            count->Increase();
        }
        return *this;
    }

    SharedPtr<T> &operator=(SharedPtr&& ptr) noexcept {
        _data = ptr._data;
        count = ptr.count;
        ptr.count = nullptr;
        ptr._data = nullptr;
        return *this;
    }

 
    void reset()
    {
        *this = SharedPtr{};
    }

    void reset(T *ptr)
    {
        *this = SharedPtr{ptr};
    }

    void swap(SharedPtr& ptr) {
        if (_data != ptr._data) {
            std::swap(_data, ptr._data);
            std::swap(count, ptr.count);
        }
    }

    T* get() {
        if (_data == nullptr) {
            throw std::invalid_argument("null pointer");
        }
        return _data;
    }

    T& operator*() const {
        if (_data == nullptr)
            throw std::invalid_argument("Error");
        return *_data;
    }

    T* operator->() const {
        if (_data == nullptr)
            throw std::invalid_argument("Error");
        return _data;
    }

    size_t use_count() const {
        return static_cast<size_t>(count->Get());
    }

    explicit operator bool() const {
        return _data == nullptr;
    }
};
