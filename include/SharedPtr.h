// Copyright 2020 Siver Elisey <sivereliseu7@gmail.com>

#ifndef LAB_03_SHARED_PTR_SHAREDPTR_H
#define LAB_03_SHARED_PTR_SHAREDPTR_H

#include "atomic"

using std::atomic_uint;

template <typename T>
class SharedPtr {
 private:
  T* ptr;
  std::atomic_uint* counter;

 public:
  //конструктор без параметров
  SharedPtr() : ptr(nullptr), counter(nullptr) {
    /*  ptr = nullptr;
      counter = nullptr;*/
  }

  //конструктор из обычной ссылки
  SharedPtr(T* pointer) {
    ptr = pointer;
    counter = new std::atomic_uint;
    (*counter) = 1;
  }

  //конструктор копирования
  SharedPtr(const SharedPtr& r) {
    ptr = r.ptr;
    counter = r.counter;
    (*counter)++;
  }

  //конструктор перемещения
  SharedPtr(SharedPtr&& r) {
    ptr = r.ptr;
    r.ptr = nullptr;
    counter = r.counter;
    r.counter = nullptr;
  };

  //деструктор
  ~SharedPtr() {
    if (ptr != nullptr) {
      (*counter)--;

      if (*counter == 0) {
        delete ptr;
        delete counter;
      }
    }
  }

  auto operator=(const SharedPtr& r) -> SharedPtr& {
    if (this != &r) {
      if (ptr != nullptr) {
        (*counter)--;
        if (*counter == 0) {
          delete ptr;
          delete counter;
        }
      }
      ptr = r.ptr;
      counter = r.counter;
      (*counter)++;
    }
    return *this;
  }

  auto operator=(SharedPtr&& r) -> SharedPtr& {
    if (this != &r) {
      if (ptr != nullptr) {
        (*counter)--;
        if (*counter == 0) {
          delete ptr;
          delete counter;
        }
      }
      ptr = r.ptr;
      counter = r.counter;

      r.counter = nullptr;
      r.ptr = nullptr;
    }
    return *this;
  }

  // проверяет, указывает ли указатель на объект
  operator bool() const {
    if (ptr != nullptr) return true;
    return false;
  }

  auto operator*() const -> T& { return *ptr; }

  auto operator->() const -> T* { return ptr; }

  auto get() -> T* { return ptr; }

  void reset() {
    if (*counter != 0) (*counter)--;
    if (*counter == 0) {
      delete ptr;
      delete counter;
    }
    counter = nullptr;
    ptr = nullptr;
  }

  void reset(T* pointer) {
    if (*counter != 0) (*counter)--;
    if (*counter == 0) {
      delete ptr;
      delete counter;
    }
    counter = new std::atomic_uint;
    *counter = 1;
    ptr = pointer;
  }

  void swap(SharedPtr& r) {
    if (*this != *r) {
      SharedPtr<T> buf = r;
      r.ptr = ptr;
      r.counter = counter;
      ptr = buf.ptr;
      counter = r.counter;
    }
  }
  // возвращает количество объектов SharedPtr, которые ссылаются на тот же
  // управляемый объект
  auto use_count() const -> std::size_t { return *counter; };
};

#endif  // LAB_03_SHARED_PTR_SHAREDPTR_H
