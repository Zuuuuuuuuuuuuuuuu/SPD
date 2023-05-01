#pragma once

#include<vector>
#include<cmath>
#include "parameters.hh"
using namespace std;

class dynamic : public parameters
{
    public:
        std::vector<int> memory;
        int minimum = 100000;
        void dynamic_programming_init(vector<parameters> set);
        int dynamic_programming(vector<parameters> set, vector<int> D);
};