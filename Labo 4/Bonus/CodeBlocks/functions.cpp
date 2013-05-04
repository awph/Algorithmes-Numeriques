#include "functions.h"
#include "GeomGlut.h"

#include <iostream>
#include <cmath>

extern GeomGlut graphWin;
extern long double radius;
extern long double speedStraight;
extern long double speedAlong;

void clear()
{
	cout << string(50, '\n' );
}

void printHeader()
{
    cout << "|===========================================|" << endl
         << "|Program realized by :                      |" << endl
         << "|                        - Diego Antognini  |" << endl
         << "|                        - Alexandre Perez  |" << endl
         << "|                        - Sebastien Vaucher|" << endl
         << "|===========================================|" << endl;
}

long double distanceStraight(long double phi)
{
    return fabsl(radius)*sqrtl(2.0d+2.0d*cos(2.0d*phi));
}

long double distanceAlong(long double phi)
{
    return phi*radius;
}

long double f(long double phi)
{
    return distanceStraight(phi)/speedStraight + 2.0d*distanceAlong(phi)/speedAlong;
}

long double derivateFirstOrder(long double x, long double (*f)(long double), long double h)
{
    return (f(x+h)-f(x-h))/(2.0d*h);
}

long double derivateSecondOrder(long double x, long double (*f)(long double), long double h)
{
    return (f(x+h)+f(x-h)-2*f(x))/(h*h);
}

void drawFunctions()
{
    const float STEP = 1e-5;
    const float xMin = 0.0f;
    const float xMax = M_PI/2.0f;
    glPointSize(2.0f);

    //Draw f(x)
    for(float x=xMin; x<xMax; x+=STEP)
        graphWin.plot(x, f(x), 1.0f,0.5f,0.0f);

    //Draw f'(x)
    for(float x=xMin; x<xMax; x+=STEP)
        graphWin.plot( x, derivateFirstOrder(x,f) , 0.5f,0.5f,0.5f);

    //Draw f''(x)
    for(float x=xMin; x<xMax; x+=STEP)
        graphWin.plot(x, derivateSecondOrder(x,f), 1.0f,0.5f,1.0f);

    clear();
    printHeader();
    std::cout << "x is in the subset [" << graphWin.xMin() << ";" << graphWin.xMax() << "[" << std::endl;
    std::cout << "y is in the subset [" << graphWin.yMin() << ";" << graphWin.yMax() << "[" << std::endl << std::endl;
    std::cout << "Graphical Informations : " << std::endl
              << "- Function choosen (f(x)) in orange" << std::endl
              << "- First derivative in gray" << std::endl
              << "- Second derivative in rose" << std::endl
              << "- The axes x,y are in bleu " << std::endl
              << "- The unitary vectors are in red " << std::endl << std::endl;
}
