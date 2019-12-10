#include <gtest/gtest.h>

#include "SharedPtr.hpp"

TEST(shared_ptr, NullCostructor)
{
    SharedPtr<int> ptr;

    EXPECT_EQ(ptr.get(),nullptr);
    EXPECT_EQ(bool(ptr),false);
    EXPECT_EQ(ptr.use_count(),0);
}

TEST(shared_ptr, ItemInsideCostructor)
{
    SharedPtr ptr(new int{5});

    EXPECT_EQ(*(ptr.get()),5);
    EXPECT_EQ(bool(ptr),true);
    EXPECT_EQ(ptr.use_count(),1);
}

TEST(shared_ptr, PtrInsideCostructor1)
{
    SharedPtr ptr(new int{5});

    SharedPtr ptr2(ptr);

    EXPECT_EQ(*(ptr.get()),*(ptr2.get()));
    EXPECT_EQ(*(ptr.get()),5);

    EXPECT_EQ(bool(ptr),bool(ptr2));
    EXPECT_EQ(bool(ptr),true);

    EXPECT_EQ(ptr.use_count(),ptr2.use_count());
    EXPECT_EQ(ptr.use_count(),2);
}

TEST(shared_ptr, PtrInsideCostructor2)
{
    SharedPtr ptr(new int{5});

    SharedPtr ptr2(std::move(ptr));

    EXPECT_EQ(*(ptr2.get()),5);
    EXPECT_EQ(bool(ptr2),true);
    EXPECT_EQ(ptr2.use_count(),1);
}

TEST(shared_ptr, DeleteTest)
{
    SharedPtr ptr(new int{5});

    SharedPtr ptr2 = ptr;

    EXPECT_EQ(*(ptr.get()),*(ptr2.get()));
    EXPECT_EQ(*(ptr.get()),5);

    EXPECT_EQ(bool(ptr),bool(ptr2));
    EXPECT_EQ(bool(ptr),true);

    EXPECT_EQ(ptr.use_count(),ptr2.use_count());
    EXPECT_EQ(ptr.use_count(),2);

    ptr.~SharedPtr();

    EXPECT_EQ(*(ptr2.get()),5);
    EXPECT_EQ(bool(ptr2),true);
    EXPECT_EQ(ptr2.use_count(),1);
}

TEST(shared_ptr, OperatorPrisvaivania1)
{
    SharedPtr ptr(new int{5});

    SharedPtr ptr2 = ptr;

    EXPECT_EQ(*(ptr.get()),*(ptr2.get()));
    EXPECT_EQ(*(ptr.get()),5);

    EXPECT_EQ(bool(ptr),bool(ptr2));
    EXPECT_EQ(bool(ptr),true);

    EXPECT_EQ(ptr.use_count(),ptr2.use_count());
    EXPECT_EQ(ptr.use_count(),2);
}

TEST(shared_ptr, OperatorPrisvaivania2)
{
    SharedPtr ptr(new int{5});

    SharedPtr ptr2 = std::move(ptr);

    EXPECT_EQ(*(ptr2.get()),5);
    EXPECT_EQ(bool(ptr2),true);
    EXPECT_EQ(ptr2.use_count(),1);
}

TEST(shared_ptr, IntInsideCostructor)
{
    SharedPtr ptr(new int{5});

    EXPECT_EQ(*(ptr.get()),5);
    EXPECT_EQ(bool(ptr),true);
    EXPECT_EQ(ptr.use_count(),1);

    SharedPtr ptr2(ptr);

    EXPECT_EQ(*(ptr2.get()),5);
    EXPECT_EQ(bool(ptr2),true);
    EXPECT_EQ(ptr.use_count(),ptr2.use_count());
    EXPECT_EQ(ptr.use_count(),2);

    ptr.~SharedPtr();

    EXPECT_EQ(*(ptr2.get()),5);
    EXPECT_EQ(bool(ptr2),true);
    EXPECT_EQ(ptr2.use_count(),1);
}

TEST(shared_ptr, OperatorBool)
{
    SharedPtr<int> ptr{};

    EXPECT_EQ(bool(ptr),false);

    SharedPtr ptr2(new int{5});

    EXPECT_EQ(bool(ptr2),true);
}

TEST(shared_ptr, RESET)
{
    SharedPtr ptr{new int{5}};

    ptr.reset();
    EXPECT_EQ(bool(ptr),false);

    ptr.reset(new int{5});
    EXPECT_EQ(*(ptr.get()),5);
    EXPECT_EQ(bool(ptr),true);
    EXPECT_EQ(ptr.use_count(),1);
}

TEST(shared_ptr, SWAP)
{
    SharedPtr ptr{new int{5}};
    SharedPtr ptr2{new int{105}};

    ptr.swap(ptr2);

    EXPECT_EQ(*(ptr2.get()),5);
    EXPECT_EQ(bool(ptr2),true);
    EXPECT_EQ(ptr2.use_count(),1);

    EXPECT_EQ(*(ptr.get()),105);
    EXPECT_EQ(bool(ptr),true);
    EXPECT_EQ(ptr.use_count(),1);
}

TEST(shared_ptr, Count)
{
    int a = rand();
    SharedPtr ptr{new int {a}};
    EXPECT_EQ(ptr.use_count(),1);
}


