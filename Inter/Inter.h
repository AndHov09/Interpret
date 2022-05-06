#ifndef _INTER_
#define _INTER_

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <exception>

#include "Type.h"
#include "Utility.h"

class Inter
{
    public:
        Inter(std::string);
        ~Inter();
        
        void start();
        void Tokens(std::vector<std::string>&);
        void print(std::vector<std::string>&);
        bool creat_var(std::vector<std::string>&);
        std::vector<std::string> split(std::string,std::string);
        void fun_if(std::vector<std::string>&,bool&);
        void fun_else(bool&);
        void fun_while(std::vector<std::string>&);
    private:

        std::map<std::string,Var> m_variable;
        std::ifstream m_file;
};

#endif // _INTER_
