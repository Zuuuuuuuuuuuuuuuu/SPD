#include <vector>
#include "parameters.hh"
#include "RandomNumberGenerator.hh"
#include <stdio.h>
#include <queue>
#include <functional>
#include <algorithm>
#include <tuple>
#include <map>
using namespace std;

int evaluate(const vector<parameter*> &set) 
{
    int lastM = set[0]->last(); // ostatnia maszyna
    int lastP = set.size() - 1; // ostatnie zadanie

    for (int i = 0; i <= lastM; ++i) //dla kazdej maszyny
     {
        for (int j = 0; j <= lastP; ++j) //dla kazdego zadania
         { 
            int Cmax;       //aktualne zadanie
            int lastCmax;   
            int maximum; 
            int p = set[j]->op[i].p; // czas trwania obecnego zadania

            if(i == 0) //maszyna 1
            { 
                lastCmax = 0;
                if(j == 0) //zadanie 1
                {
                     Cmax = 0 + p;
                } 
                else 
                {
                    Cmax = set[j-1]->op[i].C + p; //poprzednio zakonczone + czas trwania tego
                }
            } 
            else 
            { 
                lastCmax = set[j]->op[i-1].C; //koniec zadania na poprzedniej maszynie
                if(j == 0) 
                {
                    maximum = 0; 
                }
                else 
                {
                    maximum = set[j-1]->op[i].C; //Cmax na obecnej maszynie koniec zadania na poprzednije
                }
                Cmax = max(lastCmax, maximum) + p; 
            }
            set[j]->op[i].C = Cmax; // ustaw czas zakończenia obecnego zadania na obecnej maszynie równy Cmax
        }
    }
    return set[lastP]->op[lastM].C; // ostatnie zadanie z ostatniej maszyny
}


//najkrotszy czas wykonania
inline parameter* minP(const vector<parameter*> &set, int *it) 
{
    parameter* minP = set[0]; // wskaźnik na najlepsze zadanie
    *it = 0;

    for(int i = 0; i < set.size(); ++i) //dla zadania
    { 
        int firstTime = set[i]->op[0].p;               // czas trwania na pierwszej maszynie
        int lastTime = set[i]->op[minP->last()].p;     // czas trwania na ostatniej maszynie
        int bestFirst = minP->op[0].p;                 // czas trwania najlepszego zadania na pierwszej maszynie
        int bestLast = minP->op[minP->last()].p;       // czas trwania najlepszego zadania na ostatniej maszynie

        if(firstTime < bestFirst) 
        { 
            if (firstTime < bestLast) 
            { 
                minP = set[i]; 
                *it = i;       
            }
        }
        if(lastTime < bestFirst) 
        { 
            if(lastTime < bestLast) 
            { 
                minP = set[i]; 
                *it = i; 
            }
        }
    }
    return minP;
}


//sciezka krytyczna
vector<tuple<int, int>> criticalPath(vector<parameter*> PI) 
{
    int m = PI[0]->op.size() - 1; // aktualna maszyna
    auto n = PI.back();           // aktualne zadanie
    int index = PI.size() - 1;    // index aktualnego parameteru
    vector<tuple<int, int>> J;    // wektor -> zadanie, maszyna
    evaluate(PI);                 // aktualne C i S
    J.push_back({index, m});      // ostatnie zadanie jako 1 w sciezce

    while(index > 0) //dopoki nie osiagniemy pierwszego zadania
    { 
        int start = n->op[m].C - n->op[m].p; // czas rozpoczęcia zadania 
        int prevC = PI[index-1]->op[m].C;    // czas końca poprzedniego zadania

        if(prevC == start) // jesli nowe sie zaczyna tam gdzie stare konczy
        { 
            index--; 
            J.push_back({index, m}); 
            n = PI[index];
        } 
        else 
        { 
            m--; 
            J.push_back({index, m}); 
        }
    }
    return J;
}

