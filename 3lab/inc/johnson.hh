#pragma once
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <utility>
#include <numeric>
#include <algorithm>
#include <cmath>
#include "parameters.hh"
using namespace std;

class johnsons : public parameters
{
    public:
        vector<parameters> johnson(vector<parameters> set);
        vector<parameters> johnson2maszyny(vector<parameters> set);
        
};