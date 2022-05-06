#include "Inter.h"
#include <iostream>

int main(int argv,char** argc)
{
    try
    {
        Inter obj(argc[1]);
        obj.start();
    }catch(std::exception& exp)
    {
        std::cout << exp.what() << std::endl;
    }
}
