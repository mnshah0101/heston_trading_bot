#ifndef BLACKSCHOLES_HPP
#define BLACKSCHOLES_HPP

#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

double N(double z);

class BlackScholes
{
public:
    BlackScholes(double callFlagInput, double SInput, double XInput, double rInput, double volInput, double TInput);
    BlackScholes();
    ~BlackScholes();

    double d1();
    double d2();
    double Price();
    void printTest();
    void ErrorChecker();
    
    double callFlag;

private:
    double S;
    double X;
    double r;
    double vol;
    double T;
};

#endif // BLACKSCHOLES_HPP
