// Copyright 2020 Petr Portnov <gh@progrm-jarvis.ru>

#ifndef INCLUDE_SHARED_POINTER_HPP_
#define INCLUDE_SHARED_POINTER_HPP_

#include <atomic>
#include <memory>
#include <utility>

namespace shared_pointer {

    /* **************************************************** API **************************************************** */

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

    /* ********************************************** Implementations ********************************************** */

    template <typename T>
    void SharedPointer<T>::ControlBlock::acquireStrong_() {
        ++strongRefCount_;
    }

    template <typename T>
    void SharedPointer<T>::ControlBlock::releaseStrong_() {
        if (!--strongRefCount_) {
            delete rawPointer_;
            delete this; // this is legal (!!!)
        }
    }

    template <typename T>
    SharedPointer<T>::ControlBlock::ControlBlock(T* const rawPointer) : rawPointer_(rawPointer), strongRefCount_(1) {}

    template <typename T>
    SharedPointer<T>::SharedPointer() : rawPointer_(nullptr), controlBlock_(nullptr) {}

    template <typename T>
    SharedPointer<T>::SharedPointer(T*&& rawPointer)
        : rawPointer_(rawPointer), controlBlock_(new ControlBlock(rawPointer)) {}

    template <typename T>
    template <typename... ConstructorArguments>
    SharedPointer<T>::SharedPointer(ConstructorArguments&&... constructorArguments)
        : SharedPointer(new T{constructorArguments...}) {}

    // Add a new strong owner
    template <typename T>
    SharedPointer<T>::SharedPointer(const SharedPointer& original)
        : rawPointer_(original.rawPointer_), controlBlock_(original.controlBlock_) {
        if (controlBlock_) controlBlock_->acquireStrong_();
    }

    // Exchange ownership
    template <typename T>
    SharedPointer<T>::SharedPointer(SharedPointer&& original) noexcept
        : rawPointer_(std::exchange(original.rawPointer_, nullptr)),
          controlBlock_(std::exchange(original.controlBlock_, nullptr)) {}

    template <typename T>
    SharedPointer<T>::~SharedPointer() {
        if (auto const controlBlock = controlBlock_) controlBlock->releaseStrong_();
    }

    template <typename T>
    SharedPointer<T>& SharedPointer<T>::operator=(const SharedPointer& other) noexcept {
        if (&other != this) {
            rawPointer_ = other.rawPointer_;
            auto const newControlBlock = other.controlBlock_;
            if (auto oldControlBlock = std::exchange(controlBlock_, newControlBlock)) oldControlBlock->releaseStrong_();
            newControlBlock->acquireStrong_();
        }

        return *this;
    }

    template <typename T>
    SharedPointer<T>& SharedPointer<T>::operator=(SharedPointer&& other) noexcept {
        if (&other != this) {
            std::swap(rawPointer_, other.rawPointer_);
            std::swap(controlBlock_, other.controlBlock_);
        }

        return *this;
    }
    template <typename T>
    SharedPointer<T>::operator bool() const noexcept {
        return rawPointer_;
    }

    template <typename T>
    T& SharedPointer<T>::operator*() const noexcept {
        return *rawPointer_;
    }

    template <typename T>
    T* SharedPointer<T>::operator->() const noexcept {
        return rawPointer_;
    }

    template <typename T, typename... ConstructorArguments>
    SharedPointer<T> make_shared(ConstructorArguments&&... constructorArguments) {
        return SharedPointer<T>(std::forward<ConstructorArguments>(constructorArguments)...);
    }

} // namespace shared_pointer

#endif // INCLUDE_SHARED_POINTER_HPP_
