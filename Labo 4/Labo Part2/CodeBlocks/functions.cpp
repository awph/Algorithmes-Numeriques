#include "functions.h"
#include "GeomGlut.h"

#include <iostream>
#include <cmath>
#include <vector>
#include <string>

extern GeomGlut graphWin;
extern vector<pair<string,long double> > goldValues;

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
/*
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
//Long double necessary to keep a coeherent result with the machin epsilon !
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
*/
void drawFunctions()
{
    glPointSize(2.0f);

    //Draw gold values
    string oldYear="";
    vector<pair<string,long double> >::iterator it = goldValues.begin();
    for(float x=graphWin.xMin(); it != goldValues.end() && x < graphWin.xMax(); ++it, ++x)
    {
        graphWin.plot(x, it->second, 1.0f,0.5f,0.0f);
        string date = it->first;
        string currentYear = date.substr(date.length()-4,4);
        if(currentYear != oldYear)
        {
            graphWin.print(x, graphWin.yMax()-50, currentYear.c_str(), 1.0f, 0.0f, 0.0f);
            for(float y=graphWin.yMin(); y < graphWin.yMax(); ++y)
                graphWin.plot(x, y, 1.0f,0.0f,0.0f);
            oldYear = currentYear;
        }
    }



}
