// Copyright 2020 Petr Portnov <gh@progrm-jarvis.ru>

#ifndef INCLUDE_SHARED_POINTER_HPP_
#define INCLUDE_SHARED_POINTER_HPP_

#include <atomic>
#include <memory>

namespace shared_pointer {

    template <typename T>
    class SharedPointer final {
        // stored right here so that access is faster than access through atomic member of control block
        T* rawPointer_;

        class ControlBlock final {
            friend class SharedPointer;

            std::atomic<T*> rawPointer_;
            std::atomic_size_t strongRefCount_;

            explicit ControlBlock(T* rawPointer);

            void acquireStrong_();
            void releaseStrong_();
        } * controlBlock_;

    public:
        // Constructors and destructor

        SharedPointer();

        explicit SharedPointer(T*&& rawPointer);

        template <typename... ConstructorArguments>
        explicit SharedPointer(ConstructorArguments&&... constructorArguments);

        SharedPointer(SharedPointer const& original);

        SharedPointer(SharedPointer&& original) noexcept;

        ~SharedPointer();

        SharedPointer& operator=(SharedPointer const& other) noexcept;

        SharedPointer& operator=(SharedPointer&& other) noexcept;

        // Operators

        operator bool() const noexcept;
        T& operator*() const noexcept;
        T* operator->() const noexcept;
    };

    template <typename T, typename... ConstructorArguments>
    inline SharedPointer<T> make_shared(ConstructorArguments&&... constructorArguments);
} // namespace shared_pointer

#endif // INCLUDE_SHARED_POINTER_HPP_
