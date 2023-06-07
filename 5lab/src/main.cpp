#include "harmonogram.hh"
#include <chrono>
#include <iostream>
#include <math.h>
#include <iostream>
using namespace std;

//tworzy zbior parametrow
std::vector<parameter*> generateoperations(const int &n, const int &m, const int &seed)
 {
    RandomNumberGenerator randf(seed);
    std::vector<parameter*> set;

    for(int j = 1; j <= n; ++j) 
	{
        parameter* tmp = new parameter();
        for(int i = 1; i <= m; ++i) 
		{
            tmp->addoperation(operation(j, randf.nextInt(1, 29))); //generowanie operacji
        }
        set.push_back(tmp);
    }
    return set;
}

//wypisuje wektor 
void print(const std::vector<parameter*> &set)
 {
	cout << "[";
    for(int i = 0; i < set.size(); ++i) 
	{
        cout << set[i]->op[0].j;
        if(i != set.size() - 1)
		{
			 cout << ", ";
		}
    }
    cout << "]" << endl;
    cout << evaluate(set);
    cout << endl << endl;
}


int main() 
{
    int SEED = 1;
    int NUM_OPERATIONS = 100;
    int NUM_MACHINES = 6;
    std::vector<parameter*> set = generateoperations(NUM_OPERATIONS, NUM_MACHINES, SEED);
	cout << endl;
	cout << "KOLEJNOSC" << endl;
    print(set);
	cout << "NEH" << endl;
    print(NEH(set));
    cout << "NEH1" << endl;
    print(NEH1(set));
    cout << "NEH2" << endl;
    print(NEH2(set));
    return 0;
}
