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
        int lb;
        vector<parameters> best_pi;
        int count_lb0(vector<parameters> pi, vector<parameters> N);
        int count_lb3(vector<parameters> N, vector<parameters> pi);
        vector<parameters> init_bnb(vector<parameters> set);
        void bnb(int j, vector<parameters> N, vector<parameters> pi, vector<parameters> set);
        
};