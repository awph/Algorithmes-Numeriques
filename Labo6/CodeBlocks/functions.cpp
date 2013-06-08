#include "functions.h"
#include "GeomGlut.h"
#include <iostream>
#include <string>

extern GeomGlut graphWin;
extern GeomGlut::Action action;

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

long double rungeKutta(const RungeKuttaData& datas)
{
	long double(*f)(long double) = datas.f;
	long double v = datas.v1;
	long double ft = datas.ft;
	long double n = datas.n;
	long double h = (ft-datas.t1)/n;

	while(n-->0)
	{
		long double s1 = f(v);
		long double s2 = f(v+s1*h/2.0);
		long double s3 = f(v+s2*h/2.0);
		long double s4 = f(v+s3*h);

		v +=(s1+2*s2+2*s3+s4)*h/6.0;
	}

	return v;
}

long double simpsons(long double(*rk)(const RungeKuttaData& datas), const RungeKuttaData& datas)
{
	int n = datas.n;
	long double a = datas.t1;
	long double b = datas.ft;

	RungeKuttaData simpsonData = datas;

    // If n is odd, we transform it to even
    if(n%2 == 1)
        ++n;

	simpsonData.n = n;

    long double h = (b-a)/static_cast<long double>(n);
    long double sum = 0.0d;

    // If j is even, we multiply the result of f(a+j*h) by 2, otherwise by 4
    for(int j = 1; j < n; ++j)
	{
		simpsonData.ft = a+j*h;
        sum += rk(simpsonData) * ((j%2 == 0) ? 2.0d : 4.0d);
	}

    // We add f(0) (=f(a)) and f(n) (=f(b)), because j € [1;n[
    simpsonData.ft = a;
	sum += rk(simpsonData);

	simpsonData.ft = b;
    sum += rk(simpsonData);

    return h/3.0*sum;
}

//XXX with Coefficient of Friction
long double aCF(long double v)
{
    return -k_g-k_k/k_m*v;
}

//XXX Without Coefficient of Friction
long double aWCF(long double v)
{
    return -k_g;
}

long double v(const RungeKuttaData& data)
{
    return rungeKutta(data);
}

long double y(const RungeKuttaData& data)
{
    return k_y0+simpsons(&rungeKutta, data);
}

void drawFunctions()
{
    const long double STEP = 0.4;
    glPointSize(4.0f);

    long double t0 = 0.0;
    long double ft = 80.0;
    long double n = 300.0;
    long double v0 = k_v0;
    RungeKuttaData dataCF(&aCF,t0,v0,ft,n);//With CF
    RungeKuttaData dataWCF(dataCF);//WithoutCF
    dataWCF.f = &aWCF;

    for(long double x = 0; x < graphWin.xMax(); x += STEP)
    {
        long double y1 = 0.0;
        long double y2 = 0.0;

        dataCF.ft = dataWCF.ft = x;

        if(action == GeomGlut::Y)
        {
            y1 = k_y0+simpsons(&rungeKutta, dataCF);
            y2 = k_y0+simpsons(&rungeKutta, dataWCF);
        }
        else if(action == GeomGlut::V)
        {
            y1 = k_v0+rungeKutta(dataCF);
            y2 = k_v0+rungeKutta(dataWCF);
        }
        else if(action == GeomGlut::A)
        {
            y1 = aCF(k_v0+rungeKutta(dataCF));
            y2 = aWCF(k_v0+rungeKutta(dataWCF));
        }
        else if(action == GeomGlut::AV)
        {
            y1 = k_v0+rungeKutta(dataCF);
            y2 = aCF(y1);
        }

        graphWin.plot(x, y1, 1.0f, 0.0f, 0.0f);
        graphWin.plot(x, y2, 0.0f, 1.0f, 1.0f);
    }

    clear();
    printHeader();
    std::cout << "x is in range [" << graphWin.xMin() << ";" << graphWin.xMax() << "[" << std::endl;
    std::cout << "y is in range [" << graphWin.yMin() << ";" << graphWin.yMax() << "[" << std::endl << std::endl;

    std::string legendF1 = "";
    std::string legendF2 = "";

    if(action == GeomGlut::Y)
    {
        graphWin.print(78,20,"t[s]");
        graphWin.print(0,4850,"y[m]");
        graphWin.print(0,4950,"5000 m");
        graphWin.print(31.9,0,"31.933 s");
        graphWin.print(72.3,0,"72.2895 s");
        legendF1 = "y(t)";
        legendF2 = "y(t) with CF";
    }
    else if(action == GeomGlut::V)
    {
        graphWin.print(78,-20,"t[s]");
        graphWin.print(0,-780,"v[m/s]");
        graphWin.print(73,-95,"-77.6732 m/s");
        graphWin.print(73,-790,"-784.532 m/s");
        legendF1 = "v(t)";
        legendF2 = "v(t) with CF";
    }
    else if(action == GeomGlut::A)
    {
        graphWin.print(78,0,"t[s]");
        graphWin.print(0,-9.5,"a[m/s2]");
        graphWin.print(-2,-10,"9.80665 m/s2");
        legendF1 = "a(t)";
        legendF2 = "a(t) with CF";
    }
    else if(action == GeomGlut::AV)
    {
        graphWin.print(78,0,"t[s]");
        graphWin.print(0,-75,"a[m/s2]",0.0f,1.0f,0.0f);
        graphWin.print(0,-78,"v[m/s]",0.0f,1.0f,1.0f);
        graphWin.print(-5,-10,"9.80665 m/s2");
        graphWin.print(72,-80,"-77.6732  m/s");
        legendF1 = "a(t) with CF";
        legendF2 = "v(t) with CF";
    }

    std::cout << "Graphical Information : " << std::endl
              << "- Green function represents " << legendF1;
     std::cout << std::endl << "- Light blue function represents " + legendF2;
     std::cout << std::endl << std::endl;
}
