//Copyright 2019 ARAOvsepyan
#pragma once

#include <iostream>
#include <atomic>
#include <algorithm>
#include <cstddef>
#include <string>
#include <utility>


template <typename T>
class SharedPtr{
private:
    T* _data;
    std::atomic_uint *cnt;

public:
    SharedPtr()
    {
        _data = nullptr;
        cnt = nullptr;
    };

    explicit SharedPtr(T* ptr)
    {
        _data = ptr;
        cnt = new std::atomic_uint(1);
    };

    SharedPtr(const SharedPtr& r)
    {
        cnt = nullptr;
        *this = r;
    };

    SharedPtr(SharedPtr&& r) noexcept
    {
        cnt = nullptr;
        *this = std::move(r);
    };

    ~SharedPtr()
    {
        if (cnt == nullptr)
            return;
        (cnt)--;
        if (cnt == 0) {
            delete _data;
            delete cnt;
        }
    };

    auto operator=(const SharedPtr& r)->SharedPtr&{
        if (this == &r)
            return *this;

        this->~SharedPtr();

        _data = r._data;
        cnt = r.cnt;
        (*cnt)++;

        return *this;
    };

    auto operator=(SharedPtr&& r) noexcept ->SharedPtr&  {
        if (this == &r)
            return *this;

        this->~SharedPtr();

        _data = r._data;
        cnt = r.cnt;
        r.cnt = nullptr;
        r._data = nullptr;

        return *this;
    };

    explicit operator bool() const
    {
        return _data != nullptr;
    };

    auto operator*() const->T&{
        return *_data;
    };

    auto operator->() const->T*{
        return _data;
    };

    auto get()->T*{
        return _data;
    };

    void reset(){
        *this = SharedPtr();
    }

    void reset(T* ptr){
        *this = SharedPtr(ptr);
    }

    void swap(SharedPtr& r){
        std::swap(_data, r._data);
        std::swap(cnt, r.cnt);
    }

    [[nodiscard]] auto use_count() const->size_t {
        if (cnt != nullptr)
            return *cnt;
        else
            return 0;
    };
};
