#include "bnb.hh"

int bnbs::count_lb(vector<parameters> N, vector<parameters> pi)
{
    return 0;   // dorobić
}


//inicjacja algorytmu podziału i ograniczeń
vector<parameters> bnbs::init_bnb(vector<parameters> set)
{
    vector<parameters> N;
    vector<parameters> pi;

    ub = INT_MAX;   // ewentualnie do zmiany przy rozwoju algorytmu

    for (int i = 0; i < set.size(); i++)
    {
        N.push_back(set[i]);
    }

    for (int j=0; j<N.size(); j++)
    {
        bnb(j, N, pi);
    }

    return pi;
}


void bnbs::bnb(int j, vector<parameters> N, vector<parameters> pi)
{
    vector<parameters> best_pi;
    pi.push_back(N[j]);
    N.erase(N.begin() + j);

    if (!N.empty())
    {
        lb = count_lb(pi, N);
        if (lb < ub)
        {
            for (int j=0; j<N.size(); j++)
            {
                bnb(j, N, pi);
            }
        }
    }
    else 
    {
        int Cmax = evaluate(pi);
        if (Cmax < ub)
        {
            ub = Cmax;
            best_pi = pi;   // ??
        }
    }
}