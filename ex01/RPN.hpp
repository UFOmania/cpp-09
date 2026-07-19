#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <sstream>
#include <exception>

class RPN {
    private:
        static int parseFormula(const std::string & value);
        static int doCalculate(const std::string & formula);

    
    public:
        ~RPN();
        RPN();
        RPN(const RPN &);
        RPN &operator=(const RPN &);
        static void calculate(const std::string &);

};

#endif