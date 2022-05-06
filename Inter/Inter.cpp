#include "Inter.h"

Inter::Inter(std::string file_name) : m_variable{}, m_file{file_name}
{
}

Inter::~Inter()
{
    m_file.close();
}

void Inter::start()
{
    if(!m_file.is_open())
    {
        throw std::invalid_argument("File Not Found");
    }
    std::string str{};
    while(std::getline(m_file,str))
    {
        std::vector<std::string> vec = split(str," ");
        Tokens(vec);
        str.clear();
    }
}

void Inter::Tokens(std::vector<std::string>& vec)
{
        
        bool flag = false;
        if(vec[0] == Utility::tokens[Utility::Let])
        {
            if(!creat_var(vec))
            {
                std::cout << "Syntax Error!" << std::endl;
                exit(1);
            }
        }
        else if(vec[0] == Utility::tokens[Utility::Show])
        {
            print(vec);
        }
        else if(vec[0] == Utility::tokens[Utility::If])
        {
            fun_if(vec,flag);
            while(!flag)
            {
                std::string str{};
                int count = 0;
                getline(m_file,str);
                if(str == "{")
                {
                    ++count;
                }else if(str == "}")
                {
                    --count;
                }else if(!count)
                {
                    break;
                }
            }
        }else if(vec[0] == Utility::tokens[Utility::Else])
        {
            if(vec[1] == Utility::tokens[Utility::If])
            {
                vec.erase(vec.begin());
                fun_if(vec,flag);
                while(!flag)
                {
                    std::string str{};
                    int count = 0;
                    getline(m_file,str);
                    if(str == "{")
                    {
                        ++count;
                    }else if(str == "}")
                    {
                        --count;
                    }else if(!count)
                    {
                        break;
                    }
                }
            }
            else
            {
                fun_else(flag);
            }
            
        }
        else if(vec[0] == Utility::tokens[Utility::While])
        {
            fun_while(vec);
        }
        else if(m_variable.find(vec[0]) != m_variable.end()){
            if(vec[1] == "=")
            {
                m_variable[vec[0]] = m_variable.find(vec[2]) == m_variable.end() ? vec[2] : m_variable[vec[2]];
            }
            else if(vec[1] == "+=")
            {
                m_variable[vec[0]] += m_variable.find(vec[2]) == m_variable.end() ? vec[2] : m_variable[vec[2]];
            }
            else if(vec[1] == "-=")
            {
                m_variable[vec[0]] -= m_variable.find(vec[2]) == m_variable.end() ? vec[2] : m_variable[vec[2]];
            }
            else if(vec[1] == "*=")
            {
                m_variable[vec[0]] *= m_variable.find(vec[2]) == m_variable.end() ? vec[2] : m_variable[vec[2]];
            }
            else if(vec[1] == "/=")
            {
                m_variable[vec[0]] /= m_variable.find(vec[2]) == m_variable.end() ? vec[2] : m_variable[vec[2]];
            }
            else if(vec[1] == "%=")
            {
                m_variable[vec[0]] %= m_variable.find(vec[2]) == m_variable.end() ? vec[2] : m_variable[vec[2]];
            }
        }
        else
        {
            if(vec[0] != "{" && vec[0] != "}")
            {
            std::cout << "Syntax Error" << std::endl;
            exit(2);
            }
        }

}

std::vector<std::string> Inter::split(std::string s, std::string delimiter){
    size_t pos_start = 0;
    size_t pos_end;
    size_t delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) 
    {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
        token.clear();
        if(delimiter != " ")
        {
            res.push_back(delimiter);
        }
    }

    res.push_back (s.substr (pos_start));
    return res;
}

bool Inter::creat_var(std::vector<std::string>& vec)
{
    if(vec[0] == Utility::tokens[Utility::Let])
    {
        if( m_variable.find(vec[1]) != m_variable.end() )
        {
            return false;
        }
        m_variable[vec[1]] = Var{vec[3]};
    }else{
        if( m_variable.find(vec[0]) == m_variable.end() )
        {
            return false;
        }
        m_variable[vec[0]] = Var{vec[2]};
    }
    vec.clear();
    return true;
}

