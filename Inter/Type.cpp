#include "Type.h"

Var::Var() : m_ptr{}, m_info{Utility::Types::undefined}
{}

Var::Var(const Var& oth) : m_ptr{},m_info{oth.m_info}
{
    switch(m_info)
    {
        case Utility::undefined:
            break;
        case Utility::number:
           m_ptr = new long(*(long*)oth.m_ptr);
           break;
        case Utility::float_number:
            m_ptr = new double(*(double*)oth.m_ptr);
            break;
        case Utility::string:
            m_ptr = new std::string(*(std::string*)oth.m_ptr);
            break;
        case Utility::boolean:
            m_ptr = new bool(*(bool*)oth.m_ptr);
            break;
    }
}

Var::Var(Var&& tmp) : m_ptr{tmp.m_ptr}, m_info{tmp.m_info}
{
    tmp.m_ptr = nullptr;
    tmp.m_info = Utility::Types::undefined;
}

Var::Var(const std::string& str)
{
    if(Utility::is_boolean(str))
    {
        m_ptr = new bool(str == "true" ? true:false);
        m_info = Utility::Types::boolean;
    }else if(Utility::is_number(str))
    {
        m_ptr = new long(std::stol(str));
        m_info = Utility::Types::number;
    }else if(Utility::is_float_number(str))
    {
        m_ptr = new double(std::stod(str));
        m_info = Utility::Types::float_number;
    }else{
        m_ptr = new std::string(str);
        m_info = Utility::Types::string;
    }
}

Var::Var(double db) : m_ptr{new double(db)}, m_info{Utility::Types::float_number}
{}

Var::Var(long lg) : m_ptr{new long(lg)}, m_info{Utility::Types::number}
{}

Var::~Var()
{
    if(m_ptr)
    { 
        switch(m_info)
        {
            case Utility::undefined:
                break;
            case Utility::number:
                delete (long*)m_ptr;
                break;
            case Utility::float_number:
                delete (double*)m_ptr;
                break;
            case Utility::string:
                delete (std::string*)m_ptr;
                break;
            case Utility::boolean:
                delete (bool*)m_ptr;
                break;
        }
    }
}

Var& Var::operator=(const Var& oth)
{
    if(!m_ptr)
    {
        switch(m_info)
        {
            case Utility::undefined:
                break;
            case Utility::number:
                delete (long*)m_ptr;
                break;
            case Utility::float_number:
                delete (double*)m_ptr;
                break;
            case Utility::string:
                delete (std::string*)m_ptr;
                break;
            case Utility::boolean:
                delete (bool*)m_ptr;
                break;
        }
    }
    m_info = oth.m_info;
    switch(m_info)
    {
        case Utility::undefined:
            break;
        case Utility::number:
           m_ptr = new long(*(long*)oth.m_ptr);
           break;
        case Utility::float_number:
            m_ptr = new double(*(double*)oth.m_ptr);
            break;
        case Utility::string:
            m_ptr = new std::string(*(std::string*)oth.m_ptr);
            break;
        case Utility::boolean:
            m_ptr = new bool(*(bool*)oth.m_ptr);
            break;
    }
    return *this;
}

Var& Var::operator=(Var&& tmp)
{
    if(!m_ptr)
    {
        switch(m_info)
        {
            case Utility::undefined:
                break;
            case Utility::number:
                delete (long*)m_ptr;
                break;
            case Utility::float_number:
                delete (double*)m_ptr;
                break;
            case Utility::string:
                delete (std::string*)m_ptr;
                break;
            case Utility::boolean:
                delete (bool*)m_ptr;
                break;
        }
    }
    m_ptr = tmp.m_ptr;
    m_info = tmp.m_info;
    tmp.m_ptr = nullptr;
    tmp.m_info = Utility::Types::undefined;
    return *this;
}

std::string Var::typeof() const
{
    switch(m_info)
    {
        case Utility::undefined:
            return "Undefined";
            break;
        case Utility::number:
            return "Number";
            break;
        case Utility::float_number:
            return "Float";
            break;
        case Utility::string:
            return "String";
            break;
        case Utility::boolean:
            return "Boolean";
            break;
    }
    return "";
}

