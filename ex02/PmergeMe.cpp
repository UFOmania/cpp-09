#include "PmergeMe.hpp"

PmergeMe::~PmergeMe(){}
PmergeMe::PmergeMe(){}
PmergeMe::PmergeMe(const PmergeMe &){}
PmergeMe & PmergeMe::operator=(const PmergeMe &) {return *this;}

std::vector<int> PmergeMe::_data; 
std::deque<int> PmergeMe::_data2; 


std::vector<int>  PmergeMe::jakop(int size)
{

    std::vector<int> jsSequence;

    jsSequence.push_back(1);
    jsSequence.push_back(1);
    jsSequence.push_back(3);


    if (size < 3)
        return jsSequence;
    
    while (jsSequence.back() <= size)
        jsSequence.push_back(*(jsSequence.end() - 1) + (*(jsSequence.end() - 2) * 2));
    
    return jsSequence;
}

std::deque<int>  PmergeMe::jakop_deq(int size)
{

    std::deque<int> jsSequence;

    jsSequence.push_back(1);
    jsSequence.push_back(1);
    jsSequence.push_back(3);


    if (size < 3)
        return jsSequence;
    
    while (jsSequence.back() <= size)
        jsSequence.push_back(*(jsSequence.end() - 1) + (*(jsSequence.end() - 2) * 2));
    
    return jsSequence;
}

int PmergeMe::makePairs(const std::vector<int> & org, std::vector<int> & winners, std::vector<int> & loosers){

    int left = -1, right = -1;
    
    for(std::vector<int>::const_iterator it = org.begin() ; it != org.end(); it++)
    {
        
        left = *it;

        if ((it + 1) != org.end())
        {
            it++;
            right = (*it);
            winners.push_back (left > right ? left : right);
            loosers.push_back (left < right ? left : right);

        }
        else
            return left;
        
    }
    return -1;

}

int PmergeMe::makePairs(const std::deque<int> & org, std::deque<int> & winners, std::deque<int> & loosers){

    int left = -1, right = -1;
    
    for(std::deque<int>::const_iterator it = org.begin() ; it != org.end(); it++)
    {
        
        left = *it;

        if ((it + 1) != org.end())
        {
            it++;
            right = (*it);
            winners.push_back (left > right ? left : right);
            loosers.push_back (left < right ? left : right);

        }
        else
            return left;
        
    }
    return -1;

}

std::deque<int> PmergeMe::doMergeSort(std::deque<int> & data)
{
    std::deque<int> result;
    if (data.size() <= 1)
    {
        result = data;
        return result;
    }

    std::deque <int> winners;
    std::deque <int> loosers;

    int leftOver = makePairs(data, winners, loosers);

    result = doMergeSort(winners);

    std::deque<int> jsSequence = jakop_deq(loosers.size() + 1);

    int i = 0;
    int KKK = 0;
    while (i < (int)loosers.size())
    {
        int start = i;
        int end = i + jsSequence[KKK] - 1;
        KKK += 1;

        if (end > (int)loosers.size()) end = loosers.size() - 1;

        
        i = end + 1;
        while (true)
        {

            std::deque<int>::iterator winnerPos = std::find(result.begin(), result.end(), winners[end]);
            std::deque<int>::iterator insertionPoint = std::lower_bound(result.begin(), winnerPos, loosers[end]);
            
            result.insert(insertionPoint, loosers[end]);
            
            if (end == start)
                break;
            end -= 1;
            
        }
        
        
    }

    if (leftOver != -1)
    {
        std::deque<int>::iterator insertionPoint = std::lower_bound(result.begin(), result.end(), leftOver);
        result.insert(insertionPoint, leftOver);
    }

    return result;
}


std::vector<int> PmergeMe::doMergeSort(std::vector<int> & data)
{
    std::vector<int> result;
    if (data.size() <= 1)
    {
        result = data;
        return result;
    }

    std::vector <int> winners;
    std::vector <int> loosers;

    int leftOver = makePairs(data, winners, loosers);

    result = doMergeSort(winners);

    std::vector<int> jsSequence = jakop(loosers.size() + 1);

    int i = 0;
    int KKK = 0;
    while (i < (int)loosers.size())
    {

        int start = i;
        int end = i + jsSequence[KKK] - 1;
        KKK += 1;

        if (end > (int)loosers.size()) end = loosers.size() - 1;

        
        i = end + 1;
        while (true)
        {
            

            std::vector<int>::iterator winnerPos = std::find(result.begin(), result.end(), winners[end]);
            std::vector<int>::iterator insertionPoint = std::lower_bound(result.begin(), winnerPos, loosers[end]);
            
            result.insert(insertionPoint, loosers[end]);
            
            if (end == start)
                break;
            end -= 1;
            
        }
        
        
    }
    if (leftOver != -1)
    {
        std::vector<int>::iterator insertionPoint = std::lower_bound(result.begin(), result.end(), leftOver);
        result.insert(insertionPoint, leftOver);
    }

    return result;
}


void PmergeMe::parseInput(int ac, char **av)
{
    for (int i = 1; i < ac; i++)
    {
        std::stringstream ss;
        int value = 0;
        ss << av[i];
        ss >> value;

        if ((ss.fail() && !ss.eof()) || !ss.eof() || value < 0)
        {
            
            std::string msg;
            msg += "invalid value '";
            msg += av[i];
            throw std::runtime_error(msg);
        }

        _data.push_back(value);
        _data2.push_back(value);
    }
}



void PmergeMe::mergeSort(int ac, char **av){
    try
    {
        parseInput(ac, av);

        std::vector<int>::iterator it;
        for(it = _data.begin() ; it < _data.end(); it++)
            std::cout  << *it << " " ; 
        std::cout << std::endl;

        

        clock_t before = clock();
        std::vector<int> res = doMergeSort(_data);
        clock_t after = clock();
        
        for(size_t i = 0; i < res.size(); i++)
            std::cout << res[i] << " ";
        std::cout << std::endl;
        
        unsigned int vec_time = after - before / CLOCKS_PER_SEC * 1000000;
        
        
        before = clock();
        std::deque<int> res2 = doMergeSort(_data2);    
        after = clock();
        
        unsigned int deq_time = after - before / CLOCKS_PER_SEC * 1000000;
        
        std::cout << "Time to process a range of " << res2.size() << " elements with std::deque  : " << deq_time << " us" << std::endl;
        std::cout << "Time to process a range of "<< res.size() << " elements with std::vector : " << vec_time << " us" << std::endl;
        
    }
    catch(const std::exception& e)
    {
        std::cerr <<"Error : " <<  e.what() << '\n';
    }
    

}
