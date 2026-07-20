#include "BitcoinExchange.hpp"

BitcoinExchange::~BitcoinExchange()
{
    
}

BitcoinExchange::BitcoinExchange(): _isFirstLine(true)
{
    
}
BitcoinExchange::date_t BitcoinExchange::validateKey(std::string & key)
{
    std::string year;
    std::string month;
    std::string day;

    std::string finalKey;

    //extraction
    size_t delemPos = key.find('-');
    if (delemPos == key.npos || delemPos == 0)
        throw std::runtime_error(key);
    year = key.substr(0, delemPos);

    size_t delemPos2 = key.find('-', delemPos + 1);
    if (delemPos2 == key.npos || key.find('-', delemPos2 + 1) != key.npos)
        throw std::runtime_error(key);
    
    month = key.substr(delemPos + 1, delemPos2 - delemPos - 1);
        
    day = key.substr(delemPos2 + 1);
    

    if (day.empty())
        throw std::runtime_error(key);

    //validation
    struct date_s date;
    int tmp;
    std::stringstream ss;

    ss << year;
    if (!(ss >> tmp) || tmp < 0)
        throw std::runtime_error(key);

    date.year = tmp;
    ss.clear();

    ss << month;
    if (!(ss >> tmp) || tmp < 0)
        throw std::runtime_error(key);
    date.month = tmp;
    ss.clear();

    ss << day;
    if (!(ss >> tmp) || tmp < 0)
        throw std::runtime_error(key);
    date.day = tmp;
    ss.clear();

    //save result

    return date;

}

double BitcoinExchange::validateValue(const std::string &value)
{
    std::stringstream ss;

    ss << value;
    
    double numValue;

    if (!(ss >> numValue))
        throw std::runtime_error(value);

    return numValue;
}

void BitcoinExchange::validateDatabaseLine(const std::string & line)
{
    std::string key;
    std::string value;
// std::cout << line << std::endl;
size_t delemPos = line.find(',');
// std::cout << delemPos << std::endl;

    if (delemPos == line.npos || delemPos == 0 || line.find(',', delemPos + 1) != line.npos)
        throw std::runtime_error("Bad line at data.csv");

    key = line.substr(0, delemPos);
    value = line.substr(delemPos + 1);

    // std::cout << key << "  " << value << std::endl;

    if (value.empty())
        throw std::runtime_error("Bad line at data.csv");
    
    if (_isFirstLine == false)
    {
        date_t date = validateKey(key);
        double numValue = validateValue(value);
        std::cout << key << " | " << numValue << std::endl;
        _database[date] = numValue;
    }
    _isFirstLine = false;
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
        if (file.fail() && !file.eof())
            throw std::runtime_error("couldn't read line from 'data.csv'");
        if(file.eof())
            break;
        validateDatabaseLine(line);

    }
}

// bool BitcoinExchange::date_t::operator==(const BitcoinExchange::date_t & o)
// {
//     return (this->day == o.day && this->month == o.month && this->year == o.year) ;
// }

void BitcoinExchange::validateInputLine(const std::string & line)
{
    std::string date, ammount;

    size_t delemPos = line.find(" | ", 0);
    if (delemPos == line.npos )
        throw std::runtime_error("Bad Input");
    date = line.substr(0, delemPos);
    ammount = line.substr(delemPos + 4);

    date_t key =  validateKey(date);
    double numAmmount = validateValue(ammount);
    if (_database.find(key) != _database.end())
    {
        std::cout << date << " => " << ammount << " => " << numAmmount * _database[key]<< ".\n";
    }
    else
    {
        std::cout << date << " => " << ammount << " => " << numAmmount * -1<< ".\n";
    }
}

void BitcoinExchange::read_input(const char * filename)
{
    std::ifstream file(filename);
    if (file.fail())
        throw std::runtime_error("Couldn't open file.");
    while (true)
    {
        std::string line;
        std::getline(file, line);
        if (file.fail() && !file.eof())
            throw std::runtime_error("Failed to read line.");
        if(file.eof())
            break;
        
    }
}