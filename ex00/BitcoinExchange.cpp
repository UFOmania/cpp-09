#include "BitcoinExchange.hpp"

BitcoinExchange::~BitcoinExchange()
{
    
}

BitcoinExchange::BitcoinExchange(): _init(true)
{
    
}

void BitcoinExchange::validateKey(const std::string & key)
{
    std::string year;
    std::string month;
    std::string day;

    //extraction
    size_t delemPos = key.find('-');
    if (delemPos == key.npos || delemPos == 0)
        throw std::runtime_error(key);
    year = key.substr(0, delemPos);

    size_t delemPos2 = key.find('-');
    if (delemPos2 == key.npos || key.find('-') != key.npos)
        throw std::runtime_error(key);
    
    month = key.substr(delemPos, delemPos2);

    day = key.substr(delemPos2);

    if (day.empty())
        throw std::runtime_error(key);

    //validation
    int tmp;
    std::stringstream ss;

    ss << year;
    if (!(ss >> tmp) || tmp < 0)
        throw std::runtime_error(key);


    ss.clear();

    ss << month;
    if (!(ss >> tmp) || tmp < 0)
        throw std::runtime_error(key);
    ss.clear();

    ss << day;
    if (!(ss >> tmp) || tmp < 0)
        throw std::runtime_error(key);
    ss.clear();
    


}

void BitcoinExchange::validateDatabaseline(const std::string & line)
{
    std::string key;
    std::string value;

    size_t delemPos = line.find(',');
    if (delemPos == line.npos || delemPos == 0 || line.find(',') != line.npos)
        throw std::runtime_error("Bad line at data.csv");

    key = line.substr(0, delemPos - 1);
    value = line.substr(delemPos + 1);

    if (value.empty())
        throw std::runtime_error("Bad line at data.csv");
    
    if (_init == false)
    {
        validateKey(key);
        double numValue = validateValue(value);
        _database.insert((std::make_pair<std::string, double>(key, numValue)));
    }
    _init = false;
}

void BitcoinExchange::initDatabase(const char * filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("couldn't open 'data.csv' file");
    }

    std::string line;
    while (true)
    {
        std::getline(file, line);
        if (file.fail())
            throw std::runtime_error("couldn't read line from 'data.csv'");

        validateDatabaseline(line);

    }
}