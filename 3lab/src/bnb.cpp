#include "bnb.hh"

int bnbs::count_lb0(vector<parameters> pi, vector<parameters> N, vector<parameters> set)
{
    int x = pi.size();  // ile zadań uszeregowanych
    int sum_p;
    int lb0;
    int sum_c = evaluate(pi);   //cmax dla uszeregowanych zadan
    //int sum_c = set[x].c[NUM_MACHINES-1];    // czasy zakończenia zadania 
    for (int j=0; j<N.size(); j++)
    {
        sum_p += set[j].p[NUM_MACHINES-1];
    }
    return lb0 = sum_c + sum_p;
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
        bnb(j, N, pi, set);
    }

    return pi;
}


void bnbs::bnb(int j, vector<parameters> N, vector<parameters> pi, vector<parameters> set)
{
    pi.push_back(N[j]);
    N.erase(N.begin() + j); //usuniecie j-tego elementu z nieuszeregowanych

    if (!N.empty())
    {
        lb = count_lb0(pi, N, set);  // lub podmienić count_lb4
        if (lb < ub)
        {
            for (int j=0; j<N.size(); j++)
            {
                bnb(j, N, pi, set);
            }
        }
    }
    else 
    {
        int Cmax = evaluate(pi);
        if (Cmax < ub)
        {
            ub = Cmax;
            best_pi = pi;
        }
    }
}