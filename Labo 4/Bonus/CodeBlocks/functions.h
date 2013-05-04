#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <limits>

void clear();
void printHeader();

long double distanceStraight(long double phi);
long double distanceAlong(long double phi);
long double f(long double phi);

long double derivateFirstOrder(long double x, long double (*f)(long double), long double h = std::numeric_limits<double>::epsilon());
long double derivateSecondOrder(long double x, long double (*f)(long double), long double h = 1e-6);

void drawFunctions();

#endif // FUNCTIONS_H
