#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <exception>

class BitcoinExchange {
    private:
        std::map<std::string, double> _database;
        bool _init;
        void validateDatabaseline(const std::string & line);
        void validateKey(const std::string &);
        double validateValue(const std::string &);



    public:
        ~BitcoinExchange();
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &);
        BitcoinExchange &operator=(const BitcoinExchange &);
        void initDatabase(const char * filename);
};


#endif
