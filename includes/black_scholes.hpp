#ifndef BLACK_SCHOLES_H
#define BLACK_SCHOLES_H

#include <stdio.h>
#include <math.h>

void black_scholes_pricer(double S, double K, double T, double r, double vol, double *C, double *P);

double covered_call(double S, double K, double T, double r, double vol, double *profit_if_exercised, double *profit_if_not_exercised);

#endif // BLACK_SCHOLES_H
