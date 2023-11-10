#ifndef LEARNSTRUCTURE_MULTILIST_H
#define LEARNSTRUCTURE_MULTILIST_H

#include <iostream>
#include <iterator>

#include "linearList.h"
#include "../uitls/myExceptions.h"

template<class T>
class multiList
{
    enum direction { LEFT, RIGHT };
public:
    multiList( int initialCapacity = 10, int nTable = 2 );

    multiList( const multiList<T> &theList );

    ~multiList()
    {
        delete[]element;
        delete[]front;
        delete[]last;
    }

    void insert( int i, int theIndex, const T &theElement );

    void balanceInsert( int i, int theIndex, const T &theElement );

    void erase( int i, int theIndex);

    void output( std::ostream &out );

private:
    void checkIndex( int i, int theIndex );

    void checkTable( int i );

    // void changeLength1D(direction dir);
    T *element;
    int *front;
    int *last;
    int tableNumber;
    int arrayLength;
    int free;
};

// template<class T>
// void multiList<T>::changeLength1D(direction dir)
// {
//     T *temp = new T[ 2 * arrayLength];
//     switch ( dir )
//     {
//         case LEFT:
//             std::copy(element, element + arrayLength, temp + arrayLength);
//             for (int i = 1; i <= tableNumber+1; i++)
//             { front[i] += arrayLength; last[i] += arrayLength;}
//             break;
//         case RIGHT:
//             std::copy(element,element + arrayLength, temp);
//             front[tableNumber+1] = last[tableNumber+1] = 2 * arrayLength - 1;
//             break;
//     }
//
//     delete []element;
//     element = temp;
//     arrayLength *= 2;
// }

template<class T>
void multiList<T>::checkTable( int i )
{
    if ( i <= 0 || i >= tableNumber + 1 )
    {
        std::ostringstream s;
        s << "table number = " << i << " total number of table = " << tableNumber;
        throw illegalParameterValue(s.str());
    }
}

template<class T>
void multiList<T>::checkIndex( int i, int theIndex )
{
    int size = last[ i ] - front[ i ];
    if ( theIndex < 0 || theIndex >= size )
    {
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << size;
        throw illegalIndex(s.str());
    }
}

template<class T>
std::ostream &operator<<( std::ostream &out, multiList<T> &theList )
{
    theList.output(out);
    return out;
}

template<class T>
void multiList<T>::output( std::ostream &out )
{
    for ( int i = 1; i <= tableNumber; i++ )
    {
        out << "list" << i << " = ";
        for ( T *t = element + front[ i ] + 1; t != element + last[ i ] + 1; t++ ) out << *t << " ";
        out << std::endl;
    }
}

template<class T>
void multiList<T>::erase( int i, int theIndex )
{
    checkTable(i);
    checkIndex(i, theIndex);

    int size = last[i] - front[i];
    int erasePoint = front[i] + 1 + theIndex;
    if (theIndex < size / 2)
    {
        std::copy_backward(element + front[i] + 1, element + erasePoint, element + erasePoint + 1);
        front[i]++;
    }
    else
    {
        std::copy(element + erasePoint + 1, element + last[i] + 1, element + erasePoint);
        last[i]--;
    }

    free++;
}

