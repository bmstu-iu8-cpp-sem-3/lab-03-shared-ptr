// Copyright 2020 Petr Portnov <gh@progrm-jarvis.ru>

#include <gtest/gtest.h>

#include <shared_pointer.hpp>
#include <string>

namespace shared_pointer {

    inline static void assertNotDestroyed(bool const destroyed) {
        if (destroyed) FAIL() << "Destructor has already been called";
    }

    inline static void assertDestroyed(bool const destroyed) {
        if (!destroyed) FAIL() << "Destructor has not been called";
    }

    struct DestructionMonitor {
        /*[[maybe_unused]]*/ bool &destroyed;
        int value;

        ~DestructionMonitor() { destroyed = true; }
    };

    TEST(SharedPointer, Dereference) {
        SharedPointer<std::string> const sharedPointer("Hello world");
        ASSERT_EQ(*sharedPointer, "Hello world");
    }

    TEST(SharedPointer, OperatorBool) {
        ASSERT_FALSE(SharedPointer<int>());
        ASSERT_TRUE(SharedPointer<int>(123));
    }

    TEST(SharedPointer, ConstructorFromVaarg) {
        bool monitor = false;
        {
            SharedPointer<DestructionMonitor> const sharedPointer(monitor, 6274);
            ASSERT_EQ(sharedPointer->value, 6274);
            assertNotDestroyed(monitor);
        }
        assertDestroyed(monitor);
    }

    TEST(SharedPointer, ConstructorFromRaw) {
        bool monitor = false;
        {
            SharedPointer<DestructionMonitor> const sharedPointer(new DestructionMonitor{monitor, 1234});
            ASSERT_EQ(sharedPointer->value, 1234);
            assertNotDestroyed(monitor);
        }
        assertDestroyed(monitor);
    }

    TEST(SharedPointer, MakeShared) {
        bool monitor = false;
        {
            auto const sharedPointer = make_shared<DestructionMonitor>(monitor, 3264);
            ASSERT_EQ(sharedPointer->value, 3264);
            assertNotDestroyed(monitor);
        }
        assertDestroyed(monitor);
    }

    TEST(SharedPointer, CopyConstructor) {
        bool monitor = false;
        {
            SharedPointer<DestructionMonitor> const sharedPointer(new DestructionMonitor{monitor, 1467});
            ASSERT_EQ(sharedPointer->value, 1467);
            {
                SharedPointer<DestructionMonitor> const otherSharedPointer(sharedPointer);
                ASSERT_EQ(sharedPointer->value, 1467);
                ASSERT_EQ(otherSharedPointer->value, 1467);
                assertNotDestroyed(monitor);
            }
            ASSERT_EQ(sharedPointer->value, 1467);
            assertNotDestroyed(monitor);
        }
        assertDestroyed(monitor);
    }

    TEST(SharedPointer, CopyAssignment) {
        bool monitor = false;
        {
            SharedPointer<DestructionMonitor> const sharedPointer(new DestructionMonitor{monitor, 4728});
            ASSERT_EQ(sharedPointer->value, 4728);
            {
                SharedPointer<DestructionMonitor> otherSharedPointer;
                otherSharedPointer = sharedPointer;
                ASSERT_EQ(sharedPointer->value, 4728);
                ASSERT_EQ(otherSharedPointer->value, 4728);
                assertNotDestroyed(monitor);
            }
            ASSERT_EQ(sharedPointer->value, 4728);
            assertNotDestroyed(monitor);
        }
        assertDestroyed(monitor);
    }

    TEST(SharedPointer, MoveConstructor) {
        bool monitor = false;
        {
            SharedPointer<DestructionMonitor> sharedPointer(
                SharedPointer<DestructionMonitor>(new DestructionMonitor{monitor, 6847}));
            ASSERT_EQ(sharedPointer->value, 6847);
            assertNotDestroyed(monitor);
        }
        assertDestroyed(monitor);
    }

    TEST(SharedPointer, MoveAssignment) {
        bool monitor = false;
        {
            SharedPointer<DestructionMonitor> sharedPointer;
            {
                SharedPointer<DestructionMonitor> otherSharedPointer = SharedPointer<DestructionMonitor>(new DestructionMonitor{monitor, 7412});
                sharedPointer = std::move(otherSharedPointer);
                ASSERT_FALSE(otherSharedPointer);
            }
            ASSERT_EQ(sharedPointer->value, 7412);
            assertNotDestroyed(monitor);
        }
        assertDestroyed(monitor);
    }
} // namespace shared_pointer
