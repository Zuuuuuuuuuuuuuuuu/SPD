#include <iostream>
#include <cmath>
#include <stdio.h>
#include <vector>
#include <numeric>
#include "RandomNumberGenerator.h"

using namespace std;

//wypisywanie elementów fektora
template<typename T>
ostream & operator<<(ostream &stream, const vector<T> vector) 
{
	for(const T &i : vector) {
		stream << i << "\t";
	}

	return stream;
}

//funkcja dostaje 3 wektory pj, rj i j
int evaluate(const vector<int> &pj, const vector<int> &rj, const vector<int> &j) 
{
    //ustawienie wartosci maksimum na 0
	int maximum = 0;
    //po kolei przez wszystkie wartosci wektora j
	for(size_t i=0; i<j.size(); i++) 
    {
        //wybieram maksymalna wartosc pomiedzy obecnym maxiumum a kolejna wartoscia w wektorze rj
		const int S = max(rj[j[i]-1], maximum);
        //zmiana wartosci maksiumum
		maximum = S + pj[j[i]-1];
	}
	return maximum;
}

int main()
{
    //generowanie ziarna
	RandomNumberGenerator rng(1);
	
    //stworzenie wektora j i wypełnienie go kolejnymi wartościami (1-10)
	vector<int>j(10);
	iota(j.begin(), j.end(), 1);

    //stworzenie wektora pj i wypełnienie go wartościami z RandomNumber Generator
	vector<int> pj(10);
	for(int &i : pj)
    {
		i = rng.nextInt(1, 29);
    }

    //zliczenie sumy wartości z pj
	const int suma = accumulate(pj.begin(), pj.end(), 0);

    //stworzenie wektora rj i wypełnienie go wartościami z RandomNumber Generator
	vector<int> rj(10);
	for(int &i : rj)
    {
		i = rng.nextInt(1, suma);
    }

    //wypisanie danych
	cout << "j: " << j << endl;
	cout << "rj: " << rj << endl;
	cout << "pj: " << pj << endl;

    //wypisanie rozwiazania
	cout << evaluate(pj, rj, j) << endl;
}
