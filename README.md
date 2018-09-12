# Лабораторная работа №2

### Задание 2. SharedPtr

Например, класс `scoped_refptr` (аналог `std::shared_ptr`) используется в Chromium [32,753 раз](https://cs.chromium.org/search/?q=scoped_refptr&sq=package:chromium&type=cs).

Реализуйте класс SharedPtr. Для счетчика ссылок используйте переменную класса `std::atomic_uint`. Интерфейс работы с этим классом аналогичен работе с переменной типа `unsigned int`, т.е. к нему применимы операции префиксного инкремента и декремента.
