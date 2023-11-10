
#ifndef LEARNSTRUCTURE_ARRAYLISTWITHITERATOR_H
#define LEARNSTRUCTURE_ARRAYLISTWITHITERATOR_H

#include <algorithm>
#include <iterator>

#include "linearList.h"
#include "changeLength1D.h"

template <class T>
class arrayListWithIterator : public linearList<T>
{
public:
    // constructor, copy constructor && destructor
    arrayListWithIterator(int initialCapacity = 10);         // constructor
    arrayListWithIterator(const arrayListWithIterator<T> &); // copy constructor
    ~arrayListWithIterator() { delete[] element; };          // destructor

    // ADT functions
    bool empty() const { return listSize == 0; };   // return true if list is empty
    int size() const { return listSize; };          // return the number of elements
    T &get(int theIndex) const;                     // return the element at theIndex
    int indexOf(const T &theElement) const;         // return the index of the first element matched
    void erase(int theIndex);                       // erase the element at theIndex
    void insert(int theIndex, const T &theElement); // insert an element at theIndex
    void output(std::ostream &out) const;           // put the list into out stream

    // iterator
    class iterator;
    iterator begin() { return iterator(element); } // invoke constructor of iterator
    iterator end() { return iterator(element + listSize); }

    class iterator
    {
    public:
        // bidirectional iterator
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef T value_type;
        typedef std::ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T &reference;

        // constructor
        iterator(T *thePosition = 0) { position = thePosition; }

        // dereference
        T &operator*() const { return *position; } // *
        T *operator->() const { return position; } // ->

        // plus
        iterator &operator++() // prev
        {
            ++position;
            return *this;
        }
        iterator operator++(int) // post
        {
            iterator old = *this;
            ++position;
            return old;
        }

        // minus
        iterator &operator--() // prev
        {
            --position;
            return *this;
        }
        iterator operator--(int) // post
        {
            iterator old = *this;
            --position;
            return old;
        }

        // check if equals
        bool operator!=(const iterator right) const { return position != right.position; } // !=
        bool operator==(const iterator right) const { return position == right.position; } // ==

    protected:
        T *position;
    };

protected:
    void checkIndex(int theIndex) const; // throw exception if theIndex is invalid
    T *element;                          // one-dimensional array to store elements
    int arrayLength;                     // capacity of the array
    int listSize;                        // number of the elements
};

template <class T>
arrayListWithIterator<T>::arrayListWithIterator(int initialCapacity)
{
    if (initialCapacity < 1)
    {
        std::ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(s.str());
    }
    arrayLength = initialCapacity;
    element = new T[arrayLength];
    listSize = 0;
}

template <class T>
arrayListWithIterator<T>::arrayListWithIterator(const arrayListWithIterator<T> &theList)
{
    arrayLength = theList.arrayLength;
    listSize = theList.listSize;
    element = new T[arrayLength];
    std::copy(theList.element, theList.element + listSize, element);
}

template <class T>
void arrayListWithIterator<T>::checkIndex(int theIndex) const
{
    if (theIndex < 0 || theIndex >= listSize)
    {
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }
}

template <class T>
T &arrayListWithIterator<T>::get(int theIndex) const
{
    checkIndex(theIndex);
    return element[theIndex];
}

template <class T>
int arrayListWithIterator<T>::indexOf(const T &theElement) const
{
    T *p = std::find(element, element + listSize, theElement);
    int theIndex = p - element;

    // check if there is the theElement
    if (theIndex == listSize)
        return -1; // not found
    else
        return theIndex;
}

template <class T>
void arrayListWithIterator<T>::erase(int theIndex)
{
    checkIndex(theIndex);

    std::copy(element + theIndex + 1, element + listSize, element + theIndex);

    element[--listSize].~T(); // free the last element
}

template <class T>
void arrayListWithIterator<T>::insert(int theIndex, const T &theElement)
{
    if (theIndex < 0 || theIndex > listSize) // differ from normal index check
    {
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }

    // check if array is full
    if (listSize == arrayLength)
    {
        changeLength1D(element, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }

    std::copy_backward(element + theIndex, element + listSize, element + listSize + 1);

    element[theIndex] = theElement;

    listSize++;
}

template <class T>
void arrayListWithIterator<T>::output(std::ostream &out) const
{
    std::copy(element, element + listSize, std::ostream_iterator<T>(out, " "));
}

// overload <<
template <class T>
std::ostream &operator<<(std::ostream &out, const arrayListWithIterator<T> &theArray)
{
    theArray.output(out);
    return out;
}

#endif // LEARNSTRUCTURE_ARRAYLISTWITHITERATOR_H
