#ifndef LEARNSTRUCTURE_ARRAYLIST_H
#define LEARNSTRUCTURE_ARRAYLIST_H

#include <algorithm>
#include <iterator>

#include "linearList.h"
#include "changeLength1D.h"

template<class T>
class arrayList : public linearList<T>
{
public:
    // constructor, copy constructor && destructor
    arrayList( int initialCapacity = 10 );

    arrayList( const arrayList<T> & );

    ~arrayList() { delete[]element; };

    // ADT functions
    bool empty() const { return listSize == 0; }; // return true if list is empty
    int size() const { return listSize; }; // return the number of elements
    T &get( int theIndex ) const; // return the element at theIndex
    int indexOf( const T &theElement ) const; // return the index of the first element matched
    // void erase(int theIndex); // erase the element at theIndex
    void insert( int theIndex, const T &theElement ); // insert an element at theIndex
    void output( std::ostream &out ) const; // put the list into out stream
    int capacity() const { return arrayLength; } // return total capacity

    // homework
    void trimToSize(); // O(listSize)
    void setSize( int size ); // O(max{listSize-size, 0}))
    T &operator[]( int theIndex ) const;

    bool operator==( const arrayList<T> & ) const;

    bool operator!=( const arrayList<T> & ) const;

    bool operator<( const arrayList<T> & ) const;

    void push_pack( const T &theElement ); // 最坏 O(listSize+1) 最好 O(1)
    T &pop_back(); // O(1)
    void swap( arrayList<T> & ); // O(2*listSize+theList.listSize)
    void reserve( int theCapacity );

    void set( int theIndex, const T &theElement );

    void clear(); // O(listSize)
    void removeRange( int start, int end ); // O(min{end, listSize}-max{0, start})
    int lastIndexOf( const T &theElement ) const; // 最坏 O(listSize) 最好 O(1) 平均 O(listSize)
    void erase( int theIndex );

    void reverse(); // Θ(listSize/2)
    void reverse( int left, int right ); // Θ((right-left)/2)
    void leftShift( int theOffset ); // O(max{listSize-theOffset, 0})
    void circularShift( int theOffset ); // O(2*listSize)
    void half(); // O(listSize)
    void meld( const arrayList<T> &a, const arrayList<T> &b ); // O(a.listSize+b.listSize)
    void merge( const arrayList<T> &a, const arrayList<T> &b ); // O(a.listSize+b.listSize)
    void split( arrayList<T> &a, arrayList<T> &b ) const; // O(a.listSize+b.listSize)

    class iterator;

    iterator begin() { return iterator(element); }

    iterator end() { return iterator(element + listSize); }

    class iterator
    {
    public:
        // member typedefs
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef value_type &reference;
        typedef value_type *pointer;
        typedef std::random_access_iterator_tag iterator_category;

        // constructor
        iterator( T *thePosition = 0 ) { position = thePosition; }
        iterator( const iterator &it) { position = it.position; }

        iterator &operator=( const iterator &right )
        {
            position = right.position;
            return *this;
        }

        // Pointer like operators
        reference operator[]( int theIndex ) const { return position[ theIndex ]; }

        reference operator*() const { return *position; }

        const value_type *operator->() const { return position; }

        // Increment / Decrement
        iterator &operator++()
        {
            ++position;
            return *this;
        }

        iterator operator++( int )
        {
            iterator old = *this;
            ++position;
            return old;
        }

        iterator &operator--()
        {
            --position;
            return *this;
        }

        iterator operator--( int )
        {
            iterator old = *this;
            --position;
            return old;
        }

        // Arithmetic
        iterator &operator+=( difference_type off )
        {
            position += off;
            return *this;
        }

        iterator operator+( difference_type off ) const { return iterator(position + off); }

        friend iterator operator+( difference_type off, const iterator &right )
        {
            return iterator(off + right.position);
        }

        iterator &operator-=( difference_type off )
        {
            position -= off;
            return *this;
        }

