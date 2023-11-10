#include <iostream>

#include "../../../list/circularArrayList.h"
#include "util.h"

int main()
{
    titleLine("constructor");
    circularArrayList<int> cArrayList = circularArrayList<int>(10);
    std::cout << "size = " << cArrayList.size() << ", cap = " << cArrayList.capacity() << std::endl;

    titleLine("empty");
    std::cout << "now, list is" << ( cArrayList.empty() ? " " : " not " ) << "empty." << std::endl;

    titleLine("insert");
    int i;
    for ( i = 0; i < 7; i++ ) cArrayList.insert(i, i);
    std::cout << "size = " << cArrayList.size() << ", cap = " << cArrayList.capacity() << std::endl;
    std::cout << "now, arr = " << cArrayList << std::endl;

    titleLine("capacity expansion");
    cArrayList.insert(0, i++);
    std::cout << "insert value at pos(0), arr = " << cArrayList << std::endl;
    cArrayList.insert(8, i++);
    std::cout << "insert value at pos(8), arr = " << cArrayList << std::endl;
    cArrayList.insert(3, i++);
    std::cout << "insert value at pos(3), arr = " << cArrayList << std::endl;
    cArrayList.insert(7, i++);
    std::cout << "insert value at pos(7), arr = " << cArrayList << std::endl;
    std::cout << "size = " << cArrayList.size() << ", cap = " << cArrayList.capacity() << std::endl;

    titleLine("get");
    for ( i = 0; i < cArrayList.size(); i++ ) std::cout << "get(" << i << ") = " << cArrayList.get(i) << std::endl;

    titleLine("indexOf");
    for ( i = 0; i < cArrayList.size(); i++ )
        std::cout << "element " << i << " is at pos(" << cArrayList.indexOf(i) << ")" << std::endl;

    titleLine("copy constructor");
    circularArrayList<int> copyList = circularArrayList<int>(cArrayList);
    std::cout << "copy list from origin list, copy list = " << copyList << std::endl;
    copyList.erase(0);
    std::cout << "remove value at pos(0), copy list = " << copyList << std::endl;
    copyList.erase(9);
    std::cout << "remove value at pos(9), copy list = " << copyList << std::endl;
    std::cout << "origin arr = " << cArrayList << std::endl;

    titleLine("erase");
    circularArrayList<int> arr3 = circularArrayList<int>(10);
    for ( i = 0; i < 10; i++ ) arr3.insert(i, i);
    std::cout << "arr3 = " << arr3 << ", size = " << arr3.size() << std::endl;
    while ( !arr3.empty())
    {
        int p = arr3.size() / 2;
        arr3.erase(p);
        std::cout << "erase pos(" << p << "), arr3 = " << arr3 << ", size = " << arr3.size() << std::endl;
    }


    titleLine("bidirectional_iterator");
    std::cout << "now, back to the origin list: \nlist = ";
    for ( auto &v: cArrayList ) std::cout << v << " ";
    std::cout << "(using for each)\nlist = ";
    for ( circularArrayList<int>::iterator cArrayList_it = cArrayList.begin();
          cArrayList_it != cArrayList.end(); cArrayList_it++ )
        std::cout << *cArrayList_it << " ";;
    std::cout << "(using iterator explicitly in positive order)\nlist = ";
    circularArrayList<int>::iterator cArrayList_it = cArrayList.end();
    do
    {
        std::cout << *( --cArrayList_it ) << " ";
    } while ( cArrayList_it != cArrayList.begin());
    std::cout << "(using iterator explicitly in reverse order)\n";

    circularArrayList<int> arr4 = circularArrayList<int>(10);
    for ( i = 0; i < 10; i++ ) arr4.insert(i, i);
    std::cout << "-------------\nand we have another list arr4, note that arr4 is full.\narr4 = "
              << arr4 << ", size = " << arr4.size() << ", capacity = " << arr4.capacity() << std::endl;

    std::cout << "list = ";
    for (int & arr4_it : arr4) std::cout << arr4_it << " ";
    std::cout << "(using iterator explicitly)\nlist = ";
    circularArrayList<int>::iterator arr4_it_rev = arr4.end();
    do
    {
        std::cout << *(--arr4_it_rev) << " ";
    } while (arr4_it_rev != arr4.begin());
    std::cout << "(using iterator explicitly in reverse order)\n";

    circularArrayList<int> arr5 = circularArrayList<int>(5);
    i = 0;
    for (i = 0; i < 5; i++) arr5.insert(i, i);
    std::cout << "-------------\nand we have third array list, arr5 = " << arr5 << std::endl;
    arr5.erase(1); // [unknown, 0, 1, 3, 4]
    arr5.erase(1); // [unknown, unknown, 0, 3, 4]
    for (int j = 0; j < 2; j++) arr5.insert(arr5.size(), i+j); // [5, 6, 0, 3, 4] => 0 3 4 5 6
    std::cout << "after some operations, last is before first in the array.\narr5 = ";
    for ( circularArrayList<int>::iterator arr5_it = arr5.begin(); arr5_it != arr4.end(); arr5_it++) std::cout << *arr5_it << " ";
    std::cout << "(using iterator explicitly)\narr5 = ";
    circularArrayList<int>::iterator arr5_it_rev = arr5.end();
    do
    {
        std::cout << *(--arr5_it_rev) << " ";
    } while (arr5_it_rev != arr5.begin());
    std::cout << "(using iterator explicitly in reverse order)\n";

    titleLine("reverse");
    arr5.reverse();
    std::cout << "reverse arr5, arr5 = " << arr5 << std::endl;

    titleLine("meld");
    cArrayList.meld(arr4, arr5);
    std::cout << "meld arr4 and arr5, origin array list = " << cArrayList << std::endl;

    titleLine("merge");
    arr5.reverse();
    cArrayList.merge(arr4, arr5);
    std::cout << "merge arr4 and arr5(reverse), origin array list = " << cArrayList << std::endl;

    titleLine("split");
    circularArrayList<int> a, b;
    cArrayList.split(a, b);
    std::cout << "split origin arr into a and b\na = " << a << "\nb = " << b << std::endl;

    return 0;
}
