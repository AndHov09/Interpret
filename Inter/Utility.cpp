#include "Utility.h"

bool Utility::is_boolean(const std::string& str)
{
    if(str == "true" || str == "false")
    {
        return true;
    }
    return false;
}

bool Utility::is_number(const std::string& str)
{
    for(int i = 0; i < str.size(); ++i)
    {
        if(str[i] < '0' || str[i] > '9')
        {
            return false;
        }
    }
    return true;
}

bool Utility::is_float_number(const std::string& str)
{
    for(int i = 0; i < str.size(); ++i)
    {
        if(str[i] == '.')
        {
            continue;
        }else if(str[i] < '0' || str[i] > '9')
        {
            return false;
        }
    }
    return true;
}
