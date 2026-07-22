#include "PmergeMe.hpp"

PmergeMe::~PmergeMe(){}
PmergeMe::PmergeMe(){}
PmergeMe::PmergeMe(const PmergeMe &){}
PmergeMe & PmergeMe::operator=(const PmergeMe &) {return *this;}

std::vector<int> PmergeMe::_data; 

int jj(int i)
{
    if (i == 0 || i == 1)
        return i;
    return jj(i - 1) + (jj(i - 2) * 2);
}

std::vector<int>  PmergeMe::jakop(int size)
{

    std::vector<int> jsSequence;

    jsSequence.push_back(1);
    jsSequence.push_back(1);
    jsSequence.push_back(3);


    if (size < 3)
        return jsSequence;// understade
    
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
        else //one element
            return left;
        
    }
    return -1;

}

void put(const std::vector<int> lst)
{
    for(size_t i = 0; i < lst.size(); i++)
        std::cout << lst[i] << " ";

    std::cout << std::endl;
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
    std::cout << "JakopStall Seq: " << jsSequence.size() << "  => ";
    put(jsSequence);


    
    std::cout << "loosers : "; put(loosers); 
    int i = 0;
    int KKK = 0;
    while (i < (int)loosers.size())
    {
        // std::cout <<"i -> |" << i <<"|"<< loosers.size() << std::endl;
        // std::chrono::high_resolution_clock::time_point sss = std::chrono::high_resolution_clock::now();
        int start = i;
        int end = i + jsSequence[KKK] - 1;
        KKK += 1;
        // std::chrono::high_resolution_clock::time_point done = std::chrono::high_resolution_clock::now();
        
        // std::chrono::microseconds durration = std::chrono::duration_cast<std::chrono::microseconds>(done - sss);
        // std::cout << "time : " << durration.count() << std::endl;
        // std::cout << "##### " << i << " + " << jsSequence[i] << " = " << end << std::endl;
        if (end > (int)loosers.size()) end = loosers.size() - 1; // 
        // std:: cout << "start: " << start << ", end: " << end << std::endl;
        // std::cout << "range: ";
        // for(int tmp = start; tmp <= end; tmp++)
        //     std::cout << loosers[tmp] << " ";
        // std::cout << "\n";
        
        i = end + 1;
        while (true)
        {
            
            //  std::cout <<"j -> |" << end <<"|"<< std::endl;
            std::vector<int>::iterator winnerPos = std::find(result.begin(), result.end(), winners[end]);
            std::vector<int>::iterator insertionPoint = std::lower_bound(result.begin(), winnerPos, loosers[end]);
            
            result.insert(insertionPoint, loosers[end]);
            
            if (end == start)
                break;
            end -= 1;
            
        }
        
        
    }
    // std::cout << std::endl;
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
    }
}



void PmergeMe::mergeSort(int ac, char **av){
    try
    {
        parseInput(ac, av);
        std::vector<int>::iterator it;
        for(it = _data.begin() ; it < _data.end(); it++)
            std::cout << "[" << *it << "] " ; 
        std::cout << std::endl;
        std::vector<int> res = doMergeSort(_data);
        for(size_t i = 0; i < res.size(); i++)
            std::cout << res[i] << " ";
        std::cout << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr <<"Error : " <<  e.what() << '\n';
    }
    

}
