#include "BitcoinExchange.hpp"
#include <iostream>
#include <iomanip>
int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cout << "Error: Usage: btc <file_name>" << std::endl;
        return 1;
    }

    BitcoinExchange bc;
    try{
        
        std::cout << std::setprecision(10);
        bc.initDatabase("data.csv");
        bc.read_input(av[1]);
        
    }
    catch (const std::exception & e){
        std::cout <<"Error: "<<  e.what() << std::endl;
        return 1;
    }
    std::cout << 47115.93 << std::endl;

}