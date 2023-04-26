#include "parameters.hh"

// generowanie liczb i wpisywanie do struktury
void parameters::write_generated_numbers(vector<parameters> &set)
{
    RandomNumberGenerator rng(SEED);
    for (int j=0; j<NUM_ELEMENTS; j++)
    {
        set[j].j = j+1;                       //j
    }
    for (int j=0; j<NUM_ELEMENTS; j++)
    {
        for (int i=0; i<NUM_MACHINES; i++)
        {
            set[j].p.push_back(rng.nextInt(LOW, HIGH));   //p
        }
    }
}

// do wyświetlania wygenerowanych wartości
void parameters::print(const vector<parameters> set)  // 0 - p, 1 - r, 2 - q
{
    for (int i = 0; i < set.size(); i++)
    {
        cout << "j: " << set[i].j << "\t";
        cout << "p: ";
        for (int j = 0; j < set[i].p.size(); j++)
        {
            cout << set[i].p[j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

// do liczenia Cmax
int parameters::evaluate(const vector<parameters> set) 
{
    int S [set.size()][set[0].p.size()];
    int C [set.size()][set[0].p.size()];
    int maximum=0;

    S[0][0] = 0;
    C[0][0] = set[0].p[0];
    for(int j = 1; j < set[0].p.size(); j++)
    {
        S[0][j] = C[0][j-1];
        C[0][j] = S[0][j] + set[0].p[j];
    }

    for (int m = 1; m < set.size(); m++)
    {
        for (int n = 0; n < set[0].p.size(); n++)
        {
            if (n == 0)
            {
                S[m][0] = C[m-1][0];
            }
            else
            {
                S[m][n] = max(C[m][n-1],C[m-1][n]);
            }
            C[m][n] = S[m][n] + set[m].p[n];
            maximum = max(maximum, C[m][n]);      
        }
    }
    return maximum;
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