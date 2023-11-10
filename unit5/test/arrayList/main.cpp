#include <iostream>
#include <functional>
#include <cstdlib>

#include "../../../list/arrayList.h"
#include "util.h"
#include "../../../list/arrayListWithIterator.h"

#include <gtest/gtest.h>

class ArrayListTest : public testing::Test {
protected:
    void SetUp() override
    {
        a1 = arrayList<int>(10);
    }

    static constexpr int initialCapacity = 10;

    arrayList<int> a0;
    arrayList<int> a1;
    arrayList<int> a2;
};

TEST_F(ArrayListTest, DefaultConstructor)
{
    EXPECT_EQ(0, a0.size());
}

TEST_F(ArrayListTest, CopyConstructor)
{
    EXPECT_EQ(initialCapacity, a1.size());
}


int testTrimToSize();
int testSetSize();
int testOverload();
int testPart2();
int testReverse();
int testLeftShift();
int testCircularShift();
int testHalf();
int testRandomIterator();
int testMeld();
int testMerge();
int split();

int main()
{
    titleLine("constructor");
    arrayList<int> arr = arrayList<int>(10);
    std::cout << "init a arrayList, size = " << arr.size() << "\n";

    titleLine("empty");
    std::cout << "arrayList is " << (arr.empty() ? "" : "not ") << "empty\n";

    titleLine("insert");
    arr.insert(0, 1);
    arr.insert(1, 2);
    arr.insert(2, 3);
    arr.insert(2, 4);
    arr.insert(4, 5);
    std::cout << "insert 1, 2, 4, 3, 5 into arrayList\n";
    std::cout << "arrayList.output: " << arr << "\n";

    titleLine("size");
    std::cout << "there should be 5 numbers.\n";
    std::cout << "arrayList' size is " << arr.size();

    titleLine("erase");
    arr.erase(0);
    std::cout << "move 0 from arrayList\n";
    std::cout << "arrayList.output: " << arr << "\n";

    titleLine("get");
    std::cout << "get the element(index = 0): " << arr.get(0) << "\n";

    titleLine("indexOf");
    arr.insert(4, 3);
    std::cout << "after insert 3 into arrayList, now arrayList is " << arr << "\n";
    std::cout << "element(3)' index is " << arr.indexOf(3) << "\n";

    titleLine("copy constructor");
    arrayList<int> arr1 = arrayList<int>(arr);
    std::cout << "arr1.output: " << arr1 << "\n";

    testTrimToSize();
    testSetSize();
    testOverload();

    testPart2();

    // testReverse();

    testLeftShift();

    testCircularShift();

    testHalf();

    testRandomIterator();

    testMeld();

    testMerge();

    split();

    return 0;
}

int testTrimToSize()
{
    titleLine("trimToSize");
    arrayList<int> arr = arrayList<int>(2);
    std::cout << "initial capacity = " << arr.capacity() << "\n";
    arr.insert(0, 'a');
    arr.insert(1, 'b'); // full
    arr.insert(2, 'c'); // expand to 4
    std::cout << "after insert 3 characters, capacity = " << arr.capacity() << "\n";
    arr.trimToSize(); // trim to 3
    std::cout << "after using trimToSize, capacity = " << arr.capacity() << "\n";
    return 0;
}

int testSetSize()
{
    titleLine("setSize");
    arrayList<char> arr = arrayList<char>(5);
    arr.insert(0, 'a');
    arr.insert(1, 'b');
    arr.insert(2, 'c');
    std::cout << "arr is " << arr << "\n";
    arr.setSize(5);
    std::cout << "use setSize(5), arr is " << arr << "\n";
    arr.setSize(2);
    std::cout << "use setSize(2), arr is " << arr << "\n";
    return 0;
}

