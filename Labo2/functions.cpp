#include "functions.h"
#include "GeomGlut.h"

#include <math.h>
#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>

extern GeomGlut graphWin;
extern long double (*f)(long double);

void clear()
{
	cout << string(50, '\n' );
}

void printHeader()
{
    cout << "|===========================================|" << endl
         << "|Programme réalisé par :                    |" << endl
         << "|                        - Diego Antognini  |" << endl
         << "|                        - Alexandre Perez  |" << endl
         << "|                        - Sebastien Vaucher|" << endl
         << "|===========================================|" << endl;
}

long double f1(long double x)
{
    return sin(x) - (x / 3);
}

long double f2(long double x)
{
    return x / (1 - x*x);
}

long double g(long double x, long double lambda)
{
    return x + lambda*f(x);
}

std::vector<long double> findRoot()
{
    const long double epsilon = std::numeric_limits<double>::epsilon();
    const long double STEP = 2*epsilon;
     std::vector<long double> solutions;

    //FindRoot

    //Recherche les racines du côté x >= 0
    long double oldStep = 2*epsilon;
    for(long double x=oldStep; x<graphWin.xMax(); x+=fabsl(g(x)-x))
    {
        //Dessin des barres comme dans le cours
        graphWin.segment(x-oldStep,x-oldStep,x-oldStep,g(x-oldStep));
        if(x > g(x))
        {
            if(f == f1)
                graphWin.segment(x-oldStep,g(x-oldStep),x,g(x-oldStep));
            else
                graphWin.segment(x-oldStep,x-oldStep,x,x-oldStep);
        }
        else
            graphWin.segment(x-oldStep,x,x,x);

        if(fabsl(g(x)-x) <= epsilon)
        {
            solutions.push_back(x);
            x+=STEP;//On ajoute suffisement de STEP pour que la fonction puisse repartir et chercher d'autres solutions
        }
        oldStep = fabsl(g(x)-x);
    }

    oldStep = 2*epsilon;
    //Recherche les racines du côté x < 0
    for(long double x=-epsilon; x > graphWin.xMin(); x-=fabsl(g(x)-x))
    {
        //Dessin des barres comme dans le cours
        graphWin.segment(x+oldStep,x+oldStep,x+oldStep,g(x+oldStep));
        if(x < g(x))
        {
            if(f == f1)
                graphWin.segment(x+oldStep,g(x+oldStep),x,g(x+oldStep));
            else
                graphWin.segment(x+oldStep,x+oldStep,x,x+oldStep);
        }
        else
            graphWin.segment(x+oldStep,x,x,x);

        if(fabsl(g(x)-x) <= epsilon)
        {
            solutions.push_back(x);
            x-=STEP;//On ajoute le STEP initiale pour que la fonction puisse repartir et chercher d'autres solutions
        }

        oldStep = fabsl(g(x)-x);
    }

    sort(solutions.begin(),solutions.end());

    return solutions;
}

void drawFunctions()
{
    const float STEP = graphWin.findSmartStepX();
    glPointSize(2.0f);

    //Draw selected  (f(x))
    for(float x=graphWin.xMin(); x<graphWin.xMax(); x+=STEP)
        graphWin.plot(x, f(x), 1.0f,0.5f,0.0f);

    //Draw f(x) = x
    for(float x=graphWin.xMin(); x<graphWin.xMax(); x+=STEP)
        graphWin.plot( x, x, 0.5f,0.5f,0.5f);

    //Draw g(x)
    for(float x=graphWin.xMin()+STEP; x<graphWin.xMax(); x+=STEP)
        graphWin.plot(x, g(x), 1.0f,0.5f,1.0f);

    clear();
    printHeader();
    std::cout << "x est compris dans l'ensemble [" << graphWin.xMin() << ";" << graphWin.xMax() << "[" << std::endl;
    std::cout << "y est compris dans l'ensemble [" << graphWin.yMin() << ";" << graphWin.yMax() << "[" << std::endl << std::endl;
    std::cout << "Information graphique : " << std::endl
              << "- Fonction choisie (f(x)) en orange" << std::endl
              << "- Fonction h(x) = x, en gris" << std::endl
              << "- Fonction g(x) = x + l*f(x), l = 1, en rose" << std::endl
              << "- Les axes x,y en bleu " << std::endl
              << "- Les vecteurs unitaires en rouge " << std::endl
              << "- Les solutions de la fonction en vert" << std::endl << std::endl;

    vector<long double> solutions = findRoot();
    std::cout << "Solutions : " << std::endl;

    glColor3f(0.0f, 1.0f, 0.0f);
    glPointSize(10);

    //Draw solutions
    for(unsigned int i = 0;i < solutions.size(); ++i)
    {
        std::cout << "[" << i << "] -> " << static_cast<double>(solutions[i]) << std::endl;
        glBegin( GL_POINTS );
            glVertex3d(solutions[i], 0, 0.0);
        glEnd();
    }
}
