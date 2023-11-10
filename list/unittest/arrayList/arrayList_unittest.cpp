#include "arrayList.h"
#include "gtest/gtest.h"

template<typename T>
class ArrayListTest : public testing::Test {
protected:
    arrayList<T> al0;
};

typedef ::testing::Types <int, char, float, double> Impl;

TYPED_TEST_SUITE(ArrayListTest, Impl);

TYPED_TEST(ArrayListTest, DefaultConstructor)
{
    EXPECT_EQ(0, this->al0.size());
    EXPECT_TRUE(this->al0.empty());
    EXPECT_EQ(10, this->al0.capacity());
}