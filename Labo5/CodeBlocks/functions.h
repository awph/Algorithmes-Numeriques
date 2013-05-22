#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <limits>

void clear();
void printHeader();

double f(double x);
double simpsons(double(*f)(double), double a, double b, int n);
void drawIntegral();

#endif // FUNCTIONS_H
