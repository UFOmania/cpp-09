#include "BitcoinExchange.hpp"

BitcoinExchange::Date::Date(){}

std::string BitcoinExchange::Date::toStr(){
    

    std::stringstream ss;

    int tmp = year * 10;
    while (tmp <= 10000)
    {
        ss << "0";
        tmp *= 10;
    }
    // std::string date('0', zeros);
    ss << year;
   ss << '-';

    if (month < 10)
        ss << '0';
    ss << month;
    ss << '-';

    if (day < 10)
        ss << '0';
    ss << day;

    std::string date;
    ss >> date;
    // std::cout << "---------\n";
    // std::cout << year << "-" << month<<'-'<< day<<std::endl;
    // std::cout << date << std::endl;
    // std::cout << "++++++++++\n";

    return date;
}


BitcoinExchange::~BitcoinExchange()
{    
}

BitcoinExchange::BitcoinExchange(): _isFirstLine(true)
{
}

bool BitcoinExchange::isValidDate(const Date & date)
{
    if (date.month > 12 || date.month <= 0 || date.day <= 0)
        return false;
    if (date.month <= 7)
    {
        if (date.month == 2)
        {
            if (((date.year % 4 == 0) && !(date.year % 100 == 0)) || (date.year % 400 == 0))
            {
                if (date.day > 29)
                    return false;
            }
            else if (date.day > 28)
                return false;
            

        }
        else
        {
            if (date.month & 1)
            {
                if (date.day > 31)
                    return false;
            }
            else if (date.day > 30)
                return false;
        }
    }
    else
    {
        if ((date.month & 1) == 0)
        {
            if (date.day > 31)
                return false;
        }
        else if (date.day > 30)
            return false;
    }
    return true;
}

BitcoinExchange::Date BitcoinExchange::validateKey(std::string & key)
{
    std::string year;
    std::string month;
    std::string day;

    std::string finalKey;

    //extraction
    size_t delemPos = key.find('-');
    if (delemPos == key.npos || delemPos == 0)
        throw std::runtime_error(std::string ("Bad Input: ") + key);
    year = key.substr(0, delemPos);

    size_t delemPos2 = key.find('-', delemPos + 1);
    if (delemPos2 == key.npos || key.find('-', delemPos2 + 1) != key.npos)
        throw std::runtime_error(std::string ("Bad Input: ") + key);
    
    month = key.substr(delemPos + 1, delemPos2 - delemPos - 1);
        
    day = key.substr(delemPos2 + 1);
    

    if (day.empty())
        throw std::runtime_error(std::string ("Bad Input: ") + key);

    //validation
    Date date;
    int tmp;
    std::stringstream ss;

    ss << year;
    if (!(ss >> tmp) || tmp < 0)
        throw std::runtime_error(std::string ("Bad Input: ") + key);

    date.year = tmp;
    ss.clear();

    ss << month;
    if (!(ss >> tmp) || tmp < 0)
        throw std::runtime_error(std::string ("Bad Input: ") + key);
    date.month = tmp;
    ss.clear();

    ss << day;
    if (!(ss >> tmp) || tmp < 0)
        throw std::runtime_error(std::string ("Bad Input: ") + key);
    date.day = tmp;
    ss.clear();

    // std::cout << date.toStr() << std::endl;
    //save result
    if (isValidDate(date) == false)
        throw std::runtime_error(std::string("Bad Input => ") + key);


    return date;

}

double BitcoinExchange::validateValue(const std::string &value)
{
    std::stringstream ss;

    ss << value;
    
    double numValue;

    if (!(ss >> numValue))
        throw std::runtime_error(value);
    
    if (numValue > __INT_MAX__)
        throw std::runtime_error("too large a number.");
    if (numValue < 0)
        throw std::runtime_error("not a positive number.");

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
        Date date = validateKey(key);
        double numValue = validateValue(value);
        // std::cout << key << " | " << numValue << std::endl;
        _database[date.toStr()] = numValue;
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


void BitcoinExchange::validateInputLine(const std::string & line)
{
    
    if (line.empty())
        return;

    std::stringstream ss(line);
    std::string date,delemiter, ammount;
    


    ss >> date >> delemiter >> ammount;
    ss >> std::ws;

    if (date.empty() || delemiter.empty() || delemiter != "|" || ammount.empty() || !ss.eof())
        throw std::runtime_error("Bad Input 1 => " + line);


    Date key;
    double numAmmount;
    try
    {
        key =  validateKey(date);
        numAmmount = validateValue(ammount);
        if (numAmmount > 1000)
            throw std::runtime_error("too large a number.");
        // std::cout << key.toStr() << std::endl;
        std::map<std::string, double>::iterator it = _database.find(key.toStr());
        if (it == _database.end())
        {
            it = _database.lower_bound(key.toStr());
            if (it != _database.begin())
                it--;
        }

        if (it != _database.end())
        {
            std::cout << key.toStr() << " => " << ammount << " => " << numAmmount * it->second << "\n";
        }
        else
        {
            std::cout << "not Found\n";
            // std::cout << date << " => " << ammount << " => " << numAmmount * -1<< ".\n";
        }
        /* code */
    }
    catch(const std::exception& e)
    {
        std::cout  <<"Error: "  << e.what() << '\n';
    }
    
}

void BitcoinExchange::validateFirstLine(const std::string & line)
{
    if (line.empty())
        throw std::runtime_error("titles are missing");

    std::string date, delemiter, amount;
    std::stringstream ss(line);

    ss >> date >> delemiter>> amount;
    ss >> std::ws;

    if (date.empty() || delemiter.empty() || delemiter != "|" || amount.empty() || !ss.eof())
        throw std::runtime_error("Invalid Titles Line");

    
}

void BitcoinExchange::read_input(const char * filename)
{
    static bool firstLine = true;
    std::ifstream file(filename);
    if (file.fail())
        throw std::runtime_error("Couldn't open file.");
    while (true)
    {
        
        std::string line;
        std::getline(file, line);
        if (file.fail() && !file.eof())
            throw std::runtime_error("Failed to read line.");
        if (firstLine){
            firstLine = false;
            validateFirstLine(line);
            continue;
        }
        try
        {
            validateInputLine(line);
        }
        catch(const std::exception& e)
        {
            std::cerr << "Error: "<< e.what() << '\n';
        }
            
        if(file.eof())
            break;
        
    }
}