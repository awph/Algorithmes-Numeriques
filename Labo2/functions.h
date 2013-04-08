#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>

void clear();
void printHeader();

long double f1(long double x);
long double f2(long double x);
long double g(long double x, long double lambda = 1);

std::vector<long double> findRoot();
void drawFunctions();

#endif // FUNCTIONS_H