int testOverload()
{
    titleLine("[]");
    arrayList<char> arr = arrayList<char>(5);
    arr.insert(0, 'a');
    arr.insert(1, 'b');
    arr.insert(2, 'c');

    std::cout << "arr = ";
    for (int i = 0; i < 3; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;

    arr[0] = 'f';
    arr[1] = 'g';
    std::cout << "set arr[0] = 'f', arr[1] = 'g', arr = ";
    for (int i = 0; i < 3; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;

    char ch = arr[2];
    std::cout << ch << std::endl;

    // std::cout << arr[3] << std::endl; // illegal index

    titleLine("==");
    arrayList<char> arr1 = arrayList<char>(10);
    arr1.insert(0, 'f');
    arr1.insert(1, 'g');
    arr1.insert(2, 'c');
    std::cout << "arr1 = " << arr1 << "\n";
    std::cout << "arr" << (arr == arr1 ? " == " : " != ") << "arr1\n";

    titleLine("!=");
    arrayList<char> arr2 = arrayList<char>(10);
    arr2.insert(0, 'f');
    arr2.insert(1, 'g');
    arr2.insert(2, 'a');
    std::cout << "arr2 = " << arr2 << "\n";
    std::cout << "arr" << (arr == arr2 ? " == " : " != ") << "arr2\n";

    titleLine("<");
    std::cout << "arr2" << (arr2 < arr ? " < " : " >= ") << "arr\n";
    arr2.erase(2);
    std::cout << "erase(2) from arr2, arr2 = " << arr2 << "\n";
    std::cout << "arr2" << (arr2 < arr ? " < " : " >= ") << "arr\n";
    arr2.insert(2, 'd');
    std::cout << "insert(2,d) into arr2, arr2 = " << arr2 << "\n";
    std::cout << "arr2" << (arr2 < arr ? " < " : " >= ") << "arr\n";
    return 0;
}

int testPart2()
{
    // 11~18
    arrayList<int> arr = arrayList<int>(10);
    std::cout << "Now, arr is " << (arr.empty() ? "" : "not") << " empty.\n";
    titleLine("push_back");
    for (int i = 0; i < 9; i++)
        arr.push_pack(i);
    std::cout << "Now, arr is " << arr << "\n";

    titleLine("pop_back");
    std::cout << "pop ";
    for (int i = 0; i < 6; i++)
        std::cout << arr.pop_back() << " ";
    std::cout << "from arr, now arr is\n" << arr << "\n";

    arrayList<int> theList = arrayList<int>(15);
    for (int i = 14; i >= 0; i--)
        theList.push_pack(i);
    std::cout << "theList has " << theList << "\n";

    titleLine("swap");
    arr.swap(theList);
    std::cout << "after swap arr and theList,\narr has " << arr << "\ntheList has " << theList << "\n";

    titleLine("reserve");
    std::cout << "before reserving arr, arr's capacity = " << arr.capacity() << "\n";
    arr.reserve(arr.capacity() + 2);
    std::cout << "set new cap = old cap + 2, now arr's capacity = " << arr.capacity() << "\n";

    titleLine("set");
    arr.set(0, 1);
    std::cout << "set element to 1 at index 0, arr[0] = " << arr.get(0) << "\n";

    titleLine("lastIndexOf");
    std::cout << "last 1 is at index " << arr.lastIndexOf(1) << " in arr\n";

    titleLine("removeRange");
    std::cout << "There are " << arr.size() << " element(s) in arr, they are " << arr << ", now remove the second half part from arr\n";
    arr.removeRange(arr.size()/2, arr.size());
    std::cout << "There are " << arr.size() << " element(s) in arr: " << arr << "\n";

    titleLine("clear");
    arr.clear();
    std::cout << "clear arr, arr is " << (arr.empty() ? "" : "not") << " empty.\n";
    return 0;
}

int testReverse()
{
    titleLine("reverse");
    const int total = 500000;
    arrayList<int> arr = arrayList<int>(total);
    arr.insert(0,0);
    arr.insert(1,1);
    arr.insert(2,2);
    arr.insert(3,3);
    arr.insert(4,4);
    arr.reverse();
    std::cout << arr << std::endl;
    arr.clear();

    int i = 0;
    int end = 5;
    while (end <= total)
    {
        while (i < end)
        {
            arr.insert(i, i);
            i++;
        }
        auto f = std::bind(static_cast<void(arrayList<int>::*)(void)>(&arrayList<int>::reverse), arr);
        std::cout << "n = " << i << ", 耗时: " << timeSpent(f, 10000000) << "s." << std::endl;
        // time_t start = time(nullptr);
        //     for (int j = 0; j < 10000000; j++)
        //         arr.reverse();
        //     std::cout << "n = " << i << ", 耗时: " << std::difftime(time(nullptr), start) << std::endl;
        end *= 10;
    }
    return 0;
}

int testLeftShift()
{
    titleLine("leftShift");
    arrayList<int> arr = arrayList<int>(10);
    for (int i = 0; i < 10; i++) arr.insert(i, i);
    std::cout << "origin arr: " << arr << std::endl;
    arr.leftShift(0);
    std::cout << "leftShift(0), arr: " << arr << std::endl;
    arr.leftShift(3);
    std::cout << "leftShift(3), arr: " << arr << std::endl;
    arr.leftShift(7);
    std::cout << "leftShift(7), arr: " << arr << std::endl;
    return 0;
}

int testCircularShift()
{
    titleLine("circularShift");
    arrayList<int> arr = arrayList<int>(10);
    for (int i = 0; i < 10; i++) arr.insert(i, i);
    std::cout << "origin arr: " << arr << std::endl;
    arr.circularShift(0);
    std::cout << "circularShift(0), arr: " << arr << std::endl;
    arr.circularShift(3);
    std::cout << "circularShift(3), arr: " << arr << std::endl;
    arr.circularShift(7);
    std::cout << "circularShift(7), arr: " << arr << std::endl;
    return 0;
}

int testHalf()
{
    titleLine("half");
    arrayList<int> arr = arrayList<int>(10);
    for (int i = 0; i < 10; i++) arr.insert(i, i);
    std::cout << "origin arr: " << arr << ", size = " << arr.size() << std::endl;
    arr.half();
    std::cout << "half once, arr: " << arr << ", size = " << arr.size() << std::endl;
    arr.half();
    std::cout << "half twice, arr: " << arr << ", size = " << arr.size() << std::endl;
    arr.half();
    std::cout << "half thrice, arr: " << arr << ", size = " << arr.size() << std::endl;
    return 0;
}

int testRandomIterator()
{
    titleLine("random iterator");
    std::srand (time(nullptr));
    arrayList<int> arr = arrayList<int>(10);
    for (int i = 0; i < 10; i++) arr.insert(i, std::rand() % 100);
    std::cout << "origin arr: " << arr << std::endl;
    std::sort(arr.begin(), arr.end());
    std::cout << "sorted arr: " << arr << std::endl;
    return 0;
}

int testMeld()
{
    titleLine("meld");
    arrayList<int> a = arrayList<int>(10);
    arrayList<int> b = arrayList<int>(15);
    for (int i = 0; i < 10; i++) a.insert(i, i);
    for (int i = 0; i < 15; i++) b.insert(i, i+10);
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    arrayList<int> c;
    c.meld(a, b);
    std::cout << "c: " << c << std::endl;
    return 0;
}

int testMerge()
{
    titleLine("merge");
    arrayList<int> a = arrayList<int>(10);
    arrayList<int> b = arrayList<int>(10);
    for (int i = 0; i < 10; i++) a.insert(i, 2*i);
    for (int i = 0; i < 10; i++) b.insert(i, 3*i);
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    arrayList<int> c;
    c.merge(a, b);
    std::cout << "c: " << c << std::endl;
    return 0;
}

int split()
{
    titleLine("split");
    arrayList<int> origin = arrayList<int>(10);
    arrayList<int> a, b;
    for (int i = 0; i < 10; i++) origin.insert(i, i);
    origin.split(a, b);
    std::cout << "origin: " << origin << std::endl;
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    return 0;
}