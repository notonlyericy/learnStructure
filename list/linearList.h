
#ifndef LEARNSTRUCTURE_LINEARLIST_H
#define LEARNSTRUCTURE_LINEARLIST_H

#include <iostream>
#include <ostream>
#include <sstream>

template<class T>
class linearList
{
public:
    virtual ~linearList() {};
    virtual bool empty() const = 0; // return true if list is empty
    virtual int size() const = 0; // return the number of elements
    virtual T &get(int theIndex) const = 0; // return the element at theIndex
    virtual int indexOf(const T &theElement) const = 0; // return the index of the first element matched
    virtual void erase(int theIndex) = 0; // erase the element at theIndex
    virtual void insert(int theIndex, const T &theElement) = 0; // insert an element at theIndex
    virtual void output(std::ostream &out) const = 0; // put the list into out stream
};

#endif //LEARNSTRUCTURE_LINEARLIST_H
