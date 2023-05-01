#include <iostream>
#include <chrono>
#include "parameters.hh"
#include "RandomNumberGenerator.hh"
#include "bruteforce.hh"
#include "dynamic.hh"


using namespace std::chrono;

int main()
{
    vector<parameters> set (NUM_ELEMENTS);
    vector<parameters> PI;
    parameters j;
    parameters class_parameters;
    class_parameters.write_generated_numbers(set);
    class_parameters.print(set);
    cout << class_parameters.evaluate(set) << endl << endl;

    // bruteforce class_brute;
    // cout << "Brutalna siła" << endl;
    // class_brute.init_brute(set);
    // class_parameters.print(class_brute.bestpi);
    // cout << "Delay: " << class_brute.ub << endl;

    // cout << "Mateoda zachłanna" << endl;
    // class_parameters.print(class_parameters.sort(set));
    // cout << class_parameters.evaluate(class_parameters.sort(set)) << endl << endl;

    dynamic class_dynamic;
    class_dynamic.dynamic_programming_init(set);
    cout << class_dynamic.minimum << endl;
}