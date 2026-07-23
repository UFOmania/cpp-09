#include "RPN.hpp"

RPN::~RPN(){}
RPN::RPN(){}
RPN::RPN(const RPN &){}
RPN &RPN::operator=(const RPN &){return *this;}

bool checkOverflow(ssize_t resultBuffer)
{
    return (resultBuffer > (long)__INT_MAX__ || resultBuffer < (long)-2147483648);
}

int RPN::doCalculate(const std::string & formula){
    std::stack<int> st;
    for (std::string::const_iterator it = formula.begin(); it != formula.end(); it++){
        if (std::isdigit(*it)){
            st.push((*it) - 48);
            continue;
        }
        if (*it == '+' || *it == '-' || *it == '*' || *it == '/'){
            if (st.size() < 2)
                return 0;

            ssize_t right = st.top();
            st.pop();
                    
            ssize_t left = st.top();
            st.pop();

            ssize_t resultBuffer = 0;
            
            switch (*it)
            {
                case '+': resultBuffer = left + right;  break;
                case '-': resultBuffer = left - right;  break;
                case '*': resultBuffer = left * right;  break;
                case '/': 
                    if( right == 0)
                        throw std::runtime_error("division by 0");

                    resultBuffer = left / right; 
                    break;
            }
            if (checkOverflow(resultBuffer))
                throw std::overflow_error("result overflow");
            
            st.push(static_cast<int>(resultBuffer));
        }
    }
    if (st.size() != 1)
        return (0);
    std::cout << st.top() << std::endl;
    return (1);
}

int RPN::parseFormula(const std::string & str)
{
    std::stringstream ss;
    ss << str;

    std::string tmp;
    while (ss >> tmp)
    {
        if (tmp.length() != 1)
            return 0;
        if (!std::isdigit(tmp[0]) && tmp[0] != '+' && tmp[0] != '-' && tmp[0] != '*' && tmp[0] != '/')
            return 0;
    }

    return 1;
}


void RPN::calculate(const std::string & formula)
{
    // parsing
    try{
        if (!parseFormula(formula) || !doCalculate(formula))
            std::cout << "Error: Bad Formula" << std::endl;
    }
    catch (const std::exception & e)
    {
        std::cout << "Error:" << e.what() << std::endl;
    }

}
