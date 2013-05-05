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
    return fabsl(graphWin.getRadius())*sqrtl(2.0d+2.0d*cos(2.0d*phi));
}

long double distanceAlong(long double phi)
{
    return phi*graphWin.getRadius();
}

long double f(long double phi)
{
    return distanceStraight(phi)/graphWin.getSpeedStraight() + 2.0d*distanceAlong(phi)/graphWin.getSpeedAlong();
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
    glPointSize(2.0f);

    //Plot f(x),f'(x),f''(x)
    for(float x=graphWin.xMin(); x<graphWin.xMax(); x+=STEP)
    {
        graphWin.plot(x, f(x), 1.0f,0.5f,0.0f);
        graphWin.plot(x, derivateFirstOrder(x,f) , 0.5f,0.5f,0.5f);
        graphWin.plot(x, derivateSecondOrder(x,f), 1.0f,0.5f,1.0f);
    }

    //Plot legends
    float x = graphWin.xMax()/2;
    float yPadding = graphWin.yMax()/30.0f;
    graphWin.print(x,f(x)+yPadding,"f(x)", 1.0f,0.5f,0.0f);
    graphWin.print(x,derivateFirstOrder(x,f)+yPadding,"f'(x)", 0.5f,0.5f,0.5f);
    graphWin.print(x,derivateSecondOrder(x,f)+yPadding,"f''(x)", 1.0f,0.5f,1.0f);

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
