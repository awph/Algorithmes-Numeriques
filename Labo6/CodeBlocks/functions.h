#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <limits>

void clear();
void printHeader();

struct RungeKuttaData
{
	long double(*f)(long double);
	long double t1;
	long double v1;
	long double ft;
	long double n;

	RungeKuttaData(long double(*_f)(long double), long double _t1, long double _v1, long double _ft, long double _n):f(_f),t1(_t1),v1(_v1),ft(_ft),n(_n){}
};

const long double k_g = 9.80665d;
const long double k_k = 10.1d;
const long double k_m = 80.0d;
const long double k_v0 = 0.0d;
const long double k_y0 = 5000.0d;

long double rungeKutta(const RungeKuttaData& datas);
long double simpsons(long double(*rk)(const RungeKuttaData& datas), const RungeKuttaData& datas);

//XXX with Coefficient of Friction
long double aCF(long double v);

//XXX Without Coefficient of Friction
long double aWCF(long double v = 0.0);

//With & Without Coefficient of Friction
long double v(const RungeKuttaData& data);
long double y(const RungeKuttaData& data);

void drawFunctions();

#endif // FUNCTIONS_H
