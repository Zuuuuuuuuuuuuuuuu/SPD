#include "functions.hh"
#include "priority_queue.hh"
#include "RandomNumberGenerator.hh"

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <utility>
#include <numeric>
#include <algorithm>
#include <cmath>

using namespace std;

//ZWARACA ELEMENT O NAJMNIEJSZEJ WARTOŚĆI Q ZE ZBIORU SET
parameters minQ(vector<parameters> set)
{
    int minimum = 1000000;
    int element = 0;
    for(int j=0; j< set.size(); j++) 
	{
		if (minimum > set[j].q)
        {
            minimum = set[j].q;
            element = j;
        }
	}
    return set[element];
}

//zwraca informacje ktory element wektora ma najmniejsze rj
parameters minR(vector<parameters> set)
{
    int minimum = 1000;
    int element = 0;
    for(int j=0; j< set.size(); j++) //najkrotsza chwila czasowa wybra z r
	{
		if (minimum > set[j].r)
        {
            minimum = set[j].r;
            element = j;
        }
	}
    return set[element];
}

//zwraca informacje ktory element wektora ma najwieksze qj
parameters maxQ(vector<parameters> set)
{
    int maximum = 0;
    int element = 0;
    for(int j=0; j< set.size(); j++) //najkrotsza chwila czasowa wybra z r
	{
		if (maximum < set[j].q)
        {
            maximum = set[j].q;
            element = j;
        }
	}
    return set[element];
}

//wypisywanie elementów wektora 
template<typename T> ostream & operator<<(ostream &stream, const vector<T> vector)  
{     
    for(const T &i : vector) 
    {         
        stream << i << "\t";    
    }
    return stream; 
}

void print(const vector<parameters> set, int j)  // 0 - p, 1 - r, 2 - q
{
    cout << "\t";
    switch(j)
    {
        case 0:
        {
            for(int i = 0; i < set.size(); i++)
            {
		        cout << set[i].p << "\t";
            }
            break;
        }
        case 1:
        {
            for(int i = 0; i < set.size(); i++)
            {
		        cout << set[i].r << "\t";
            }
            break;
        }
        case 2:
        {
            for(int i = 0; i < set.size(); i++)
            {
		        cout << set[i].q << "\t";
            }
            break;
        }
        case 3:
        {
            for(int i = 0; i < set.size(); i++)
            {
		        cout << set[i].j << "\t";
            }
            break;
        }
    }
    cout << endl;
}

//liczenie wartosci funkcji celu
int evaluate1(const vector<parameters> set, vector<moments> &moments) 
{
    vector<int> S(set.size());
    vector<int> C(set.size());
    vector<int> Cq(set.size());
    S[0] = set[0].r;
    C[0] = S[0] + set[0].p;
    Cq[0] = C[0] + set[0].q;
    moments[0].S = S[0];
    moments[0].C = C[0];
    moments[0].num = set[0].j;
    int maximum=Cq[0];
    for (int j=1; j<set.size(); j++)
    {
        S[j] = max(set[j].r, C[j-1]);
        C[j] = S[j] + set[j].p;
        Cq[j] = C[j]+set[j].q;
        maximum = max(maximum, Cq[j]);
        moments[j].S = S[j];
        moments[j].C = C[j];
        moments[j].num = set[j].j;
    }
    cout << endl << "S:\t" << S << endl << "C:\t" << C << endl << "Cq:\t" << Cq << endl;
    return maximum;
}


 vector<parameters> evaluate2a(vector<parameters> set) 
{
    vector<parameters> PI(set.size()); //harmonogram
    int k = 0; //numer rozpatrywanej permutacji
    vector<parameters> G; //zadania gotowe do realizacji
    parameters J; //zadanie
    int t = minR(set).r; //zmienna czasu
    while((!(G.empty())) || (!(set.empty())))
    {
        while((!(set.empty())) && (minR(set).r <= t))
        {
            J = minR(set);
            G.push_back(J);
            for(int i = 0; i < set.size(); i++)
            {
                if((set[i].p == J.p) && (set[i].r == J.r) && (set[i].q == J.q))
                {
                    set.erase(set.begin()+i);
                }
            }
        }
        if (!(G.empty()))
        {
            parameters maxQj = maxQ(G);
            for(int i = 0; i < G.size(); i++)
            {
                if((G[i].p == maxQj.p) &&(G[i].r == maxQj.r) &&(G[i].q == maxQj.q) )
                {
                    G.erase(G.begin()+i);
                }
            }
            PI[k] = maxQj;
            t = t + maxQj.p;
            k++;
        }
        else
        {
            t = minR(set).r;
        }
    }
    
    return PI;
}

vector<parameters> evaluate2b(vector<parameters> set) 
{
    vector<parameters> PI(set.size()); //harmonogram
    int k = 0; //numer rozpatrywanej permutacji
    prio_q G; //zadania gotowe do realizacji uporządkowane wg. maxP
    prio_q N; //zadania uporządkowane wg. minR
    for (int i = 0; i < set.size(); i++)
    {
        N.insert(set[i], 1000-set[i].r);
    }
    int t = N.max().r; //zmienna czasu
    while((!(G.isEmpty())) || (!(N.isEmpty())))
    {
        while((!(N.isEmpty())) && (N.max().r <= t))
        {
            G.insert(N.max(), (N.max()).q); //do G dodaje pierwszy element z N (najwyzszy priorytet)
            N.removeMax(); //usuwa 1 element
        }
        if (!(G.isEmpty()))
        {
            PI[k] = G.max(); //pierwszy element z G
            t = t + (G.max()).p;
            G.removeMax(); //usuwa 1 element
            k++;
        }
        else
        {
            t = N.max().r;
        }
    }
    cout << endl << "j :";
    print(PI, 3);
    cout << "r :";
    print(PI, 1);
    cout << "p :";
    print(PI, 0);
    cout << "q :";
    print(PI, 2);
    return PI;
}

vector<parameters> evaluate2c(vector<parameters> set) 
{
    vector<parameters> PI(15); //harmonogram
    int k = 0; //numer rozpatrywanej permutacji
    prio_q G; //zadania gotowe do realizacji uporządkowane wg. maxP
    prio_q N; //zadania uporządkowane wg. minR
    for (int i = 0; i < set.size(); i++)
    {
        N.insert(set[i], 1000-set[i].r); //stworzenie kolejki uszeregowanej po r
    }
    int t = N.max().r; //zmienna czasu

    while((!(G.isEmpty())) || (!(N.isEmpty())))
    {
        while((!(N.isEmpty())) && (N.max().r <= t))
        {
            G.insert(N.max(), (N.max()).q); //do G dodaje pierwszy element z N (najwyzszy priorytet)
            N.removeMax(); //usuwa 1 element
            ////
        }
        if (!(G.isEmpty()))
        {
            if (t > G.max().r)
            {
                if(PI[k-1].q < G.max().q)
                {
                    parameters cofka = PI[k-1];
                    cofka.p = (t - G.max().r); // zmiejszyc czas
                    PI[k-1].p = PI[k-1].p - (t - G.max().r);
                    G.insert(cofka, cofka.q);
                    t = (G.max().r);
                }
            }
            PI[k] = G.max(); //pierwszy element z G
            t = t + (G.max()).p;
            G.removeMax(); //usuwa 1 element
            k++;
        }
        else
        {
            t = N.max().r;
        }
    }
    cout << endl << "j :";
    print(PI, 3);
    cout << "r :";
    print(PI, 1);
    cout << "p :";
    print(PI, 0);
    cout << "q :";
    print(PI, 2);
    return PI;
}