#pragma once
#include<climits>
#include<vector>
#include "parameters.hh"
#include "johnson.hh"
using namespace std;

class bnbs : public johnsons
{
    public:
        int ub;   // wartość górnego ograniczenia; uboga wersja algorytmu
        //int count_ub();
        int lb;
        int count_lb(vector<parameters> N, vector<parameters> pi);
        vector<parameters> init_bnb(vector<parameters> set);
        void bnb(int j, vector<parameters> N, vector<parameters> pi);
        
};