void Inter::print(std::vector<std::string>& vec)
{
    try
    {
        if(vec.size() == 2)
        {
            if(m_variable.find(vec[1]) == m_variable.end())
            {
                if(Utility::is_boolean(vec[1]))
                {
                    Var{vec[1]}.print();
                }
                else if(Utility::is_number(vec[1]))
                {
                    Var{vec[1]}.print();
                }
                else if(Utility::is_float_number(vec[1]))
                {
                    Var{vec[1]}.print();
                }
                else
                {
                    Var{vec[1]}.print();
                }
            }else{
                m_variable[vec[1]].print();
            }
        }else{
            if(m_variable.find(vec[3]) != m_variable.end() && m_variable.find(vec[1]) != m_variable.end())
            {
                if(vec[2] == "=")
                {
                    (m_variable[vec[1]] = m_variable[vec[3]]).print();    
                }
                else if(vec[2] == "+")
                {
                    (m_variable[vec[1]] + m_variable[vec[3]]).print();    
                }
                else if(vec[2] == "-")
                {
                    (m_variable[vec[1]] - m_variable[vec[3]]).print();    
                }
                else if(vec[2] == "*")
                {
                    (m_variable[vec[1]] * m_variable[vec[3]]).print();    
                }
                else if(vec[2] == "/")
                {
                    (m_variable[vec[1]] / m_variable[vec[3]]).print();    
                }
                else if(vec[2] == "%")
                {
                    (m_variable[vec[1]] % m_variable[vec[3]]).print();    
                }
                if(vec[2] == "+=")
                {
                    (m_variable[vec[1]] += m_variable[vec[3]]).print();    
                }
                else if(vec[2] == "-=")
                {
                    (m_variable[vec[1]] -= m_variable[vec[3]]).print();    
                }
                else if(vec[2] == "*=")
                {
                    (m_variable[vec[1]] *= m_variable[vec[3]]).print();    
                }
                else if(vec[2] == "/=")
                {
                    (m_variable[vec[1]] /= m_variable[vec[3]]).print();    
                }
                else if(vec[2] == "%=")
                {
                    (m_variable[vec[1]] %= m_variable[vec[3]]).print();    
                }
                else if(vec[2] == "==")
                {
                    (m_variable[vec[1]] == m_variable[vec[3]]) ? std::cout << "True" << std::endl : std::cout << "False" << std::endl;
                }
                else if(vec[2] == ">=")
                {
                    (m_variable[vec[1]] >= m_variable[vec[3]]) ? std::cout << "True" << std::endl : std::cout << "Fasle" << std::endl;
                }
                else if(vec[2] == "<=")
                {
                    (m_variable[vec[1]] <= m_variable[vec[3]]) ? std::cout << "True" << std::endl : std::cout << "False" << std::endl;
                }
                else if(vec[2] == "<")
                {
                    (m_variable[vec[1]] < m_variable[vec[3]]) ? std::cout << "True" << std::endl : std::cout << "False" << std::endl;
                }
                else if(vec[2] == ">")
                {
                    (m_variable[vec[1]] > m_variable[vec[3]]) ? std::cout << "True" << std::endl : std::cout << "False" << std::endl;
                }
                else if(vec[2] == "!=")
                {
                    (m_variable[vec[1]] != m_variable[vec[3]]) ? std::cout << "True" << std::endl : std::cout << "False" << std::endl;
                }
            }else
            {
                if(vec[2] == "=")
                {
                    (m_variable[vec[1]] = Var{vec[3]}).print();    
                }
                else if(vec[2] == "+")
                {
                    (m_variable[vec[1]] + Var{vec[3]}).print();    
                }
                else if(vec[2] == "-")
                {
                    (m_variable[vec[1]] - Var{vec[3]}).print();    
                }
                else if(vec[2] == "*")
                {
                    (m_variable[vec[1]] * Var{vec[3]}).print();    
                }
                else if(vec[2] == "/")
                {
                    (m_variable[vec[1]] / Var{vec[3]}).print();    
                }
                else if(vec[2] == "%")
                {
                    (m_variable[vec[1]] % Var{vec[3]}).print();    
                }
                else if(vec[2] == "+=")
                {
                    (m_variable[vec[1]] += Var{vec[3]}).print();    
                }
                else if(vec[2] == "-=")
                {
                    (m_variable[vec[1]] -= Var{vec[3]}).print();    
                }
                else if(vec[2] == "*=")
                {
                    (m_variable[vec[1]] *= Var{vec[3]}).print();    
                }
                else if(vec[2] == "/=")
                {
                    (m_variable[vec[1]] /= Var{vec[3]}).print();    
                }
                else if(vec[2] == "%=")
                {
                    (m_variable[vec[1]] %= Var{vec[3]}).print();    
                }
                else if(vec[2] == "==")
                {
                    (m_variable[vec[1]] == Var{vec[3]}) ? std::cout << "True" << std::endl : std::cout << "False" << std::endl;
                }
                else if(vec[2] == ">=")
                {
                    (m_variable[vec[1]] >= Var{vec[3]}) ? std::cout << "True" << std::endl : std::cout << "Fasle" << std::endl;
                }
                else if(vec[2] == "<=")
                {
                    (m_variable[vec[1]] <= Var{vec[3]}) ? std::cout << "True" << std::endl : std::cout << "False" << std::endl;
                }
                else if(vec[2] == "<")
                {
                    (m_variable[vec[1]] < Var{vec[3]}) ? std::cout << "True" << std::endl : std::cout << "False" << std::endl;
                }
                else if(vec[2] == ">")
                {
                    (m_variable[vec[1]] > Var{vec[3]}) ? std::cout << "True" << std::endl : std::cout << "False" << std::endl;
                }
                else if(vec[2] == "!=")
                {
                    (m_variable[vec[1]] != Var{vec[3]}) ? std::cout << "True" << std::endl : std::cout << "False" << std::endl;
                }
            }
        }
    }
    catch(std::exception& exp)
    {
        std::cout << exp.what() << std::endl;
    }
}

