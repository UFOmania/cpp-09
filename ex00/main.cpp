#include "BitcoinExchange.hpp"
#include <iostream>

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cout << "Error: Usage: btc <file_name>" << std::endl;
        return 1;
    }

    BitcoinExchange bc;
    bc.initDatabase(av[1]);

}