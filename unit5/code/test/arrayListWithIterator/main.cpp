#include <iostream>

#include "arrayListWithIterator.h"
#include "util.h"

int main()
{
    arrayListWithIterator<int> arr = arrayListWithIterator<int>(10);
    arr.insert(0, 1);
    arr.insert(1, 2);
    arr.insert(2, 3);
    arr.insert(2, 4);
    arr.insert(4, 5);

    titleLine("iterator");
    for (arrayListWithIterator<int>::iterator it = arr.begin(); it != arr.end(); it++)
        std::cout << *it << " ";
    std::cout << "\n";
    return 0;
}