void Inter::fun_if(std::vector<std::string>& vec,bool& flag)
{
    if( vec[2] == "==")
    {
        if(m_variable.find(vec[1]) != m_variable.end())
        {
            if(m_variable.find(vec[3]) != m_variable.end())
            {
                flag = (m_variable[vec[1]] == m_variable[vec[3]]);
            }
            else
            {
                flag = (m_variable[vec[1]] == Var{vec[3]});
            }
        }
        else
        {
            if(m_variable.find(vec[3]) != m_variable.end())
            {
                flag = (Var{vec[1]} == m_variable[vec[3]]);
            }
            else
            {
                flag = (vec[1] == vec[3]);
            }
            
        }
    }
    else if(vec[2] == "!=")
    {
        if(m_variable.find(vec[1]) != m_variable.end())
        {
            if(m_variable.find(vec[3]) != m_variable.end())
            {
                flag = (m_variable[vec[1]] != m_variable[vec[3]]);
            }
            else
            {
                flag = (m_variable[vec[1]] != Var{vec[3]});
            }
        }
        else
        {
            if(m_variable.find(vec[3]) != m_variable.end())
            {
                flag = (Var{vec[1]} != m_variable[vec[3]]);
            }
            else
            {
                flag = (vec[1] != vec[3]);
            }
            
        }

    }
    else if(vec[2] == "<=")
    {
        if(m_variable.find(vec[1]) != m_variable.end())
        {
            if(m_variable.find(vec[3]) != m_variable.end())
            {
                flag = (m_variable[vec[1]] <= m_variable[vec[3]]);
            }
            else
            {
                flag = (m_variable[vec[1]] <= Var{vec[3]});
            }
        }
        else
        {
            if(m_variable.find(vec[3]) != m_variable.end())
            {
                flag = (Var{vec[1]} <= m_variable[vec[3]]);
            }
            else
            {
                flag = (vec[1] <= vec[3]);
            }
            
        }

    }
    else if(vec[2] == ">=")
    {
        if(m_variable.find(vec[1]) != m_variable.end())
        {
            if(m_variable.find(vec[3]) != m_variable.end())
            {
                flag = (m_variable[vec[1]] >= m_variable[vec[3]]);
            }
            else
            {
                flag = (m_variable[vec[1]] >= Var{vec[3]});
            }
        }
        else
        {
            if(m_variable.find(vec[3]) != m_variable.end())
            {
                flag = (Var{vec[1]} >= m_variable[vec[3]]);
            }
            else
            {
                flag = (vec[1] >= vec[3]);
            }
            
        }

    }
    else if(vec[2] == "<")
    {
        if(m_variable.find(vec[1]) != m_variable.end())
        {
            if(m_variable.find(vec[3]) != m_variable.end())
            {
                flag = (m_variable[vec[1]] < m_variable[vec[3]]);
            }
            else
            {
                flag = (m_variable[vec[1]] < Var{vec[3]});
            }
        }
        else
        {
            if(m_variable.find(vec[3]) != m_variable.end())
            {
                flag = (Var{vec[1]} < m_variable[vec[3]]);
            }
            else
            {
                flag = (vec[1] < vec[3]);
            }
            
        }

    }
    else if(vec[2] == ">")
    {
        if(m_variable.find(vec[1]) != m_variable.end())
        {
            if(m_variable.find(vec[3]) != m_variable.end())
            {
                flag = (m_variable[vec[1]] > m_variable[vec[3]]);
            }
            else
            {
                flag = (m_variable[vec[1]] > Var{vec[3]});
            }
        }
        else
        {
            if(m_variable.find(vec[3]) != m_variable.end())
            {
                flag = (Var{vec[1]} > m_variable[vec[3]]);
            }
            else
            {
                flag = (vec[1] > vec[3]);
            }
            
        }

    }
    else if(vec[2] == "+=")
    {
        if(m_variable.find(vec[1]) != m_variable.end())
        {
            if(m_variable.find(vec[3]) != m_variable.end())
            {
                flag = (m_variable[vec[1]] += m_variable[vec[3]]).to_boolean();
            }
            else
            {
                flag = (m_variable[vec[1]] += Var{vec[3]}).to_boolean();
            }
        }
        else
        {
            if(m_variable.find(vec[3]) != m_variable.end())
            {
                flag = (Var{vec[1]} += m_variable[vec[3]]).to_boolean();
            }
            else
            {
                flag = (Var{vec[1]} += Var{vec[3]}).to_boolean();
            }
            
        }

    }
    else if(vec[2] == "-=")
    {
        if(m_variable.find(vec[1]) != m_variable.end())
        {
            if(m_variable.find(vec[3]) != m_variable.end())
            {
                flag = (m_variable[vec[1]] -= m_variable[vec[3]]).to_boolean();
            }
            else
            {
                flag = (m_variable[vec[1]] -= Var{vec[3]}).to_boolean();
            }
        }
        else
        {
            if(m_variable.find(vec[3]) != m_variable.end())
            {
                flag = (Var{vec[1]} -= m_variable[vec[3]]).to_boolean();
            }
            else
            {
                flag = (Var{vec[1]} -= Var{vec[3]}).to_boolean();
            }
            
        }

    }
    else if(vec[2] == "*=")
    {
        if(m_variable.find(vec[1]) != m_variable.end())
        {
            if(m_variable.find(vec[3]) != m_variable.end())
            {
                flag = (m_variable[vec[1]] *= m_variable[vec[3]]).to_boolean();
            }
            else
            {
                flag = (m_variable[vec[1]] *= Var{vec[3]}).to_boolean();
            }
        }
        else
        {
            if(m_variable.find(vec[3]) != m_variable.end())
            {
                flag = (Var{vec[1]} *= m_variable[vec[3]]).to_boolean();
            }
            else
            {
                flag = (Var{vec[1]} *= Var{vec[3]}).to_boolean();
            }
            
        }

    }
    else if(vec[2] == "/=")
    {
        if(m_variable.find(vec[1]) != m_variable.end())
        {
            if(m_variable.find(vec[3]) != m_variable.end())
            {
                flag = (m_variable[vec[1]] /= m_variable[vec[3]]).to_boolean();
            }
            else
            {
                flag = (m_variable[vec[1]] /= Var{vec[3]}).to_boolean();
            }
        }
        else
        {
            if(m_variable.find(vec[3]) != m_variable.end())
            {
                flag = (Var{vec[1]} /= m_variable[vec[3]]).to_boolean();
            }
            else
            {
                flag = (Var{vec[1]} /= Var{vec[3]}).to_boolean();
            }
            
        }

    }
    else if(vec[2] == "%=")
    {
        if(m_variable.find(vec[1]) != m_variable.end())
        {
            if(m_variable.find(vec[3]) != m_variable.end())
            {
                flag = (m_variable[vec[1]] %= m_variable[vec[3]]).to_boolean();
            }
            else
            {
                flag = (m_variable[vec[1]] %= Var{vec[3]}).to_boolean();
            }
        }
        else
        {
            if(m_variable.find(vec[3]) != m_variable.end())
            {
                flag = (Var{vec[1]} %= m_variable[vec[3]]).to_boolean();
            }
            else
            {
                flag = (Var{vec[1]} %= Var{vec[3]}).to_boolean();
            }
            
        }

    }
}

void Inter::fun_else(bool& flag)
{
    while(flag)
    {
        std::string str{};
        std::getline(m_file,str);
        int count = 0;
        if(str == "{")
        {
            ++count;
        }else if(str == "}")
        {
            --count;
        }else if(!count)
        {
            break;
        }
    }
}

void Inter::fun_while(std::vector<std::string>& vec)
{
    bool flag;
    fun_if(vec,flag);
    std::vector<std::vector<std::string>> while_tokens{};
    std::string str{};
    int count{};
    if(flag)
    {
       while(true)
       {
            getline(m_file,str);
            while_tokens.push_back(split(str," "));
            if(str == "{")
            {
                ++count;
            }else if(str == "}")
            {
                --count;
            }
            if(!count)
            {
                break;
            }
       }
       while(flag)
       {
           for(int i = 0; i < while_tokens.size(); ++i)
           {
                Tokens(while_tokens[i]);
           }
           fun_if(vec,flag);
       }
    }
    else
    {
       while(true)
       {
            getline(m_file,str);
            if(str == "{")
            {
                ++count;
            }else if(str == "}")
            {
                --count;
            }
            if(!count)
            {
                break;
            }
       }
  
    }
}
