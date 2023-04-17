#include <iostream>

#include "parameters.hh"
#include "RandomNumberGenerator.hh"
#include "johnson.hh"
#include "bruteforce.hh"


int main()
{
    vector<parameters> set (NUM_ELEMENTS);
    vector<parameters> PI;
    parameters j;
    parameters class_parameters;
    class_parameters.write_generated_numbers(set);
    class_parameters.print(set);

    johnsons class_johnson;
    cout << "Johnson 2 MASZYNY" << endl;
    class_parameters.print(class_johnson.johnson2maszyny(set));
    cout << "Cmax: " << class_parameters.evaluate(class_johnson.johnson2maszyny(set)) << endl;

    cout << "Johnson WIĘCEJ MASZYN - kolejność zadań" << endl;
    class_parameters.print(class_johnson.johnson(set));
    cout << "Cmax: " << class_parameters.evaluate(class_johnson.johnson(set)) << endl;

    bruteforce class_brute;
    cout << "Brutalna siła - kolejność zadań" << endl;
    class_brute.init_brute(set);
    class_parameters.print(class_brute.bestpi);
    cout << "Cmax: " << class_brute.ub << endl;

}