template<class T>
void multiList<T>::balanceInsert( int i, int theIndex, const T &theElement )
{
    checkTable(i);
    int size = last[ i ] - front[ i ];
    if ( theIndex < 0 || theIndex > size )
    {
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << size;
        throw illegalIndex(s.str());
    }

    // If there is no need to shift tables
    if ( last[ i ] < front[ i + 1 ] )
    {
        int end = last[i] + 1;
        std::copy_backward(element + front[ i ] + 1 + theIndex, element + end,
                           element + end + 1);
        free--;
        return;
    }
    if (front[i] > last[i-1])
    {
        std::copy(element + front[i] + 1, element + front[i] + theIndex, element + front[i]);
        free--;
        return;
    }

    // if it's necessary to shift tables, balance available space for tables
    int avgFrSpc = (free - 1) / tableNumber;
    int lBorder = last[0], rBorder = front[tableNumber + 1];
    for (int tn = 1; tn < tableNumber; ) // if available space of table 1~(tableNumber-1) are enough, left space is enough for tableNumber
    {
        int lFrSpc = front[i] - lBorder;
        if (lFrSpc >= avgFrSpc)
        {
            int needMove = lFrSpc - avgFrSpc;
            std::copy(element + front[i] + 1, element + last[i] + 1, element + front[i] + 1 - needMove);
            front[i] -= needMove;
            last[i] -= needMove;
            lBorder = last[i];
            tn++;
            continue;
        }
        int rFrSpc = avgFrSpc - lFrSpc;
        int rLftSpc = front[i+1] - last[i];
        if (rFrSpc <= rLftSpc)
        { lBorder = last[i] + rFrSpc; tn++; continue; }

        // if there are not enough space for table i, check if right part of array has lots of space and shift them
        for (int j = tn; j <= tableNumber; j++)
        {
            if (front[j + 1] - last[j] >= rFrSpc)
            {
                int needMove = rFrSpc - rLftSpc;
                int end = last[j] + 1;
                std::copy_backward(element + front[tn] + 1, element + end, element + end + needMove);
                while (j >= tn)
                {
                    front[j] += needMove;
                    last[j] += needMove;
                    j--;
                }
                break;
            }
        }
    }

    insert(i, theIndex, theElement);
}

template<class T>
void multiList<T>::insert( int i, int theIndex, const T &theElement )
{
    checkTable(i);
    int size = last[ i ] - front[ i ];
    if ( theIndex < 0 || theIndex > size )
    {
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << size;
        throw illegalIndex(s.str());
    }

    if (free == 0) throw outOfMemory();

    int start = front[ i ] + 1 + theIndex;
    for ( int j = i; j <= tableNumber; j++ )
    {
        if ( last[ j ] < front[ j + 1 ] )
        {
            int end = last[j] + 1;
            std::copy_backward(element + start, element + end, element + end + 1);
            element[ start ] = theElement;
            while ( j > i )
            {
                front[ j ]++;
                last[ j ]++;
                j--;
            }
            last[ i ]++;
            free--;
            return;
        }
    }
    int end = front[ i ] + theIndex + 1;
    for ( int j = i; j >= 1; j-- )
    {
        if ( front[ j ] > last[ j - 1 ] )
        {
            std::copy(element + front[ j ] + 1, element + end, element + front[ j ]);
            element[ end ] = theElement;
            while ( j < i )
            {
                front[ j ]--;
                last[ j ]--;
                j++;
            }
            front[ i ]--;
            free--;
            return;
        }
    }
}

template<class T>
multiList<T>::multiList( const multiList<T> &theList )
{
    free = theList.free;
    arrayLength = theList.arrayLength;
    T *tElement = new T[arrayLength];
    std::copy(theList.element, theList.element + arrayLength, tElement);
    tableNumber = theList.tableNumber;
    int *tFront = new int[tableNumber + 2];
    int *tLast = new int[tableNumber + 2];
    std::copy(theList.front, theList.front + tableNumber + 2, tFront);
    std::copy(theList.last, theList.last + tableNumber + 2, tLast);
    delete[]element;
    delete[]front;
    delete[]last;
    element = tElement;
    front = tFront;
    last = tLast;
}

template<class T>
multiList<T>::multiList( int initialCapacity, int nTable )
{
    if ( initialCapacity < 0 )
    {
        std::ostringstream s;
        s << "initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(s.str());
    }
    if ( nTable < 0 )
    {
        std::ostringstream s;
        s << "initial table number = " << nTable << " Must be > 0";
        throw illegalParameterValue(s.str());
    }
    free = arrayLength = initialCapacity;
    element = new T[arrayLength];
    tableNumber = nTable;
    front = new int[tableNumber + 2];
    last = new int[tableNumber + 2];
    front[ 0 ] = last[ 0 ] = -1;
    front[ tableNumber + 1 ] = last[ tableNumber + 1 ] = arrayLength - 1;
    int avg = arrayLength / tableNumber;
    for ( int i = 1; i <= tableNumber; i++ )
    {
        front[ i ] = last[ i ] = ( i - 1 ) * avg - 1;
    }
}

# endif // LEARNSTRUCTURE_MULTILIST_H