//powownuje czas wykonywania dla a i b
bool compare(parameter* a, parameter* b) 
{
    int sumA = 0;
    int sumB = 0;

    for (size_t i = 0; i < a->op.size(); i++)
    {
        sumA += a->op[i].p; //suma czasow w a
    }

    for (size_t i = 0; i < b->op.size(); i++)
    {
        sumB += b->op[i].p; //sumac zasow w b
    }

    return sumA < sumB;
}

//wstawia zadanie w optymalne miejsce
vector<parameter*> insertNeh(vector<parameter*> PI, parameter* parameter) 
{
    int minCmax = 100000; 
    int index;
    for (size_t l = 0; l <= PI.size(); l++) // dla każdej pozycji
    {
        PI.insert(PI.begin() + l, parameter); // dodaj zadanie
        int tmp = evaluate(PI); // policz Cmax
        if(tmp < minCmax) 
        { 
            minCmax = tmp;
            index = l;
        }
        PI.erase(PI.begin() + l); // usuń zadanie z tej pozycji 
    }
    PI.insert(PI.begin() + index, parameter); // dodaj zadanie w best pozycji
    return PI;
}

vector<parameter*> NEH(vector<parameter*> set) 
{
    vector<parameter*> PI;
    sort(set.begin(), set.end(), compare); // posortuj od najdłuższych czasów wykonania
    while(!set.empty()) 
    {
        auto j = set.back(); // weź zadanie o najkrotszym czasie
        PI = insertNeh(PI, j); // wstaw w najlepszej pozycji
        set.pop_back(); 
    }
    return PI;
}

vector<parameter*> NEH1(vector<parameter*> set) //zadanie z najdluzsza operacja na scieżce krytycznej
{
    vector<parameter*> PI;
    sort(set.begin(), set.end(), compare); // posortuj od najdłuższych czasów wykonania
    while(!set.empty()) 
    {
        auto j = set.back(); //zadanie o najkrotszy czasie
        PI = insertNeh(PI, j); 
        set.pop_back(); 
        auto path = criticalPath(PI); // liczymy ścieżkę krytyczną
        parameter* found; // zadanie z najdluzszym czasie
        int indexF; // indeks 
        int max = 0; // maksymalny czas
        for (size_t i = 0; i < path.size(); i++) // dla każdej operacji
        {
            auto parameter = PI[get<0>(path[i])];
            auto p = parameter->op[get<1>(path[i])].p;
            if(p > max) 
            {
                max = p;
                found = parameter;
                indexF = get<0>(path[i]);
            }
        }        
        PI.erase(PI.begin() + indexF); 
        PI = insertNeh(PI, found); 
    }
    return PI;
}

vector<parameter*> NEH2(vector<parameter*> set) //największa suma operacji w ścieżce krytycznej
{
    vector<parameter*> PI;
    sort(set.begin(), set.end(), compare); // posortuj od najdłuższych czasów wykonania
    while(!set.empty()) 
    {
        auto j = set.back(); // weź zadanie o najkrotszym czasie
        PI = insertNeh(PI, j); // wstaw w najlepszej pozycji
        set.pop_back(); 
        auto path = criticalPath(PI); //ścieżka krytyczna
        parameter* found; // znalezione zadanie
        int indexF; // indeks znalezionego zadania
        int max = 0;
        int tab[path.size()];
        for(int i = 0; i < path.size(); i++)
        {
            tab[i] = 0;
        }
        for (size_t i = 0; i < path.size(); i++) // dla każdej operacji
        {
            auto index = get<0>(path[i]);
            auto parameter = PI[index];
            auto p = parameter->op[get<1>(path[i])].p;            
            tab[index] += p;
        }

        for(size_t i = 0; i < path.size(); i++) 
        {
            if(max< tab[i])
            {
                max = tab[i];
                indexF = i;
            }
        }
        found = PI[indexF];
        PI.erase(PI.begin() + indexF); 
        PI = insertNeh(PI, found); 
    }    
    return PI;
}