#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <limits>

void clear();
void printHeader();

long double f(long double x);
long double simpsons(long double(*f)(long double), long double a, long double b, int n);
void drawIntegral();

#endif // FUNCTIONS_H
