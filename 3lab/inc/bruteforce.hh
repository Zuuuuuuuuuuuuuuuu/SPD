#pragma once
#include<climits>
#include<vector>
#include "parameters.hh"
#include "johnson.hh"
using namespace std;

class bruteforce : public johnsons
{
    public:
        int ub; 
        vector<parameters> init_brute(vector<parameters> set);
        void brute(int j, vector<parameters> N, vector<parameters> pi);
        vector<parameters> bestpi;
};