#include <gtest/gtest.h>

namespace {
    struct C {
        int* data;
    };
//
    TEST(shared_ptr, basic_ptr) {
        int number = 100;
        // Create a shared_ptr
        SharedPtr<int> p1;
        SharedPtr<int> p2;
        *p2 = number;
        const SharedPtr<int> &p3(p2);
        SharedPtr<C> obj;
        EXPECT_EQ(1, p1.use_count());
        EXPECT_EQ(2, p2.use_count());
        EXPECT_EQ(2, p3.use_count());
        EXPECT_EQ(1, obj.use_count());
    }
    
    TEST(shared_ptr, no_throw) {
        int number = 1000;
        // Create a shared_ptr
        SharedPtr<int> p1;
        SharedPtr<int> p2;
        *p2 = number;
        SharedPtr<int> p3(p2);
        SharedPtr<C> obj;
        ASSERT_NO_THROW(p1.reset());
        ASSERT_NO_THROW(p2.reset());
        ASSERT_NO_THROW(p3.reset());
        ASSERT_NO_THROW(obj.reset());
    }
    
    TEST(shared_ptr, check_operator) {
        int number = 100;
        // Create a shared_ptr
        SharedPtr<int> p1;
        SharedPtr<int> p2;
        *p2 = number;
        SharedPtr<int> p3(p2);
        EXPECT_EQ(1, p1.use_count());
        EXPECT_EQ(3, p2.use_count());
        EXPECT_EQ(3, p3.use_count());
        p1 = p2;
        p2 = p3;
        EXPECT_EQ(4, p1.use_count());
        EXPECT_EQ(4, p2.use_count());
        EXPECT_EQ(4, p3.use_count());
    }

    TEST(shared_ptr, check_constructor) {
        int number = 100;
        // Create a shared_ptr
        SharedPtr<int> p2;
        *p2 = number;
        SharedPtr<int> p1 = std::move(p2);
        EXPECT_EQ(1, p1.use_count());
        SharedPtr<int> p3(std::move(p1));
        EXPECT_EQ(1, p3.use_count());
    }
}
