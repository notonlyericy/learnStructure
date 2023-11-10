
#ifndef ARRAYLIST_VERTORLIST_H
#define ARRAYLIST_VERTORLIST_H

#include <vector>
#include <iterator>

#include "linearList.h"
#include "../uitls/myExceptions.h"

template<class T>
class vectorList : public linearList<T>
{
public:
    vectorList(int initialCapacity = 10);
    vectorList(const vectorList<T> &);
    ~vectorList(){ delete element; }

    bool empty() const { return element->empty();}
    int size() const { return (int)element->size(); }
    T &get(int theIndex) const;
    int indexOf(const T &theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T &theElement);
    void output(std::ostream &out) const;
    void half();
    void meld(const vectorList<T> &a, const vectorList<T> &b);
    void merge(const vectorList<T> &a, const vectorList<T> &b);
    void split(vectorList<T> &a, vectorList<T> &b);

    int capacity() const { return (int)element->capacity(); }

    typedef typename std::vector<T>::iterator iterator;
    iterator begin() { return element->begin(); }
    iterator end() { return element->end(); }

protected:
    void checkIndex(int theIndex) const;
    std::vector<T> *element;
};

template<class T>
void vectorList<T>::split(vectorList<T> &a, vectorList<T> &b)
{
    int listSize = size();
    for (int i = 0; i < listSize; i++)
    {
        if (i % 2 == 0) a.element->push_back((*element)[i]);
        else b.element->push_back((*element)[i]);
    }
}

template<class T>
void vectorList<T>::merge(const vectorList<T> &a, const vectorList<T> &b)
{
    int ai, bi;
    for (ai = 0, bi = 0; ai < a.size() && bi < b.size();)
    {
        if ((*a.element)[ai] < (*b.element)[bi]) { element->push_back((*a.element)[ai]); ai++; }
        else { element->push_back((*b.element)[bi]); bi++; }
    }
    while (ai < a.size()) element->push_back((*a.element)[ai++]);
    while (bi < b.size()) element->push_back((*b.element)[bi++]);
}

template<class T>
void vectorList<T>::meld(const vectorList<T> &a, const vectorList<T> &b)
{
    int totalSize = a.size() + b.size();
    for (int i = 0, ai = 0, bi = 0; i < totalSize; )
    {
        if (ai < a.size()) { element->push_back((*a.element)[ai]); i++; ai++; }
        if (bi < b.size()) { element->push_back((*b.element)[bi]); i++; bi++; }
    }
}

template<class T>
void vectorList<T>::half()
{
    int listSize = size();
    int i;
    for (i = 1; 2 * i < listSize; i++) (*element)[i] = (*element)[2 * i];
    element->resize(i);
}

template<class T>
void vectorList<T>::checkIndex( int theIndex ) const
{
    int listSize = element->size();
    if (theIndex < 0 || theIndex >= listSize)
    {
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }
}

template<class T>
std::ostream &operator<<(std::ostream &out, const vectorList<T> &theList)
{
    theList.output(out);
    return out;
}

template<class T>
void vectorList<T>::output( std::ostream &out ) const
{
    std::copy(element->begin(), element->end(), std::ostream_iterator<T>(out, " "));
}

template<class T>
void vectorList<T>::insert( int theIndex, const T &theElement )
{
    int listSize = element->size();
    if (theIndex < 0 || theIndex > listSize)
    {
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }
    element->insert(begin() + theIndex, theElement);
}

template<class T>
void vectorList<T>::erase( int theIndex )
{
    checkIndex(theIndex);
    element->erase(begin() + theIndex);
}

template<class T>
int vectorList<T>::indexOf(const T &theElement) const
{
    int listSize = element->size();
    for (int i = 0; i < listSize; i++) if ( (*element)[ i ] == theElement ) return i;
    return -1;
}

template<class T>
T &vectorList<T>::get(int theIndex) const
{
    checkIndex(theIndex);
    return (*element)[theIndex];
}

template<class T>
vectorList<T>::vectorList( const vectorList<T> &theList) { element = new std::vector<T>(*theList.element); }

template<class T>
vectorList<T>::vectorList( int initialCapacity )
{
    if (initialCapacity < 1)
    {
        std::ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(s.str());
    }

    element = new std::vector<T>;
    element->reserve(initialCapacity);
}
#endif //ARRAYLIST_VERTORLIST_H
