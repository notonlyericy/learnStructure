#ifndef LEARNSTRUCTURE_CIRCULARARRAYLIST_H
#define LEARNSTRUCTURE_CIRCULARARRAYLIST_H

#include <iterator>

#include "linearList.h"
#include "myExceptions.h"

template<class T>
class circularArrayList : public linearList<T>
{
public:
    // constructor
    circularArrayList( int initialCapacity = 10);

    circularArrayList( const circularArrayList<T> &theList );

    ~circularArrayList() { delete[]element; }

    // adt
    bool empty() const { return first == -1; } // O(1)

    int size() const
    {
        if (first == -1) return 0;
        return (last + arrayLength - first) % arrayLength + 1;
    } // O(1)

    T &get( int theIndex ) const; // O(1)

    int indexOf( const T &theElement ) const; // O(listSize)

    void insert( int theIndex, const T &theElement ); // O(listSize/2)

    void erase( int theIndex ); // O(listSize/2)

    void reverse(); // O(listSize/2)

    void meld(const circularArrayList<T> &a, const circularArrayList<T> &b); // O(a.listSize+b.listSize) if list is empty

    void merge(const circularArrayList<T> &a, const circularArrayList<T> &b); // O(a.listSize+b.listSize) if list is empty

    void split(circularArrayList<T> &a, circularArrayList<T> &b); // O(listSize) if a and b are empty

    void output( std::ostream &out ) const;

    // other
    int capacity() const { return arrayLength; } // O(1)

    class iterator;
    iterator begin() { return iterator(this, element + first); }
    iterator end()
    {
        int listSize = size();
        int position = getPosition(listSize-1) + 1; // don't use getPosition(listSize). If last is at the end of the array, end() should be next not start of array
        return iterator(this, nullptr);
    }

    class iterator
    {
    public:
        // typedefs
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef value_type &reference;
        typedef value_type *pointer;
        typedef std::bidirectional_iterator_tag iterator_category;

        // constructor
        iterator(circularArrayList<T> *theBuffer, pointer thePosition)
        { buff = theBuffer; position = thePosition; }
        // copy constructor
        iterator(const iterator &it) { buff = it.buff; position = it.position; }
        // copyassignable
        iterator &operator=(const iterator &it) { position = it.position; return *this; }

        // dereferenceable
        reference operator*() const { return *position; }
        const pointer operator->() const { return position; }
        reference operator[](int theIndex) const { return position[theIndex]; }

        // increment / decrement
        iterator &operator++()
        {
            ++position;
            if (position == (buff->element + buff->last + 1)) position = nullptr;
            if (position == buff->border) position = buff->element;
            return *this;
        }
        iterator operator++(int)
        {
            iterator old = *this;
            ++*this; // invoke ++(prefix)
            return old;
        }
        iterator &operator--()
        {
            if (position == nullptr) position = buff->element + buff->last + 1;
            if (position == buff->element) position = buff->border;
            --position;
            return *this;
        }
        iterator operator--(int)
        {
            iterator old = *this;
            --*this;
            return old;
        }

        // comparison operators
        bool operator==(const iterator &it) { return position == it.position; }
        bool operator!=(const iterator &it) { return position != it.position; }

    protected:
        circularArrayList<T> *buff;
        pointer position;
    };

private:
    int getPosition( int theIndex ) const;
    void checkIndex( int theIndex ) const; // throw exception if theIndex is invalid
    void changeLength1D(int newArrayLength);

    int first;
    int last;
    int arrayLength;
    T *border;
    T *element;
};

template<class T>
std::ostream &operator<<( std::ostream &out, circularArrayList<T> theList )
{
    theList.output(out);
    return out;
}

template<class T>
int circularArrayList<T>::getPosition( int offset ) const
{
    return ( first + offset + arrayLength ) % arrayLength;
}

template<class T>
void circularArrayList<T>::changeLength1D(int newArrayLength)
{
    if (newArrayLength < 2 * arrayLength) newArrayLength = 2 * arrayLength;
    T *temp = new T[newArrayLength];
    int listSize = size();
    int j = 0;
    for (int i = 0; i < listSize; i++)
    {
        int p = getPosition(i);
        temp[j++] = element[p];
    }
    delete[]element;
    element = temp;
    arrayLength = newArrayLength;
    first = 0;
    last = j;
    border = element + arrayLength;
}

template<class T>
void circularArrayList<T>::checkIndex( int theIndex ) const
{
    int listSize = size();
    if ( theIndex < 0 || theIndex >= listSize )
    {
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }
}

template<class T>
void circularArrayList<T>::split(circularArrayList<T> &a, circularArrayList<T> &b)
{
    int listSize = size();
    for (int i = 0, ai = 0, bi = 0; i < listSize; i++)
    {
        int sp = getPosition(i);
        if (i % 2 == 0) a.insert(ai++, element[sp]);
        else b.insert(bi++, element[sp]);
    }
}

