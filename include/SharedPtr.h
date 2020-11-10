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

  SharedPtr() {
    ptr = nullptr;
    counter = nullptr;
  }

  SharedPtr(T* ptr){
      this->ptr=ptr;
      *counter=1;
  }

  SharedPtr(const SharedPtr& r){
    ptr=r.ptr;
    counter=r.counter;
    if(*counter!=0) *counter++;
  }

  SharedPtr(SharedPtr&& r);

  ~SharedPtr(){
    *counter--;
    if(*counter==0) delete ptr;
  }

  auto operator=(const SharedPtr& r) -> SharedPtr&;

  auto operator=(SharedPtr&& r) -> SharedPtr&;

  // проверяет, указывает ли указатель на объект
  operator bool() const;
  auto operator*() const -> T&;
  auto operator->() const -> T*;

  auto get() -> T*;
  void reset();
  void reset(T* ptr);
  void swap(SharedPtr& r);
  // возвращает количество объектов SharedPtr, которые ссылаются на тот же
  // управляемый объект
  auto use_count() const -> size_t;
};

#endif  // LAB_03_SHARED_PTR_SHAREDPTR_H
