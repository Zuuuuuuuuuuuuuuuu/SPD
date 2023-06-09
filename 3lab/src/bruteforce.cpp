#include "bruteforce.hh"

//inicjacja algorytmu podziału i ograniczeń
vector<parameters> bruteforce::init_brute(vector<parameters> set)
{
    vector<parameters> N;
    vector<parameters> pi;

    ub = 1000; 

    for (int i = 0; i < set.size(); i++)
    {
        N.push_back(set[i]);
    }

    for (int j=0; j<N.size(); j++)
    {
        brute(j, N, pi);
    }

    return pi;
}


void bruteforce::brute(int j, vector<parameters> N, vector<parameters> pi)
{
    pi.push_back(N[j]);
    N.erase(N.begin() + j);

    if (!N.empty())
    {

        for (int j=0; j<N.size(); j++)
        {
           brute(j, N, pi);
        }
    }
    else 
    {
        int Cmax = evaluate(pi);
        if (Cmax < ub)
        {
            ub = Cmax;
            bestpi = pi;  
        }
    }
}