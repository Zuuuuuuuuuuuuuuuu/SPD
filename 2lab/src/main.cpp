#include <iostream>
#include <vector>
#include <utility>
#include <numeric>
#include <algorithm>
#include <cmath>

#include "priority_queue.hh"
#include "RandomNumberGenerator.hh"
#include "functions.hh"
#include "carlier.hh"

#define SEED 1
#define LOW 1
#define HIGH 29
#define NUM_ELEMENTS 12
using namespace std;

int main()
{
    vector<parameters> set (NUM_ELEMENTS); //zbiór wszystkich elementów
    vector<moments> moments (NUM_ELEMENTS+10); // zbiór czasów S i C
    // generating random numbers for parameters r (preparation time) and p (operation time)
    RandomNumberGenerator rng(SEED);

    for (int j=0; j<NUM_ELEMENTS; j++)
    {
        set[j].j = j+1;                       //j
    }
    for (int j=0; j<NUM_ELEMENTS; j++)
    {
        set[j].p = rng.nextInt(LOW, HIGH);   //p
    }
    int sum = 0;
    for (int i = 0; i < NUM_ELEMENTS; i++)
    {
        sum += set[i].p;                    //sum
    }
    
    for (int j=0; j<NUM_ELEMENTS; j++)
     {
         set[j].r = rng.nextInt(LOW, sum);   //r
     }
     for (int j=0; j<NUM_ELEMENTS; j++)
     {
         set[j].q = rng.nextInt(LOW, sum);   //q   DRUGA OPCJA (LOW, sum)
     }

    cout << "j :";
    print(set, 3);
    cout << "r :";
    print(set, 1);
    cout << "p :";
    print(set, 0);
    cout << "q :";
    print(set, 2);


    cout <<  evaluate1(set, moments) << endl << endl;
    //cout << "Schrage: " << evaluate1(evaluate2a(set), moments) << endl << endl;
    //cout << "Schrage z kolejką: " << evaluate1(evaluate2b(set), moments) << endl << endl;
    //cout << "Schrage z przerwaniami: " << evaluate1(evaluate2c(set), moments) << endl << endl;
    //cout << "test evaluate2a: " << evaluate2a(set) << endl;
    //cout << "Carlier: " << evaluate3(set, moments) << endl;

    //evaluate3(set, moments);
    cout << "Carlier: " << evaluate1(evaluate3(set, moments), moments) << endl << endl;

}