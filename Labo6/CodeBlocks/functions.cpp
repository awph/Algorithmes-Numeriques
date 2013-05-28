#include "functions.h"
#include "GeomGlut.h"
#include <iostream>
#include <cmath>
#include <string>
#include <cstdio>

extern GeomGlut graphWin;
extern long double (*f1)(long double);
extern long double (*f2)(long double);
extern bool flagIsFinishDrawingPoint;

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
    static float xPoint = 0;
    glPointSize(2.0f);
    for(float x = 0; x < graphWin.xMax(); x += STEP)
    {
        graphWin.plot(x, f1(x), 0.0f, 1.0f, 0.0f);
        graphWin.plot(x, f2(x), 0.0f, 1.0f, 1.0f);
    }

    if(!flagIsFinishDrawingPoint)
    {
        glPointSize(10.0f);
        float val1 = f1(xPoint);
        float val2 = f2(xPoint);
        graphWin.plot(xPoint, val1, 1.0f, 0.0f, 0.0f);
        graphWin.plot(xPoint, val2, 1.0f, 0.0f, 0.0f);

        char buf1[30];
        char buf2[30];

        char unit1[10];
        char unit2[10];

        if(f1==&y)
            strcpy(unit1,"m");
        else if(f1==&v)
            strcpy(unit1,"m/s");
        else
            strcpy(unit1,"m/s2");

        if(f2==&yf)
            strcpy(unit2,"m");
        else if(f2==&vf)
            strcpy(unit2,"m/s");
        else
            strcpy(unit2,"m/s2");

        sprintf(buf1, "%.2f %s", val1, unit1);
        sprintf(buf2, "%.2f %s", val2, unit2);
        graphWin.print(xPoint, val1, buf1, 0.0f, 1.0f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24);
        graphWin.print(xPoint, val2, buf2, 0.0f, 1.0f, 1.0f, GLUT_BITMAP_TIMES_ROMAN_24);
        xPoint += graphWin.xMax()/50.0;
    }
    flagIsFinishDrawingPoint = (xPoint >= graphWin.xMax());

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
        graphWin.print(0,4950,"5000 m");
        graphWin.print(31.9,0,"31.933 s");
        graphWin.print(72.3,0,"72.2895 s");
        legendF1 = "y(t)";
        legendF2 = "yf(t)";
    }
    else if(f1==&v && f2==&vf)
    {
        graphWin.print(78,-20,"t[s]");
        graphWin.print(0,-780,"v[m/s]");
        graphWin.print(73,-95,"-77.6732 m/s");
        graphWin.print(73,-790,"-784.532 m/s");
        legendF1 = "v(t)";
        legendF2 = "vf(t)";
    }
    else if(f1==&a && f2==&af)
    {
        graphWin.print(78,0,"t[s]");
        graphWin.print(0,-9.5,"a[m/s2]");
        graphWin.print(-2,-10,"9.80665 m/s2");
        legendF1 = "a(t)";
        legendF2 = "af(t)";
    }
    else if(f1==&af && f2==&vf)
    {
        graphWin.print(78,0,"t[s]");
        graphWin.print(0,-75,"a[m/s2]",0.0f,1.0f,0.0f);
        graphWin.print(0,-78,"v[m/s]",0.0f,1.0f,1.0f);
        graphWin.print(-5,-10,"9.80665 m/s2");
        graphWin.print(72,-80,"-77.6732  m/s");
        legendF1 = "af(t)";
        legendF2 = "vf(t)";
    }

    std::cout << "Graphical Information : " << std::endl
              << "- Green function represents " << legendF1;
     std::cout << std::endl << "- Light blue function represents " + legendF2;
     std::cout << std::endl << std::endl;
}
