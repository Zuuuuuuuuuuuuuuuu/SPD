#include "dynamic.hh"

void dynamic::dynamic_programming_init(vector<parameters> set)
{
    vector<int> D;
    for (int i = 0; i < set.size(); i++)
    {
        D.push_back(set[i].j);  //D przetrzymuje zbior zadan
    }
    int size = std::pow(2, D.size()) - 1; // rozmiar 2^n -1
    //vector<int> memory(size, -1);  // utworzenie tablicy o rozmiarze i wypelnienie wartosciami -1
    for (int i=0; i<size; ++i)
    {
        memory.push_back(-1);   //wypelnienie tablicy wartosciami -1
    }
    dynamic_programming(set, D);
}

int dynamic::dynamic_programming(vector<parameters> set, vector<int> D)
{
    int sum = 0;
    for (int j=0; j<D.size(); ++j)
    {
        sum += set[j].p;  //suma wszystkich czasow w podproblemie
    }
    int max_value = 0;
    int max_value_weight;
    int tmp;
    for (int j=0; j<D.size(); ++j)
    {    
        tmp = max(sum-set[j].d, 0);
        if (tmp > max_value)
        {
            max_value = tmp;
            max_value_weight = max_value * set[j].w;  // max{sum-dj,0}wj
        }
    }
    int memory_fd = 0;
    for (int j=0; j<D.size(); ++j)
    {
        D.erase(D.begin()+j);
        if (memory[j] != -1) //??
        {
            memory_fd = memory[j];
        }
        else
        {
            dynamic_programming(set, D);
        }
        tmp = max_value_weight + memory_fd;
        if (tmp < minimum)
        {
            minimum = tmp;
        }
        // w ktorym momencie wpisywac do tablicy memory i co ?? 
    }
return minimum;
}