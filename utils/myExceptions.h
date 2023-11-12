#ifndef LEARNSTRUCTURE_MYEXCEPTIONS_H
#define LEARNSTRUCTURE_MYEXCEPTIONS_H

#include <string>

class illegalParameterValue
{
public:
    illegalParameterValue(std::string theMessage = "Illegal parameter value") { message = theMessage; }
    void outputMessage() { std::cout << message << std::endl; }

private:
    std::string message;
};

class illegalIndex
{
public:
    illegalIndex(std::string theMessage = "Illegal index") { message = theMessage; }
    void outputMessage() { std::cout << message << std::endl; }

private:
    std::string message;
};

class outOfMemory
{
public:
    outOfMemory(std::string theMessage = "Out of memory") { message = theMessage; }
    void outputMessage() { std::cout << message << std::endl; }

private:
    std::string message;
};

class stackEmpty
{
public:
    stackEmpty(std::string theMessage = "Stack is emtpy") { message = theMessage; }
    void outputMessage() { std::cout << message << std::endl; }

private:
    std::string message;
};

#endif // LEARNSTRUCTURE_MYEXCEPTIONS_H
