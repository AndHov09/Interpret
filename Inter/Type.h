#ifndef _TYPE_
#define _TYPE_

#include "Utility.h"
#include <exception>
#include <string>
#include <iostream>

class Var
{
    public:
        Var();
        Var(const Var&);
        Var(Var&&);
        Var(const std::string&);
        Var(double);
        Var(long);
        ~Var();

        Var& operator=(const Var&);
        Var& operator=(Var&&);

        std::string typeof() const;
        void print() const;

        Var& operator+=(const Var&);
        Var& operator-=(const Var&);
        Var& operator*=(const Var&);
        Var& operator/=(const Var&);
        Var& operator%=(const Var&);

        Var to_number() const;
        Var to_float_number() const;
        bool to_boolean() const;

        friend bool operator==(const Var&,const Var&);
        friend bool operator<(const Var&,const Var&);
    private:
        void* m_ptr;
        Utility::Types m_info;
};

Var operator+(const Var&,const Var&);
Var operator-(const Var&,const Var&);
Var operator*(const Var&,const Var&);
Var operator/(const Var&,const Var&);
Var operator%(const Var&,const Var&);

bool operator!=(const Var&,const Var&);
bool operator<=(const Var&,const Var&);
bool operator>=(const Var&,const Var&);
bool operator>(const Var&,const Var&);

#endif // _TYPE_
