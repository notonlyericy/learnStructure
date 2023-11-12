#include "stack.h"
#include "changeLength1D.h"

template <typename T>
class arrayStack : public stack<T>
{
public:
    arrayStack(int initialCapacity = 10);
    ~arrayStack() { delete[] stack; }
    bool empty() const { return stackTop == -1; }
    int size() const { return stackTop + 1; }
    T &top()
    {
        if (stackTop == -1)
            throw stackEmpty();
        return stack[stackTop];
    }
    void pop()
    {
        if (stackTop == -1)
            throw stackEmpty();
        stack[stackTop--].~T();
    }
    void push(const T &theElement);

private:
    int stackTop;
    int arrayLength;
    T *stack;
};

template <typename T>
arrayStack<T>::arrayStack(int initialCapacity)
{
    if (initialCapacity < 1)
    {
        s << "Initial Capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(s.str());
    }
    arrayLength = initialCapacity;
    stack = new T[arrayLength];
    stackTop = -1;
}

template <typename T>
void arrayStack<T>::push(const T &theElement)
{
    if (stackTop == arrayLength - 1)
    {
        changeLength1D(stack, arrayLength, arrayLength * 2);
        arrayLength *= 2;
    }

    stack[++stackTop] = theElement;
}