        iterator operator-( difference_type off ) { return iterator(position - off); }

        difference_type operator-( const iterator &right ) const { return position - right.position; }

        // Comparison operators
        bool operator!=( const iterator &right ) const { return position != right.position; }

        bool operator==( const iterator &right ) const { return position == right.position; }

        bool operator<( const iterator &right ) { return position < right.position; }

        bool operator<=( const iterator &right ) { return position <= right.position; }

        bool operator>( const iterator &right ) { return position > right.position; }

        bool operator>=( const iterator &right ) { return position >= right.position; }


    protected:
        pointer position;
    };

protected:
    void checkIndex( int theIndex ) const; // throw exception if theIndex is invalid
    T *element; // one-dimensional array to store elements
    int arrayLength; // capacity of the array
    int listSize; // number of the elements
    int initialCapacity;
};

template<class T>
arrayList<T>::arrayList( int initialCapacity )
{
    if ( initialCapacity < 1 )
    {
        std::ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(s.str());
    }
    this->initialCapacity = arrayLength = initialCapacity;
    element = new T[arrayLength];
    listSize = 0;
}

template<class T>
arrayList<T>::arrayList( const arrayList<T> &theList )
{
    this->initialCapacity = arrayLength = theList.arrayLength;
    listSize = theList.listSize;
    element = new T[arrayLength];
    std::copy(theList.element, theList.element + listSize, element);
}

template<class T>
void arrayList<T>::checkIndex( int theIndex ) const
{
    if ( theIndex < 0 || theIndex >= listSize )
    {
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }
}

template<class T>
T &arrayList<T>::get( int theIndex ) const
{
    checkIndex(theIndex);
    return element[ theIndex ];
}

template<class T>
int arrayList<T>::indexOf( const T &theElement ) const
{
    T *p = std::find(element, element + listSize, theElement);
    int theIndex = p - element;

    // check if there is the theElement
    if ( theIndex == listSize ) return -1; // not found
    else return theIndex;
}

// template<class T>
// void arrayList<T>::erase(int theIndex)
// {
//     checkIndex(theIndex);
//
//     std::copy(element + theIndex + 1, element + listSize, element + theIndex);
//
//     element[--listSize].~T(); // free the last element to avoid memory leak
// }

