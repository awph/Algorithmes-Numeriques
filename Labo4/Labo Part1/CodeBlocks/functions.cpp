#include "functions.h"
#include "GeomGlut.h"

#include <iostream>
#include <cmath>

extern GeomGlut graphWin;
extern long double (*f)(long double);

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

long double f1(long double x)
{
    return pow(x,5)+5*pow(x,3)+2*x;
}

long double f2(long double x)
{
    return x/(1-x*x);
}

long double f2_denominator(long double x)
{
    return 1-x*x;
}
//Long double necessary to keep a coherent result with the machine epsilon !
//Otherwise, we lose huge precision. For example if we use x=2 with f1 and double, we get 71 instead of 142 !
long double derivateFirstOrder(long double x, long double (*f)(long double), long double h)
{
    return (f(x+h)-f(x-h))/(2.0d*h);
}

//Unfortunately, if we use the epsilon machine, we cannot have an acceptable result,
//so we have to use h with the value 1e-6. The smaller h, the more inaccurate is the result
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
        //Better display with only points
        graphWin.plot(x, f(x), 1.0f,0.5f,0.0f);
        graphWin.plot(x, derivateFirstOrder(x,f) , 0.5f,0.5f,0.5f);
        graphWin.plot(x, derivateSecondOrder(x,f), 1.0f,0.5f,1.0f);
    }

    /*
    Of course we could use the method findRoot of the laboratory 2 but the little problem is that
    we depend on the denominator of the given function so we have to know which function is used.
    So we have to adapt the method findRoot to the function denominator.
    The easiest solution is to know the asymptotes and draw them directly, rather that compute them.
    In both cases, if we change the function, the amount of work is the same, so let's take the
    easiest and fastest solution !*/
    if(f == &f2)
    {
        graphWin.segment(1.0d, graphWin.yMin(), 1.0d, graphWin.yMax(), 2.0f, 1.0f,0.5f,1.0f);
        graphWin.segment(-1.0d, graphWin.yMin(), -1.0d, graphWin.yMax(), 2.0f, 1.0f,0.5f,1.0f);
    }

    clear();
    printHeader();
    std::cout << "x is in range [" << graphWin.xMin() << ";" << graphWin.xMax() << "[" << std::endl;
    std::cout << "y is in range [" << graphWin.yMin() << ";" << graphWin.yMax() << "[" << std::endl << std::endl;
    std::cout << "Graphical Information : " << std::endl
              << "- Chosen function (f(x)) in orange" << std::endl
              << "- First derivative in gray" << std::endl
              << "- Second derivative in pink" << std::endl
              << "- The axis x,y are in blue " << std::endl
              << "- The unit vectors are in red " << std::endl << std::endl;
}
