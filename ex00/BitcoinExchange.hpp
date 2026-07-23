#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <exception>

class BitcoinExchange {
    private:
        struct Date{
            int year;
            int month;
            int day;
            public:
                Date();
                std::string toStr();
        };
    
        std::map<std::string, double> _database;
        bool _isFirstLine;
        void validateDatabaseLine(const std::string & line);
        Date validateKey(std::string &);
        double validateValue(const std::string &);
        void validateInputLine(const std::string &);
        bool isValidDate(const Date &);
        void validateFirstLine(const std::string & line);
        
        
        
        public:
            ~BitcoinExchange();
            BitcoinExchange();
            BitcoinExchange(const BitcoinExchange &);
            BitcoinExchange &operator=(const BitcoinExchange &);
            void initDatabase(const char * filename);
            void read_input(const char * filename);
};


#endif
