#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <exception>
#include <vector>
#include <sstream>
#include <algorithm>
#include <chrono>

class PmergeMe {
    private:
        static std::vector<int> _data;
        static std::vector<int> jakop(int);
        static void parseInput(int ac, char **av);
        static std::vector<int> doMergeSort(std::vector <int> &);
        static int makePairs(const std::vector<int> & org, std::vector<int> & winners, std::vector<int> & loosers);
    
        static void makePairs();
        PmergeMe();
        PmergeMe(const PmergeMe &);
        PmergeMe &operator=(const PmergeMe &);
        
    public:
        ~PmergeMe();
        static void mergeSort(int ac, char **av);

};


#endif //jacopstall