#include "johnson.hh"

// algorytm Johnsona na wiele maszyn
vector<parameters> johnsons::johnson(vector<parameters> set)
{
    vector<parameters> N;
    for (int i = 0; i < set.size(); i++)
    {
        N.push_back(set[i]);
    }
    int l = 0;
    int k = set.size()-1;
    int minimum = 1000;
    int i;
    int j;
    int tmp;
    vector<parameters> PI(N.size());
    while (N.size())
    {
        for (int g = 0; g < N.size(); g++)
        {
            tmp = *min_element(N[g].p.begin(), N[g].p.end());
            if (tmp < minimum)
            {
                for (int h = 0; h < N[h].p.size(); h++)
                {
                    if(tmp == N[g].p[h])
                    {
                        j = g;
                        i = h;
                        minimum = tmp;
                    }
                }
            }
        }
        minimum = 1000;
        int p1 = N[j].p[0];
        int p2 = N[j].p[N[0].p.size()-1];
        if (p1 < p2)
        {       
                PI[l] = N[j];
                l++;
        }
        else
        {
                PI[k] = N[j];
                k--;
        }
        N.erase(N.begin()+j);
    }
    return PI;
}

//algorytm Johnsona na 2 maszyny
vector<parameters> johnsons::johnson2maszyny(vector<parameters> set)
{
    vector<parameters> N;
    for (int i = 0; i < set.size(); i++)
    {
        N.push_back(set[i]);
    }
    int l = 0;
    int k = set.size()-1;
    int minimum = 1000;
    int i;
    int j;
    int tmp;
    vector<parameters> PI(N.size());
    while (N.size())
    {
        for (int g = 0; g < N.size(); g++)
        {
            tmp = *min_element(N[g].p.begin(), N[g].p.end());
            if (tmp < minimum)
            {
                for (int h = 0; h < N[h].p.size(); h++)
                {
                    if(tmp == N[g].p[h])
                    {
                        j = g;
                        i = h;
                        minimum = tmp;
                    }
                }
            }
        }
        minimum = 1000;
        if (N[j].p[0] < N[j].p[1])
        {       
                PI[l] = N[j];
                l++;
        }
        else
        {
                PI[k] = N[j];
                k--;
        }
        N.erase(N.begin()+j);
    }
    return PI;
}