
#ifndef LEARNSTRUCTURE_CHANGELENGTH1D_H
#define LEARNSTRUCTURE_CHANGELENGTH1D_H

#include <algorithm>

#include "myExceptions.h"

template<class T>
void changeLength1D(T *&a, int oldLength, int newLength)
{
    if (newLength < 0)
        throw illegalParameterValue("new length must be >= 0");

    T *temp = new T[newLength];
    int number = std::min(oldLength, newLength);
    std::copy(a, a + number, temp);
    delete []a;
    a = temp;
}

#endif //LEARNSTRUCTURE_CHANGELENGTH1D_H
