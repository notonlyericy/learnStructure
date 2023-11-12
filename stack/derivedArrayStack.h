#include "stack.h"
#include "arrayList.h"

template <typename T>
class derivedArrayStack : private arrayList<T>,
                          public stack<T>
{
public:
    derivedArrayStack(int initicalCapaciry = 10)
        : arrayList<T>(initicalCapaciry) {}
    bool empty() const
    {
        return arrayList<T>::empty();
    }
    int size() const
    {
        return arrayList<T>::size();
    }
    T &top()
    {
        try
        {
            return get(arrayList<T>::size() - 1);
        }
        catch (illegalIndex)
        {
            throw stackEmpty();
        }
    }
    void pop()
    {
        try
        {
            erase(arrayList<T>::size() - 1);
        }
        catch (illegalIndex)
        {
            throw stackEmpty();
        }
    }
    void push(const T &theElement)
    {
        insert(arrayList<T>::size(), theElement);
    }
};