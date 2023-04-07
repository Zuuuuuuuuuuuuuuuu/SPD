#include "carlier.hh"
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

vector<parameters> evaluate3(vector<parameters> set, vector<moments> moments)
{
    int U;
    vector<parameters> PI = evaluate2b(set);    //czy samo evaluate2b czy evaluate1(ev2(set)) ???????
    vector<parameters> pi_asterisk(20); // pi
    U = evaluate1(PI, moments); //zwraca Cmax i są zapisane czasy C i S
    int UB = 100000000; 
    int LB = 0;
    if (U < UB)
    {
        UB = U; // za pierwszym razem nowe górne oszacowanie
        pi_asterisk = PI; 
    }

    // wyliczanie b:
    int b;
    int max = 0;
    int tmp_b;
    for (int j=0; j<set.size(); j++)
    {
        tmp_b = moments[j].C + set[j].q;
        if (tmp_b > max)
        {
            max = tmp_b;
            b = j; 
        }
    }

    // wyliczanie a:
    int a;
    int min = 1000000;
    for (int j=0; j<set.size(); j++)
    {
        int sum = 0;
        for (int k=j; k<b; k++)
        {
            sum += set[k].p;    // suma od j do b wszystkich p
        }
        int tmp = set[j].r + sum + set[j].q;  // int tmp = set[j].r + sum + set[j].q
        if (tmp < min)
        {
            min = tmp;
            a = j;   // zwróci numer zadania o najmniejszej tej sumie;sum63
        }
    }

    // wyliczanie c:
    int c=-1;
    for (int j=a; j<b; j++)
    {
        if (set[j].q < set[b].q && j>c) // j>c bo funkcja max
        {
            c = j;  // z bloku (a,b) wyszukuje zadanie o najwyższej pozycji
        }
    }
    if (c == -1) 
    {
        return pi_asterisk;
    }

   std::vector<parameters> K;
   for(int i = c+1; i <= b; i++)
   {
    K.push_back(set[i]);
   }
   
   int r_k = minR(K).r;
   int q_k = minQ(K).q;
   int p_k = 0;
   for (int j=0; j<K.size(); j++)
   {
    p_k += K[j].p;
   }
   
   int r_pi_c = set[c].r;
   set[c].r = std::max(set[c].r, r_k+p_k);

   LB = evaluate1(evaluate2c(set), moments);
   if (LB < UB)
   {
    auto carl = evaluate3(set, moments);  // rekurencja
   }

   set[c].r = r_pi_c;  //restore

//to samo dla q
   int q_pi_c = set[c].q;
   set[c].q = std::max(set[c].q, q_k+p_k);

   LB = evaluate1(evaluate2c(set), moments);
   if (LB < UB)
   {
    auto carl = evaluate3(set, moments);  // rekurencja
   }

   set[c].q = q_pi_c;  //restore

   return pi_asterisk;   
}