Var& Var::operator+=(const Var& oth)
{
    if(m_info != oth.m_info)
    {
        throw std::invalid_argument("Different Types");
    }
    switch(m_info)
    {
        case Utility::undefined:
            throw std::invalid_argument("Type is Undefined");
            break;
        case Utility::number:
            *(long*)m_ptr += *(long*)oth.m_ptr;
            break;
        case Utility::float_number:
            *(double*)m_ptr += *(double*)oth.m_ptr;
            break;
        case Utility::string:
            *(std::string*)m_ptr += *(std::string*)oth.m_ptr;
            break;
        case Utility::boolean:
            throw std::invalid_argument("Type is Boolean");
            break;
    }
    return *this;
}

Var& Var::operator-=(const Var& oth)
{
    if(m_info != oth.m_info)
    {
        throw std::invalid_argument("Different Types");
    }
    switch(m_info)
    {
        case Utility::undefined:
            throw std::invalid_argument("Type is Undefined");
            break;
        case Utility::number:
            *(long*)m_ptr -= *(long*)oth.m_ptr;
            break;
        case Utility::float_number:
            *(double*)m_ptr -= *(double*)oth.m_ptr;
            break;
        case Utility::string:
            throw std::invalid_argument("Type is String");
            break;
        case Utility::boolean:
            throw std::invalid_argument("Type is Boolean");
            break;
    }
    return *this;
}

Var& Var::operator*=(const Var& oth)
{
    if(m_info != oth.m_info)
    {
        throw std::invalid_argument("Different Types");
    }
    switch(m_info)
    {
        case Utility::undefined:
            throw std::invalid_argument("Type is Undefined");
            break;
        case Utility::number:
            *(long*)m_ptr *= *(long*)oth.m_ptr;
            break;
        case Utility::float_number:
            *(double*)m_ptr *= *(double*)oth.m_ptr;
            break;
        case Utility::string:
            throw std::invalid_argument("Type is String");
            break;
        case Utility::boolean:
            throw std::invalid_argument("Type is Boolean");
            break;
    }
    return *this;
}

Var& Var::operator/=(const Var& oth)
{
    if(m_info != oth.m_info)
    {
        throw std::invalid_argument("Different Types");
    }
    switch(m_info)
    {
        case Utility::undefined:
            throw std::invalid_argument("Type is Undefined");
            break;
        case Utility::number:
            *(long*)m_ptr /= *(long*)oth.m_ptr;
            break;
        case Utility::float_number:
            *(double*)m_ptr /= *(double*)oth.m_ptr;
            break;
        case Utility::string:
            throw std::invalid_argument("Type is String");
            break;
        case Utility::boolean:
            throw std::invalid_argument("Type is Boolean");
            break;
    }
    return *this;
}

Var& Var::operator%=(const Var& oth)
{
    if(m_info != oth.m_info)
    {
        throw std::invalid_argument("Different Types");
    }
    switch(m_info)
    {
        case Utility::undefined:
            throw std::invalid_argument("Type is Undefined");
            break;
        case Utility::number:
            *(long*)m_ptr %= *(long*)oth.m_ptr;
            break;
        case Utility::float_number:
            throw std::invalid_argument("Type is Float");
            break;
        case Utility::string:
            throw std::invalid_argument("Type is String");
            break;
        case Utility::boolean:
            throw std::invalid_argument("Type is Boolean");
            break;
    }
    return *this;
}

void Var::print() const
{
    switch(m_info)
    {
        case Utility::undefined:
            std::cout << "Undefined" << std::endl;
            break;
        case Utility::number:
            std::cout << *(long*)m_ptr << std::endl;
            break;
        case Utility::float_number:
            std::cout << *(double*)m_ptr << std::endl;
            break;
        case Utility::string:
            std::cout << *(std::string*)m_ptr << std::endl;
            break;
        case Utility::boolean:
            std::cout << std::boolalpha << *(bool*)m_ptr << std::endl;
            break;
    }
}

