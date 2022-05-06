#ifndef _UTILITY_
#define _UTILITY_

#include <vector>
#include <string>

namespace Utility
{
    enum Types
    {
        undefined,
        number,
        float_number,
        string,
        boolean
    };

    const std::vector<std::string> tokens{"let","if","else","while","show"};
    enum token_index
    {
        Let,
        If,
        Else,
        While,
        Show
    };

    bool is_boolean(const std::string&);
    bool is_number(const std::string&);
    bool is_float_number(const std::string&);
};

#endif // _UTILITY_
