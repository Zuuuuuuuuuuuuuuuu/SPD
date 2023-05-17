#include <iostream>
#include <chrono>
#include "parameters.hh"
#include "RandomNumberGenerator.hh"

using namespace std::chrono;

int main()
{
    vector<parameters> set (NUM_ELEMENTS);
    vector<parameters> PI;
    parameters j;
    parameters class_parameters;
    class_parameters.write_generated_numbers(set);
    class_parameters.print(set);
}