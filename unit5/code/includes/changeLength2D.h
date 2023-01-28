
#ifndef LEARNSTRUCTURE_CHANGELENGTH2D_H
#define LEARNSTRUCTURE_CHANGELENGTH2D_H

#include <algorithm>

#include "myExceptions.h"

template<class T>
void changeLength2D(T **&arr, int oldRows, int *&oldCols, int *&newCols, int newRows)
{
    if (newRows < 0)
        throw illegalParameterValue("number of rows that you want to change Must be >= 0");

    for (int i = 0; i < newRows; i++)
        if (newCols[i] < 0)
            throw illegalParameterValue("number of new column Must be >= 0");

    T **tempArr = new T *[newRows];
    int lines = std::min(oldRows, newRows);
    for (int i = 0; i < lines; i++)
    {
        T *temp = new T[newCols[i]];
        int number = std::min(oldCols[i], newCols[i]);
        std::copy(arr[i], arr[i]+number, temp);
        tempArr[i] = temp;
    }

    for (int i = 0; i < oldRows; i++)
        delete []arr[i];

    delete []arr;
    arr = tempArr;
}


#endif //LEARNSTRUCTURE_CHANGELENGTH2D_H
