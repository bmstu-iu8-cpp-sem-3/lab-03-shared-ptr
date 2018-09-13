# Лабораторная работа №2

### Задание 2. SharedPtr
**SharedPtr** реализует подсчет ссылок на ресурс. Ресурс освободится тогда, когда счетчик ссылок на него будет равен 0. Как видно, система реализует одно из основных правил сборщика мусора.
Многопоточное программирование сложно представить без использования класса `shared_ptr`. Например, класс `scoped_refptr` (аналог `std::shared_ptr`) используется в Chromium [32,753 раз](https://cs.chromium.org/search/?q=scoped_refptr&sq=package:chromium&type=cs). Чтобы лучше усвоить и понять принцип работы этого "умного" указателя, необходимо его реализовать своими руками.

Реализуйте класс SharedPtr. Для счетчика ссылок используйте переменную класса `std::atomic_uint`. Интерфейс работы с этим классом аналогичен работе с переменной типа `unsigned int`, т.е. к нему применимы операции префиксного инкремента и декремента.

```cpp
template <typename T>
class SharedPtr {
public:
  SharedPtr();
  SharedPtr(const SharedPtr&);
  SharedPtr& opeartor=(const SharedPtr&);
  SharedPtr(const SharedPtr&);
  
  void reset();
  void reset(T*);
  void swap(SharedPtr&);
  T* get();
  T& operator*() const;
  T* operator->() const;
  // возвращает количество объектов shared_ptr, которые ссылаются на тот же управляемый объект
  size_t use_count() const;
  // проверяет, указывает ли указатель на объект
  operator bool() const;
};

```