TEST(shared_ptr, NullCostructor)
{
    SharedPtr<int> ptr;

    EXPECT_EQ(ptr.get(),nullptr);
    EXPECT_EQ(bool(ptr),false);
    EXPECT_EQ(ptr.use_count(),0);
}

TEST(shared_ptr, ItemInsideCostructor)
{
    SharedPtr ptr(new int{5});

    EXPECT_EQ(*(ptr.get()),5);
    EXPECT_EQ(bool(ptr),true);
    EXPECT_EQ(ptr.use_count(),1);
}

TEST(shared_ptr, PtrInsideCostructor1)
{
    SharedPtr ptr(new int{5});

    SharedPtr ptr2(ptr);

    EXPECT_EQ(*(ptr.get()),*(ptr2.get()));
    EXPECT_EQ(*(ptr.get()),5);

    EXPECT_EQ(bool(ptr),bool(ptr2));
    EXPECT_EQ(bool(ptr),true);

    EXPECT_EQ(ptr.use_count(),ptr2.use_count());
    EXPECT_EQ(ptr.use_count(),2);
}

TEST(shared_ptr, PtrInsideCostructor2)
{
    SharedPtr ptr(new int{5});

    SharedPtr ptr2(std::move(ptr));

    EXPECT_EQ(*(ptr2.get()),5);
    EXPECT_EQ(bool(ptr2),true);
    EXPECT_EQ(ptr2.use_count(),1);
}

TEST(shared_ptr, DeleteTest)
{
    SharedPtr ptr(new int{5});

    SharedPtr ptr2 = ptr;

    EXPECT_EQ(*(ptr.get()),*(ptr2.get()));
    EXPECT_EQ(*(ptr.get()),5);

    EXPECT_EQ(bool(ptr),bool(ptr2));
    EXPECT_EQ(bool(ptr),true);

    EXPECT_EQ(ptr.use_count(),ptr2.use_count());
    EXPECT_EQ(ptr.use_count(),2);

    ptr.~SharedPtr();

    EXPECT_EQ(*(ptr2.get()),5);
    EXPECT_EQ(bool(ptr2),true);
    EXPECT_EQ(ptr2.use_count(),1);
}

TEST(shared_ptr, OperatorPrisvaivania1)
{
    SharedPtr ptr(new int{5});

    SharedPtr ptr2 = ptr;

    EXPECT_EQ(*(ptr.get()),*(ptr2.get()));
    EXPECT_EQ(*(ptr.get()),5);

    EXPECT_EQ(bool(ptr),bool(ptr2));
    EXPECT_EQ(bool(ptr),true);

    EXPECT_EQ(ptr.use_count(),ptr2.use_count());
    EXPECT_EQ(ptr.use_count(),2);
}

TEST(shared_ptr, OperatorPrisvaivania2)
{
    SharedPtr ptr(new int{5});

    SharedPtr ptr2 = std::move(ptr);

    EXPECT_EQ(*(ptr2.get()),5);
    EXPECT_EQ(bool(ptr2),true);
    EXPECT_EQ(ptr2.use_count(),1);
}

TEST(shared_ptr, IntInsideCostructor)
{
    SharedPtr ptr(new int{5});

    EXPECT_EQ(*(ptr.get()),5);
    EXPECT_EQ(bool(ptr),true);
    EXPECT_EQ(ptr.use_count(),1);

    SharedPtr ptr2(ptr);

    EXPECT_EQ(*(ptr2.get()),5);
    EXPECT_EQ(bool(ptr2),true);
    EXPECT_EQ(ptr.use_count(),ptr2.use_count());
    EXPECT_EQ(ptr.use_count(),2);

    ptr.~SharedPtr();

    EXPECT_EQ(*(ptr2.get()),5);
    EXPECT_EQ(bool(ptr2),true);
    EXPECT_EQ(ptr2.use_count(),1);
}

TEST(shared_ptr, OperatorBool)
{
    SharedPtr<int> ptr{};

    EXPECT_EQ(bool(ptr),false);

    SharedPtr ptr2(new int{5});

    EXPECT_EQ(bool(ptr2),true);
}

TEST(shared_ptr, RESET)
{
    SharedPtr ptr{new int{5}};

    ptr.reset();
    EXPECT_EQ(bool(ptr),false);

    ptr.reset(new int{5});
    EXPECT_EQ(*(ptr.get()),5);
    EXPECT_EQ(bool(ptr),true);
    EXPECT_EQ(ptr.use_count(),1);
}

TEST(shared_ptr, SWAP)
{
    SharedPtr ptr{new int{5}};
    SharedPtr ptr2{new int{105}};

    ptr.swap(ptr2);

    EXPECT_EQ(*(ptr2.get()),5);
    EXPECT_EQ(bool(ptr2),true);
    EXPECT_EQ(ptr2.use_count(),1);

    EXPECT_EQ(*(ptr.get()),105);
    EXPECT_EQ(bool(ptr),true);
    EXPECT_EQ(ptr.use_count(),1);
}

TEST(shared_ptr, Count)
{
    int a = rand();
    SharedPtr ptr{new int {a}};
    EXPECT_EQ(ptr.use_count(),1);
}