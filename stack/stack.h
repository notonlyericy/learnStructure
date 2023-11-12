#ifndef LEARNSTRUCTURE_STACK_H
#define LEARNSTRUCTURE_STACK_H

template <typename T>
class stack
{
public:
    virtual ~stack() {}

    virtual bool empty() const = 0;

    virtual int size() const = 0;

    virtual T &top() = 0;

    virtual void pop() = 0;

    virtual void push(const T &theElement) = 0;
};

#endif // LEARNSTRUCTURE_STACK_H