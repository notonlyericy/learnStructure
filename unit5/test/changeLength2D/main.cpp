#include <iostream>
#include <iterator>

#include "../../../uitls/changeLength2D.h"
#include "util.h"

int main()
{
    const int rows = 10;
    const int cols = 5;
    int **arr = new int *[rows];
    for (int i = 0; i < rows; i++)
    {
        arr[i] = new int[cols];
        for (int j = 0; j < cols; j++)
        {
            arr[i][j] = j;
        }
        std::copy(arr[i], arr[i]+cols, std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }
    std::cout << "rows = " << rows << " cols = " << cols << "\n";

    titleLine("changeLength2D");
    int *oldCols = new int[rows];
    for (int i = 0; i < rows; i++)
        oldCols[i] = cols;

    int newRows = rows/2;
    int *newCols = new int[newRows];
    for (int i = 0; i < newRows; i++)
        newCols[i] = i+1;

    changeLength2D(arr, rows, oldCols, newCols, newRows);

    for (int i = 0; i < newRows; i++)
    {
        std::copy(arr[i], arr[i]+newCols[i], std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }

    // std::cout << arr[newRows][0] << std::endl; // segmentation fault
    return 0;
}