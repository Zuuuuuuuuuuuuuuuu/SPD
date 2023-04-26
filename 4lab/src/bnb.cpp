#include "bnb.hh"

int bnbs::count_lb0(vector<parameters> pi, vector<parameters> N)
{
    int x = pi.size();  // ile zadań uszeregowanych
    int sum_p = 0;
    int lb0 = 0;
    int sum_c = evaluate(pi);   //cmax dla uszeregowanych zadan
    //int sum_c = set[x].c[NUM_MACHINES-1];    // czasy zakończenia zadania 
    for (int j=0; j<N.size(); j++)
    {
        sum_p += N[j].p[NUM_MACHINES-1];
    }
    return lb0 = sum_c + sum_p;
}

int bnbs::count_lb3(vector<parameters> pi, vector<parameters> N)
{
    int C = 0;
    int PIJ = 0;
    int maximum = 0;
    int temp = 0;
    int minimum = 0;
    for(int j = 0; j < NUM_MACHINES; j++)
    {
        for(int i = 0; i < pi.size(); i++)
        {
            C = C + pi[i].p[j];
        }
        for(int i = 0; i < N.size(); i++)
        {
            PIJ = PIJ + N[i].p[j];
        }
        for(int k = j+1; k<NUM_MACHINES; k++)
        {
            for(int j = 0; j < N.size(); j++)
            {
                temp = N[j].p[k];
                if(temp < minimum)
                {
                    minimum = temp;
                }    
            }
        }
        if(C+PIJ+minimum > maximum)
        {
            maximum = C+PIJ+minimum;
        }
    }
    return maximum;
}


//inicjacja algorytmu podziału i ograniczeń
vector<parameters> bnbs::init_bnb(vector<parameters> set)
{
    vector<parameters> N;
    vector<parameters> pi;
    
    ub = evaluate(johnson(set));   // ewentualnie do zmiany przy rozwoju algorytmu

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
        lb = count_lb3(pi, N);  // lub podmienić count_lb4
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
        if (Cmax <ub)
        {
            ub = Cmax;
            best_pi = pi;
        }
    }
}