template<class T>
void circularArrayList<T>::merge(const circularArrayList<T> &a, const circularArrayList<T> &b)
{
    int aList = a.size();
    int bList = b.size();
    int totalSize = aList + bList;
    if (totalSize < arrayLength) changeLength1D(totalSize);
    for (int i = 0, ai = 0, bi = 0; i < totalSize;)
    {
        T ae, be;
        if (ai < aList) ae = a.element[ a.getPosition(ai)];
        if (bi < bList) be = b.element[ b.getPosition(bi)];
        if (ai == aList && bi != bList) { element[i++] = be; bi++; }
        else if (ai != aList && bi == bList) { element[i++] = ae; ai++; }
        else if (ae < be) { element[i++] = ae; ai++; }
        else { element[i++] = be; bi++; }
    }
    first = 0;
    last = getPosition(totalSize - 1);
}

template<class T>
void circularArrayList<T>::meld(const circularArrayList<T> &a, const circularArrayList<T> &b)
{
    int aList = a.size();
    int bList = b.size();
    int totalSize = aList + bList;
    if (totalSize > arrayLength) { changeLength1D(totalSize); }
    for (int i = 0, ai = 0, bi = 0; i < totalSize; )
    {
        if (ai < aList)
        {
            int ap = a.getPosition(ai++);
            element[i++] = a.element[ap];
        }
        if (bi < bList)
        {
            int bp = b.getPosition(bi++);
            element[i++] = b.element[bp];
        }
    }
    first = 0;
    last = getPosition(totalSize-1);
}

template<class T>
void reverse( circularArrayList<T> &theList) { theList.reverse(); }

template<class T>
void circularArrayList<T>::reverse()
{
    int listSize = size();
    int l = 0;
    int r = listSize - 1;
    for (int lp = getPosition(l), rp = getPosition(r); l < r; lp = getPosition(++l), rp = getPosition(--r))
    {
        T t = element[lp];
        element[lp] = element[rp];
        element[rp] = t;
    }
}

template<class T>
void circularArrayList<T>::output( std::ostream &out ) const
{
    int listSize = size();
    std::ostream_iterator<T> oi = std::ostream_iterator<T>(out, " ");
    for (int i = 0; i < listSize; i++)
    {
        int p = getPosition(i);
        oi++ = element[p];
    }
}

template<class T>
void circularArrayList<T>::erase( int theIndex )
{
    checkIndex(theIndex);

    int listSize = size();
    int pos = getPosition(theIndex); // calculate the right position the element should be

    if (listSize == 1) first = last = -1;
    else if (theIndex < listSize / 2) // decide which part to shift according to the position of theIndex
    { // if theIndex is at left part, shift left part
        for (int i = theIndex - 1; i >= 0; i--)
        {
            int sp = getPosition(i);
            int dp = getPosition(i + 1);
            element[dp] = element[sp];
        }
        first = getPosition(1);
    }
    else
    { // if theIndex is at left part, shift left part
        for (int i = theIndex + 1; i < listSize; i++)
        {
            int sp = getPosition(i);
            int dp = getPosition(i-1);
            element[dp] = element[sp];
        }
        last = getPosition(listSize - 2);
    }

    element[pos].~T();
}

template<class T>
void circularArrayList<T>::insert( int theIndex, const T &theElement )
{
    int listSize = size();
    if ( theIndex < 0 || theIndex > listSize )
    {
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }
    if ( listSize == arrayLength ) changeLength1D(2 * arrayLength);

    if (listSize == 0) first = last = 0;
    else if (theIndex <= listSize / 2) // decide which part to shift according to the position of theIndex
    { // if theIndex is at left part, shift left part
        for (int i = 0; i < theIndex; i++)
        {
            int sp = getPosition(i);
            int dp = getPosition(i - 1);
            element[dp] = element[sp];
        }
        first = getPosition(-1);
    }
    else
    { // if theIndex is at left part, shift left part
        for (int i = listSize - 1; i >= theIndex; i--)
        {
            int sp = getPosition(i);
            int dp = getPosition(i + 1);
            element[dp] = element[sp];
        }
        last = getPosition(listSize);
    }

    int pos = getPosition(theIndex); // calculate the right position the element should be
    element[pos] = theElement;
}

template<class T>
int circularArrayList<T>::indexOf( const T &theElement ) const
{
    int listSize = size();
    for ( int i = 0; i < listSize; i++ )
    {
        int position = getPosition(i);
        if ( element[ position ] == theElement ) return i;
    }
    return -1;
}

template<class T>
T &circularArrayList<T>::get( int theIndex ) const
{
    checkIndex(theIndex);
    int position = getPosition(theIndex);
    return element[ position ];
}

template<class T>
circularArrayList<T>::circularArrayList( const circularArrayList<T> &theList )
{
    arrayLength = theList.arrayLength;
    first = theList.first;
    last = theList.last;
    border = theList.border;
    element = new T[arrayLength];
    std::copy(theList.element, theList.element + arrayLength, element);
}

template<class T>
circularArrayList<T>::circularArrayList( int initialCapacity)
{
    if ( initialCapacity < 1 )
    {
        std::ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0.";
        throw illegalParameterValue(s.str());
    }

    arrayLength = initialCapacity;
    first = last = -1;
    element = new T[arrayLength];
    border = element + arrayLength;
}

#endif //LEARNSTRUCTURE_CIRCULARARRAYLIST_H
