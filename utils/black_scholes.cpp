#include <stdio.h>
#include <math.h>

// Function to calculate the cumulative distribution function for the standard normal distribution
double norm_cdf(double x) {
    return 0.5 * (1.0 + erf(x / sqrt(2.0)));
}

// Black-Scholes Pricer, returns call and put price
void black_scholes_pricer(double S, double K, double T, double r, double vol, double *C, double *P) {
    double d1 = (log(S / K) + (r + 0.5 * vol * vol) * T) / (vol * sqrt(T));
    double d2 = d1 - vol * sqrt(T);
    *C = S * norm_cdf(d1) - K * exp(-r * T) * norm_cdf(d2);
    *P = K * exp(-r * T) * norm_cdf(-d2) - S * norm_cdf(-d1);
}

// Covered Call Strategy
void covered_call(double S, double K, double T, double r, double vol, double *profit_if_exercised, double *profit_if_not_exercised) {
    double call_price, put_price;
    black_scholes_pricer(S, K, T, r, vol, &call_price, &put_price);
    *profit_if_exercised = K - S + call_price;
    *profit_if_not_exercised = call_price;
}

// Protective Put Strategy
void protective_put(double S, double K, double T, double r, double vol, double *total_cost, double *minimum_value) {
    double call_price, put_price;
    black_scholes_pricer(S, K, T, r, vol, &call_price, &put_price);
    *total_cost = S + put_price;
    *minimum_value = K;
}