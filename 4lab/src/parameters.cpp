#include "parameters.hh"

// generowanie liczb i wpisywanie do struktury
void parameters::write_generated_numbers(vector<parameters> &set)
{
    int sum = 0;
    RandomNumberGenerator rng(SEED);
    for (int j=0; j<NUM_ELEMENTS; j++)
    {
        set[j].j = j+1;                       
        sum = sum + set[j].j;
    }
    for (int j=0; j<NUM_ELEMENTS; j++)
    {
        set[j].p = rng.nextInt(LOW, HIGH);                       
        sum = sum + set[j].p;
    }
    for (int j=0; j<NUM_ELEMENTS; j++)
    {
        set[j].w = rng.nextInt(LOW, 9);                       
        set[j].d = rng.nextInt(LOW, sum); 
    }
}

// do wyświetlania wygenerowanych wartości
void parameters::print(const vector<parameters> set)  
{
    for (int i = 0; i < set.size(); i++)
    {
        cout << "j: " << set[i].j << "\t";
        cout << "p: " << set[i].p << "\t";
        cout << "w: " << set[i].w << "\t";
        cout << "d: " << set[i].d << "\t";
        cout << endl;
    }
    cout << endl;
}

// do liczenia wartosci cmax
int parameters::evaluate(const vector<parameters> set) 
{
    int S [NUM_ELEMENTS];
    int C [NUM_ELEMENTS];
    int T [NUM_ELEMENTS];
    int delay = 0;

    S[0] = 0;
    C[0] = set[0].p;
    T[0] = 0;
    for(int j = 1; j < NUM_ELEMENTS; j++)
    {
        S[j] = C[j-1];
        C[j] = S[j] + set[j].p;
        if (C[j] > set[j].d)
        {
            T[j] = C[j] - set[j].d;
        }
        else
        {
            T[j] = 0;
        }
        delay = delay + (T[j]*set[j].w); 
    }
    cout << "S: " << endl;
    for (int j = 0; j < NUM_ELEMENTS; j++)
    {
        cout << S[j] << "\t";
    }
    cout << endl << "C: " << endl;
    for (int j = 0; j < NUM_ELEMENTS; j++)
    {
        cout << C[j] << "\t";
    }
    cout << endl << "T: " << endl;
    for (int j = 0; j < NUM_ELEMENTS; j++)
    {
        cout << T[j] << "\t";
    }
    cout << endl;
    return delay;
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