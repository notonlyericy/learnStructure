
#ifndef LEARNSTRUCTURE_TITLELINE_H
#define LEARNSTRUCTURE_TITLELINE_H

#include <iostream>
void titleLine(const std::string& message)
{
    std::cout << "\n\033[34m========================'test ";
    std::cout << message;
    std::cout << "'========================\033[0m\n";
}


#include <ctime>
template<typename T>
double timeSpent(T &func, int times)
{
    std::time_t start = std::time(nullptr);
    for (int i = 0; i < times; i++)
        func();
    std::time_t end = std::time(nullptr);
    return std::difftime(end, start);
}
#endif //LEARNSTRUCTURE_TITLELINE_H


