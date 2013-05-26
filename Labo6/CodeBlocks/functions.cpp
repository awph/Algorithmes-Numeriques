#include "functions.h"
#include "GeomGlut.h"
#include <iostream>
#include <cmath>
#include <string>

extern GeomGlut graphWin;
extern long double (*f1)(long double);
extern long double (*f2)(long double);

static const long double k_g = 9.80665d;
static const long double k_k = 10.1d;
static const long double k_m = 80.0d;
static const long double k_v0 = 0.0d;
static const long double k_y0 = 5000.0d;

void clear()
{
	cout << string(50, '\n' );
}

void printHeader()
{
    cout << "|===========================================|" << endl
         << "|Program implemented by :                   |" << endl
         << "|                        - Diego Antognini  |" << endl
         << "|                        - Alexandre Perez  |" << endl
         << "|                        - Sébastien Vaucher|" << endl
         << "|===========================================|" << endl;
}

long double y(long double t)
{
    return -1.0d/2.0d*k_g*pow(t,2) + k_v0*t + k_y0;
}

long double yf(long double t)
{
    return -k_g*pow(k_m,2)/pow(k_k,2)*exp(-k_k/k_m*t) - k_m*k_g/k_k*t + pow(k_m,2)*k_g/pow(k_k,2)+k_y0;
}

long double v(long double t)
{
  return -k_g*t + k_v0;
}

long double vf(long double t)
{
    return k_g*k_m/k_k*exp(-k_k/k_m*t)-k_m*k_g/k_k;
}

long double a(long double t)
{
    return -k_g;
}

long double af(long double t)
{
    return -k_g*exp(-k_k/k_m*t);
}

void drawFunctions()
{
    const float STEP = 1e-4;

    glPointSize(2.0f);
    for(float x = 0; x < graphWin.xMax(); x += STEP)
    {
        graphWin.plot(x, f1(x), 0.0f, 1.0f, 0.0f);
        graphWin.plot(x, f2(x), 0.0f, 1.0f, 1.0f);
    }

    clear();
    printHeader();
    std::cout << "x is in range [" << graphWin.xMin() << ";" << graphWin.xMax() << "[" << std::endl;
    std::cout << "y is in range [" << graphWin.yMin() << ";" << graphWin.yMax() << "[" << std::endl << std::endl;

    std::string legendF1 = "";
    std::string legendF2 = "";


    if(f1==&y && f2==&yf)
    {
        graphWin.print(78,20,"t[s]");
        graphWin.print(0,4850,"y[m]");
        graphWin.print(0,4950,"5000");
        graphWin.print(31.9,0,"31.933");
        graphWin.print(72.3,0,"72.2895");
        legendF1 = "y(t)";
        legendF2 = "yf(t)";
    }
    else if(f1==&v && f2==&vf)
    {
        graphWin.print(78,-20,"t[s]");
        graphWin.print(0,-780,"v[m/s]");
        graphWin.print(75,-77.67,"-77.6732");
        graphWin.print(75,-780.53,"-784.532");
        legendF1 = "v(t)";
        legendF2 = "vf(t)";
    }
    else if(f1==&a && f2==&af)
    {
        graphWin.print(78,0,"t[s]");
        graphWin.print(0,-9.5,"a[m/s^2]");
        graphWin.print(-2,-10,"9.80665");
        legendF1 = "a(t)";
        legendF2 = "af(t)";
    }
    else if(f1==&af && f2==&vf)
    {
        graphWin.print(78,0,"t[s]");
        graphWin.print(0,-75,"a[m/s^2]",0.0f,1.0f,0.0f);
        graphWin.print(0,-78,"v[m/s]",0.0f,1.0f,1.0f);
        graphWin.print(-2,-10,"9.80665");
        graphWin.print(75,-77.67,"-77.6732");
        legendF1 = "af(t)";
        legendF2 = "vf(t)";
    }

    std::cout << "Graphical Information : " << std::endl
              << "- Green function represents " << legendF1;
     std::cout << std::endl << "- Light blue function represents " + legendF2;
     std::cout << std::endl << std::endl;
}
