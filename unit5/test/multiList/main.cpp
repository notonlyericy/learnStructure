#include <iostream>
#include "../../../list/multiList.h"
#include "util.h"

int main()
{
    titleLine("insert");
    const int total = 10;
    multiList<int> ml = multiList<int>(total, 3);
    ml.insert(3, 0, 9);
    ml.insert(3, 1, 10);
    std::cout << "add 2 elements into table 3 of ml.\n" << ml << std::endl;
    for (int i = 0; i < 7; i++) ml.insert(1, i, i);
    std::cout << "and add 7 elements into tables 1 of ml\n" << ml << std::endl;
    std::cout << "after that, table 2 only has 1 room to store elements.\n";
    ml.insert(2, 0, 7);
    std::cout << ml << std::endl;
    // ml.insert(2, 1, 8); // should be error: out of memory


    titleLine("erase");
    ml.erase(1, 2); // test copy_backward
    std::cout << "move index(2), result is\n" << ml << std::endl;
    ml.erase(1, 2); // test copy_backward
    std::cout << "move index(2), result is\n" << ml << std::endl;
    ml.erase(1, 2); // test copy
    std::cout << "move index(2), result is\n" << ml << std::endl;
    ml.erase(1, 2); // test copy
    std::cout << "move index(2), result is\n" << ml << std::endl;
    ml.erase(1, 0); // test copy
    ml.erase(1, 0); // test copy
    ml.erase(1, 0); // test copy
    std::cout << "erase all elements of table 1, result is\n" << ml << std::endl;

    titleLine("balanced insert");
    multiList<int> bml = multiList<int>(total, 3);
    for (int t = 1; t <= 3; t++)
        for (int ne = 0; ne < 3; ne++) bml.insert(t, ne, t + ne);
    std::cout << bml << std::endl;

    bml.insert(3, 0, 10);
    std::cout << bml << std::endl;

    // bml.insert(2, 3, 10);  // should be error: out of memory
    return 0;
}