template<class T>
void arrayList<T>::insert( int theIndex, const T &theElement )
{
    if ( theIndex < 0 || theIndex > listSize ) // differ from normal index check
    {
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }

    // check if array is full
    if ( listSize == arrayLength )
    {
        changeLength1D(element, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }

    std::copy_backward(element + theIndex, element + listSize, element + listSize + 1);

    element[ theIndex ] = theElement;

    listSize++;
}

template<class T>
void arrayList<T>::output( std::ostream &out ) const
{
    std::copy(element, element + listSize, std::ostream_iterator<T>(out, " "));
}

template<class T>
void arrayList<T>::trimToSize()
{
    int size = std::max(listSize, 1);
    changeLength1D(element, arrayLength, size);
    arrayLength = size;
}

template<class T>
void arrayList<T>::setSize( int size )
{
    if ( size >= listSize ) return;

    for ( int i = size; i < listSize; i++ ) erase(i);
}

template<class T>
T &arrayList<T>::operator[]( int theIndex ) const
{
    checkIndex(theIndex);

    return *( element + theIndex );
}

template<class T>
bool arrayList<T>::operator==( const arrayList<T> &theList ) const
{
    if ( listSize != theList.listSize ) return false;

    for ( int i = 0; i < listSize; i++ )
        if ( *( element + i ) != *( theList.element + i )) return false;
    return true;
}

template<class T>
bool arrayList<T>::operator!=( const arrayList<T> &theList ) const
{
    return !( *this == theList ); // don't simplify, because there is not != member function for arrayList yet
}

template<class T>
bool arrayList<T>::operator<( const arrayList<T> &theList ) const
{
    int size = std::min(listSize, theList.listSize);
    int i;
    for ( i = 0; i < size; i++ )
        if ( *( element + i ) > *( theList.element + i )) return false;
        else if ( *( element + i ) < *( theList.element + i )) return true;

    if ( i == theList.listSize && i <= listSize ) return false;

    return true;
}

template<class T>
void arrayList<T>::push_pack( const T &theElement )
{
    if ( listSize == arrayLength )
    {
        changeLength1D(element, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }

    element[ listSize ] = theElement;

    listSize++;
}

template<class T>
T &arrayList<T>::pop_back()
{
    T &theElement = element[ --listSize ];

    // don't invoke theElement's ~T()
    return theElement;
}

template<class T>
void arrayList<T>::swap( arrayList<T> &theList )
{
    T *temp = new T[listSize];
    std::copy(element, element + listSize, temp);

    if ( arrayLength < theList.listSize )
    {
        int expandLength = 2 * arrayLength < theList.listSize ? theList.listSize : 2 * arrayLength;
        changeLength1D(element, arrayLength, expandLength);
        arrayLength = expandLength;
    }

    int oldListSize = listSize;

    std::copy(theList.element, theList.element + theList.listSize, element);
    listSize = theList.listSize;

    std::copy(temp, temp + oldListSize, theList.element);
    theList.listSize = oldListSize;
}

template<class T>
void arrayList<T>::reserve( int theCapacity )
{
    if ( theCapacity <= arrayLength ) return;

    changeLength1D(element, arrayLength, theCapacity);
    arrayLength = theCapacity;
}

template<class T>
void arrayList<T>::set( int theIndex, const T &theElement )
{
    checkIndex(theIndex);

    element[ theIndex ] = theElement;
}

template<class T>
void arrayList<T>::clear()
{
    while ( listSize > 0 ) element[ --listSize ].~T();
}

/**
 * @param start, end: [start, end)
 */
template<class T>
void arrayList<T>::removeRange( int start, int end )
{
    if ( start <= 0 ) start = 0;
    if ( end > listSize ) end = listSize;

    // move forward
    if ( end < listSize ) std::copy(element + end, element + listSize, element + start);

    // free memory to avoid memory leak
    for ( int i = 0, num = end - start; i < num; i++ ) element[ --listSize ].~T();
}

template<class T>
int arrayList<T>::lastIndexOf( const T &theElement ) const
{
    int i = listSize;
    while ( --i >= 0 )
        if ( element[ i ] == theElement ) break;

    return i;
}

template<class T>
void arrayList<T>::erase( int theIndex )
{
    checkIndex(theIndex);

    std::copy(element + theIndex + 1, element + arrayLength, element + theIndex);
    element[ --listSize ].~T();

    if ( listSize <= arrayLength / 4 )
        changeLength1D(element, arrayLength, std::max(arrayLength / 2, this->initialCapacity));
}

template<class T>
void arrayList<T>::reverse()
{
    reverse(0, listSize - 1);
}

/**
 *
 * @param left, right [left, right]
 */
template<class T>
void arrayList<T>::reverse( int left, int right )
{
    checkIndex(left);
    checkIndex(right);

    left = std::min(left, right);
    right = std::max(left, right);

    T t;
    while ( left < right )
    {
        t = element[ left ];
        element[ left ] = element[ right ];
        element[ right ] = t;
        left++;
        right--;
    }
}

template<class T>
void arrayList<T>::leftShift( int theOffset )
{
    if ( theOffset < 0 )
    {
        std::ostringstream s;
        s << "Offset = " << theOffset << " Must be >= 0";
        throw illegalParameterValue(s.str());
    }

    for ( int i = 0; i < theOffset; i++ ) element[ i ].~T();
    if ( theOffset >= listSize ) listSize = 0;
    else
    {
        for ( int i = theOffset; i < listSize; i++ ) element[ i - theOffset ] = element[ i ];
        listSize -= theOffset;
    }
}

template<class T>
void arrayList<T>::circularShift( int theOffset )
{
    if ( theOffset == 0 || theOffset % listSize == 0 ) return;

    theOffset %= listSize;
    theOffset = ( theOffset + listSize ) % listSize;
    reverse(0, theOffset - 1);
    reverse(theOffset, listSize - 1);
    reverse();
}

template<class T>
void arrayList<T>::half()
{
    if ( listSize == 0 ) return;
    for ( int i = 1; i < listSize; i++ )
    {
        if ( i % 2 ) element[ i ].~T();
        else element[ i / 2 ] = element[ i ];
    }
    listSize = ( listSize + 1 ) / 2;
}

/**
 * @tparam T
 * @param a the first array list
 * @param b the second array list
 *
 * meld append elements from the array a and the array b, because practice28 need time complexity O(a.listSize+b.listSize),
 * so it doesn't clear old elements. Invoke clear() manually if you want.
 */
template<class T>
void arrayList<T>::meld( const arrayList<T> &a, const arrayList<T> &b )
{
    int size = listSize + a.listSize + b.listSize;
    if ( size > arrayLength )
    {
        int newArrayLength = 2 * arrayLength;
        if ( size > newArrayLength ) newArrayLength = size;
        changeLength1D(element, arrayLength, newArrayLength);

    }
    for ( int i = 0, j = 0; i < a.listSize || j < b.listSize; )
    {
        if ( i < a.listSize ) element[ listSize++ ] = a.element[ i++ ];
        if ( j < b.listSize ) element[ listSize++ ] = b.element[ j++ ];
    }
}

template<class T>
void arrayList<T>::merge( const arrayList<T> &a, const arrayList<T> &b )
{
    int size = listSize + a.listSize + b.listSize;
    if ( size > arrayLength )
    {
        int newArrayLength = 2 * arrayLength;
        if ( size > newArrayLength ) newArrayLength = size;
        changeLength1D(element, arrayLength, newArrayLength);

    }
    for ( int i = 0, j = 0; i < a.listSize || j < b.listSize; )
    {
        while ( i < a.listSize && j < b.listSize )
        {
            if ( a.element[ i ] < b.element[ j ] ) element[ listSize++ ] = a.element[ i++ ];
            else element[ listSize++ ] = b.element[ j++ ];
        }
        while ( i < a.listSize ) element[ listSize++ ] = a.element[ i++ ];
        while ( j < b.listSize ) element[ listSize++ ] = b.element[ j++ ];
    }
}

template<class T>
void arrayList<T>::split( arrayList<T> &a, arrayList<T> &b ) const
{
    int aNeedLength = a.listSize + listSize / 2;
    if ( aNeedLength > a.arrayLength )
    {
        int newArrayLength = 2 * a.arrayLength;
        if ( aNeedLength > newArrayLength ) newArrayLength = aNeedLength;
        changeLength1D(a.element, a.arrayLength, newArrayLength);
    }
    int bNeedLength = b.listSize + listSize / 2;
    if ( bNeedLength > b.arrayLength )
    {
        int newArrayLength = 2 * b.arrayLength;
        if ( bNeedLength > newArrayLength ) newArrayLength = bNeedLength;
        changeLength1D(b.element, b.arrayLength, newArrayLength);
    }
    for (int i = 0; i < listSize; i++)
    {
        if (i % 2 == 0) a.element[a.listSize++] = element[i];
        else b.element[b.listSize++] = element[i];
    }
}


// overload <<
template<class T>
std::ostream &operator<<( std::ostream &out, const arrayList<T> &theArray )
{
    theArray.output(out);
    return out;
}

template<typename T>
void reverse( arrayList<T> theList )
{
    theList.reverse();
}

template<typename T>
void reverse( arrayList<T> theList, int left, int right )
{
    theList.reverse(left, right);
}

template<typename T>
void half( arrayList<T> theList )
{
    theList.half();
}

#endif //LEARNSTRUCTURE_ARRAYLIST_H