Var Var::to_number() const
{
    switch(m_info)
    {
        case Utility::undefined :
            return Var{0l};
            break;
        case Utility::number :
            return Var{*this};
            break;
        case Utility::float_number :
            return Var((long)*(double*)m_ptr);
            break;
        case Utility::string :
            return Var{std::stol(*(std::string*)m_ptr)}; 
            break;
        case Utility::boolean :
            return Var{*(bool*)m_ptr ? 1l : 0l};
            break;
    }
    return {};
}

Var Var::to_float_number() const
{
    switch(m_info)
    {
        case Utility::undefined :
            return Var{0.0};
            break;
        case Utility::number :
            return Var{(double)*(long*)m_ptr};
            break;
        case Utility::float_number :
            return Var(*this);
            break;
        case Utility::string :
            return Var{std::stod(*(std::string*)m_ptr)}; 
            break;
        case Utility::boolean :
            return Var{*(bool*)m_ptr ? 1.0 : 0.0};
            break;
    }
    return {};
}

bool Var::to_boolean() const
{
    switch(m_info)
    {
        case Utility::undefined :
            return false;
            break;
        case Utility::number :
            return *(long*)m_ptr ? true : false;
            break;
        case Utility::float_number :
            return *(double*)m_ptr ? true : false;
            break;
        case Utility::string :
            return ((std::string*)m_ptr)->size() ? true : false;
            break;
        case Utility::boolean :
            return *(bool*)m_ptr;
            break;
    }
    return false;
}

Var operator+(const Var& lhs,const Var& rhs)
{
    Var tmp{lhs};
    tmp += rhs;
    return tmp;
}

Var operator-(const Var& lhs,const Var& rhs)
{
    Var tmp{lhs};
    tmp -= rhs;
    return tmp;
}

Var operator*(const Var& lhs,const Var& rhs)
{
    Var tmp{lhs};
    tmp *= rhs;
    return tmp;
}

Var operator/(const Var& lhs,const Var& rhs) 
{
    Var tmp{lhs};
    tmp *= rhs;
    return tmp;
}

Var operator%(const Var& lhs,const Var& rhs) 
{
    Var tmp{lhs};
    tmp %= rhs;
    return tmp;
}

bool operator==(const Var& lhs, const Var& rhs)
{
    switch(lhs.m_info)
    {
        case Utility::undefined :
            return rhs.m_info == Utility::Types::undefined ? true : false;
            break;
        case Utility::number :
            return (*(long*)lhs.m_ptr) == (*(long*)rhs.m_ptr);
            break;
        case Utility::float_number :
            return (*(double*)lhs.m_ptr) == (*(double*)rhs.m_ptr);
            break;
        case Utility::string :
            return (*(std::string*)lhs.m_ptr) == (*(std::string*)rhs.m_ptr);
            break;
        case Utility::boolean :
            return (*(bool*)lhs.m_ptr) == (*(bool*)rhs.m_ptr);
            break;
    }
    return false;
}

bool operator!=(const Var& lhs,const Var& rhs)
{
    return !(lhs == rhs);
}

bool operator<(const Var& lhs, const Var& rhs)
{
    switch(lhs.m_info)
    {
        case Utility::undefined :
            return false;
            break;
        case Utility::number :
            return (*(long*)lhs.m_ptr) < (*(long*)rhs.m_ptr);
            break;
        case Utility::float_number :
            return (*(double*)lhs.m_ptr) < (*(double*)rhs.m_ptr);
            break;
        case Utility::string :
            return false;
            break;
        case Utility::boolean :
            return false;
            break;
    }
    return false;
}

bool operator>(const Var& lhs,const Var& rhs)
{
    return !(lhs == rhs || lhs < rhs);
}

bool operator<=(const Var& lhs,const Var& rhs)
{
    return (lhs == rhs || lhs < rhs);
}

bool operator>=(const Var& lhs,const Var& rhs)
{
    return (lhs == rhs || !(lhs < rhs));
}
