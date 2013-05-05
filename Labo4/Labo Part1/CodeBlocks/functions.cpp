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
         << "|Program realized by :                      |" << endl
         << "|                        - Diego Antognini  |" << endl
         << "|                        - Alexandre Perez  |" << endl
         << "|                        - Sebastien Vaucher|" << endl
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
//Long double necessary to keep a coherent result with the machin epsilon !
//Otherwise, we lost a big big precision. For example if we use x=2 with f1 and double, we get 71 and not 142 !
long double derivateFirstOrder(long double x, long double (*f)(long double), long double h)
{
    return (f(x+h)-f(x-h))/(2.0d*h);
}

//Unfortunately, if we use the epsilon machine, we cannot have an acceptable result,
//so we have to use h with the value 1e-6. Smaller is h, more imprecise is the result
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
    we depend of the denominator of the given function so we have to know which function is used.
    So we have to adapt the method findRoot to the function denominator.
    The easiest solution is to know the asymptotes and draw them directly, rather to compute them.
    In the both case, if we change the function, the quantity of work is the same, so let's take the
    easiest and fastest solution !*/
    if(f == &f2)
    {
        graphWin.segment(1.0d, graphWin.yMin(), 1.0d, graphWin.yMax(), 2.0f, 1.0f,0.5f,1.0f);
        graphWin.segment(-1.0d, graphWin.yMin(), -1.0d, graphWin.yMax(), 2.0f, 1.0f,0.5f,1.0f);
    }

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
