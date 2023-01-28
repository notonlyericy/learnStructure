#include <iostream>

#include "vectorList.h"
#include "util.h"

int main()
{
    titleLine("half");
    vectorList<int> vl1;
    for (int i = 0; i < 10; i++) vl1.insert(i, i);
    std::cout << "origin: " << vl1 << std::endl;
    vl1.half();
    std::cout << "after half(), vl1 = " << vl1 << std::endl;

    titleLine("meld");
    vectorList<int> vl2, vl3, vl4;
    for (int i = 0; i < 4; i++) vl2.insert(i, i + 1);
    for (int i = 0; i < 8; i++) vl3.insert(i, 2 * i);
    std::cout << "vl2 = " << vl2 << std::endl;
    std::cout << "vl3 = " << vl3 << std::endl;
    vl4.meld(vl2, vl3);
    std::cout << "meld(vl2, vl3), vl4 = " << vl4 << std::endl;

    titleLine("merge");
    vectorList<int> vl5;
    vl5.merge(vl2, vl3);
    std::cout << "vl2 = " << vl2 << std::endl;
    std::cout << "vl3 = " << vl3 << std::endl;
    std::cout << "merge(vl2, vl3), vl5 = " << vl5 << std::endl;

    titleLine("split");
    vectorList<int> vl6, vl7;
    std::cout << "vl4 = " << vl4 << std::endl;
    vl4.split(vl6, vl7);
    std::cout << "split vl4 into vl6 and vl7, vl6 = " << vl6 << "\nvl7 = " << vl7 << std::endl;
    return 0;
}
