#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <exception>

class BitcoinExchange {
    private:
    typedef struct date_s{
        int year;
        int month;
        int day;
        // public:
        //     bool operator==(const struct date_s &);
    } date_t;
    
        std::map<date_t, double> _database;
        bool _isFirstLine;
        void validateDatabaseLine(const std::string & line);
        date_t validateKey(std::string &);
        double validateValue(const std::string &);
        void validateInputLine(const std::string &);
        
        
        
        public:
        ~BitcoinExchange();
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &);
        BitcoinExchange &operator=(const BitcoinExchange &);
        void initDatabase(const char * filename);
        void read_input(const char * filename);
};


#endif
