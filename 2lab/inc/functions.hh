#ifndef FUNCTIONS
#define FUNCTIONS
#include "priority_queue.hh"
#include <vector>
#include <iostream>
using namespace std;

struct moments
{
    int S;
    int C;
    int num;    //numer zadania
};

parameters minQ(vector<parameters> set);
parameters minR(vector<parameters> set);
parameters maxQ(vector<parameters> set);
template<typename T> ostream & operator<<(ostream &stream, const vector<T> vector);  
void print(const vector<parameters> set, int j);
int evaluate1(const vector<parameters> set, vector<moments> &moments);
vector<parameters> evaluate2a(vector<parameters> set);
vector<parameters> evaluate2b(vector<parameters> set);
vector<parameters> evaluate2c(vector<parameters> set);

#endif