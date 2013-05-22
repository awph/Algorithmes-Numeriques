#include "functions.h"
#include "GeomGlut.h"
#include <iostream>
#include <iomanip>

extern GeomGlut graphWin;

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

double f(double x)
{
    return 4.0d/(1.0d + x*x);
}

double simpsons(double(*f)(double), double a, double b, int n)
{
    //If n is odd, we transform it to even
    if(n%2 == 1)
        ++n;

    double h = (b-a)/static_cast<double>(n);
    double sum = 0.0d;

    //if j is even, we multiplie the result of f(a+j*h) by 2, else by 4
    for(int j = 1; j < n; ++j)
        sum += f(a+j*h) * ((j%2 == 0) ? 2.0d : 4.0d);

    //We add f(0) (=f(a)) and f(n) (=f(b)), because j € [1;n[
    sum += f(a);
    sum += f(b);

    return h/3.0*sum;
}

void drawIntegral()
{
    const float STEP = 1e-5;

    //Plot f(x)
    for(float x=graphWin.xMin(); x<graphWin.xMax(); x+=STEP)
        //Better display with only points
        graphWin.plot(x, f(x), 1.0f,0.5f,0.0f);

    //draw Integral
    for(float x=0; x<1.0f; x+=STEP)
        graphWin.segment(x, 0, x, f(x), 2.0f, .0f, .0f, .0f);

    //We plot the average value of the function (=pi)

    double pi = simpsons(&f,0.0,1.0,190);//best n to have the most accurate pi approximation with simpson
    graphWin.plotRetangle(0,0,1,0,1,pi,0,pi);
    graphWin.print(0,f(0), "f(x) = 4(1+x^2)", 1.0f, 0.5f, 0.05);


    clear();
    printHeader();
    std::cout << "x is in range [" << graphWin.xMin() << ";" << graphWin.xMax() << "[" << std::endl;
    std::cout << "y is in range [" << graphWin.yMin() << ";" << graphWin.yMax() << "[" << std::endl << std::endl;
    std::cout << "The approximation of Pi (result of the integral) is "<< std::fixed << std::setprecision(16) << pi << endl;

    std::cout << "Graphical Information : " << endl
              << "- The dark area represents the integral of the function f(x)" << endl
              << "- The red rectangle represents the average value : 1/(b-a)*int{0,1}f(x)dx = pi" << endl;
}
