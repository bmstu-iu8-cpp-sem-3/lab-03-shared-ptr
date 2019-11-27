#include "SharedPtr.hpp"
#include <gtest/gtest.h>

int main(int argc, char *argv[]) {
    try {
        int number = 100;
        // Create a shared_ptr
        SharedPtr<int> p1;
        SharedPtr<int> p2;
        *p2 = number;
        p1 = p2;
        EXPECT_TRUE(*p1 == *p2);
        EXPECT_TRUE(p1.use_count() == p2.use_count());
    } catch (const std::invalid_argument& e) {
        std::cout << "test failed! " << e.what() << std::endl;
        return 1;
    }
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
//    return 0;
}
