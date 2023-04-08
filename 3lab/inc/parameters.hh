#pragma once
#include <vector>
#include <iostream>
#include "RandomNumberGenerator.hh"

#define SEED 1
#define LOW 1
#define HIGH 29
#define NUM_ELEMENTS 8
#define NUM_MACHINES 2

using namespace std;

class parameters : public RandomNumberGenerator
{
    public:
        int j;
        vector<int> p;
        // int Cmax;

        parameters() : RandomNumberGenerator(SEED) {}   //konstruktor
        void write_generated_numbers(vector<parameters> &set);
        void print(const vector<parameters> set);
        int evaluate(const vector<parameters> set);

};

template<typename T> ostream & operator<<(ostream &stream, const vector<T> vector);