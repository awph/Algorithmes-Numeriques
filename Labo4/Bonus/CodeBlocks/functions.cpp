#include "functions.h"
#include "GeomGlut.h"

#include <iostream>
#include <cmath>
#include <climits>

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
         << "|Program implemented by :                   |" << endl
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

long double findRoot()
{
    long double a = graphWin.xMin(), b = graphWin.xMax(), fa = derivateFirstOrder(a,&f), fm = 0.0;
    long double mnew = a + b;
    long double mold = 2*mnew;
    long double epsilon = std::numeric_limits<long double>::epsilon();

    while(fabsl(mnew-mold) >= epsilon)
    {
        mold = mnew;
        mnew = (a+b)/2.0;
        fm = derivateFirstOrder(mnew,&f);
        if(fm*fa <= epsilon)
            b = mnew;
        else
        {
            a = mnew;
            fa = fm;
        }
    }
    return mnew;
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

    graphWin.print(0,1.0,"t [s]",1.0f);
    graphWin.print(1.0,0,"phi [rad]",1.0f);

    //Plot legends
    float x = graphWin.xMax()/2;
    float yPadding = graphWin.yMax()/30.0f;
    graphWin.print(x,f(x)+yPadding,"f(x)", 1.0f,0.5f,0.0f);
    graphWin.print(x,derivateFirstOrder(x,f)+yPadding,"f'(x)", 0.5f,0.5f,0.5f);
    graphWin.print(x,derivateSecondOrder(x,f)+yPadding,"f''(x)", 1.0f,0.5f,1.0f);

    clear();
    printHeader();
    std::cout << "x is in range [" << graphWin.xMin() << ";" << graphWin.xMax() << "[" << std::endl;
    std::cout << "y is in range [" << graphWin.yMin() << ";" << graphWin.yMax() << "[" << std::endl << std::endl;
    std::cout << "Graphical Information : " << std::endl
              << "- Chosen function (f(x)) in orange" << std::endl
              << "- First derivative in gray" << std::endl
              << "- Second derivative in pink" << std::endl
              << "- The axis x,y are in blue, respectively in [rad] and [s]" << std::endl
              << "- The unit vectors are in red " << std::endl << std::endl;

    long double phi = findRoot();
    long double rootInDSecond = derivateSecondOrder(phi,&f);

    //If it's a max, we take the minimum in the edges
    if(rootInDSecond < std::numeric_limits<long double>::epsilon())
    {
        if(f(graphWin.xMin()) < f(graphWin.xMax()))
            phi = graphWin.xMin();
        else
            phi = graphWin.xMax();
    }

    std::cout << "Radius : " << graphWin.getRadius() << " meters" << std::endl;
    std::cout << "Speed on the lake : " << graphWin.getSpeedStraight() << " meters per second" << std::endl;
    std::cout << "Speed along the lake : " << graphWin.getSpeedAlong() << " meters per second" << std::endl << std::endl;
    std::cout << "SOLUTION : " << std::endl;
    std::cout << "You should go along the lake with an angle of " << phi*180.0/M_PI << "°" << std::endl;
    std::cout << "You'll take " << f(phi) << " seconds" << std::endl;
    std::cout << "You'll travel " << 2.0*distanceAlong(phi) + distanceStraight(phi) << " meters" << std::endl;
}
