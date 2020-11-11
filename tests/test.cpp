// Copyright 2020 Siver Elisey <sivereliseu7@gmail.com>

#include <gtest/gtest.h>

#include <string>

#include "SharedPtr.h"

struct monitor {
  bool &bool_;
  int value;

  ~monitor() { bool_ = true; }
};

TEST(SharedPtr, Bool) {
  SharedPtr<int> ptr1;
  SharedPtr<int> ptr2(new int(5));
  ASSERT_TRUE(!ptr1);
  ASSERT_TRUE(ptr2);
}

TEST(SharedPtr, Dereference) {
  std::string* str = new std::string("Hello");
  const SharedPtr<std::string> sharedPointer(str);
  ASSERT_EQ(*sharedPointer, "Hello");
}

TEST(SharedPtr, Constructor1) {
  bool bool_ = false;
  {
    const SharedPtr<monitor> shared(new monitor{bool_, 5});
    ASSERT_EQ(shared->value, 5);
    ASSERT_FALSE(bool_);
  }
  ASSERT_TRUE(bool_);
}

TEST(SharedPointer, CopyConstructor) {
  bool bool_ = false;
  {
    const SharedPtr<monitor> shared(new monitor{bool_, 5});
    ASSERT_EQ(shared->value, 5);
    {
      const SharedPtr<monitor> shared2(shared);
      ASSERT_EQ(shared->value, 5);
      ASSERT_EQ(shared2->value, 5);
      ASSERT_FALSE(bool_);
    }
    ASSERT_EQ(shared->value, 5);
    ASSERT_FALSE(bool_);
  }
  ASSERT_TRUE(bool_);
}

TEST(SharedPointer, Move) {
  bool bool_ = false;
  {
    SharedPtr<monitor> shared;
    {
      SharedPtr<monitor> shared2 = SharedPtr<monitor>(new monitor{bool_, 5});
      shared = std::move(shared2);
      ASSERT_FALSE(shared2);
    }
    ASSERT_EQ(shared->value, 5);
    ASSERT_FALSE(bool_);
  }
  ASSERT_TRUE(bool_);
}

TEST(SharedPointer, Moveconstructor) {
  bool bool_ = false;
  {
    SharedPtr<monitor> shared(SharedPtr<monitor>(new monitor{bool_, 1234}));
    ASSERT_EQ(shared->value, 1234);
    ASSERT_FALSE(bool_);
  }
  ASSERT_TRUE(bool_);
}

TEST(SharedPtr, Copy) {
  bool bool_ = false;
  {
    SharedPtr<monitor> shared(new monitor{bool_, 5});
    ASSERT_EQ(shared->value, 5);
    {
      SharedPtr<monitor> shared2;
      shared2 = shared;
      ASSERT_EQ(shared->value, 5);
      ASSERT_EQ(shared2->value, 5);
      ASSERT_FALSE(bool_);
    }
    ASSERT_EQ(shared->value, 5);
    ASSERT_FALSE(bool_);
  }
  ASSERT_TRUE(bool_);
}
