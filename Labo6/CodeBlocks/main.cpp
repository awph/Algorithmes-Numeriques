#include <clocale>
#include <iostream>
#include "GeomGlut.h"
#include "functions.h"

extern GeomGlut graphWin;

using namespace std;

int main()
{
	setlocale(LC_ALL, "frs");


    int choice = 0;
    do
    {
        clear();
        printHeader();
        cout << "Please choose wich graphic do you want to see :" << endl;
        cout << "1) Comparaison for y[t]" << endl;
        cout << "2) Comparaison for y'[t]" << endl;
        cout << "3) Comparaison for y''[t]" << endl;
        cout << "4) Comparaison for y'[t] & y''[t] with coefficient of friction" << endl;
        cout << "Choice : ";
        cin >> choice;
    }while(choice < 1 || choice > 4);


    double xmin = -5;
    double xmax = 80;
    double ymin = -5;
    double ymax = 5;

    GeomGlut::Action action;

    if(choice == 1)
    {
        action = GeomGlut::Y;
        ymax = 5050;
    }
    else if(choice == 2)
    {
        action = GeomGlut::V;
        ymin = -800;
    }
    else if(choice == 3)
    {
        action = GeomGlut::A;
        ymin = -10;
    }
    else
    {
        action = GeomGlut::AV;
        ymin = -80;
    }

    graphWin.initGraphicsWin(1400, 800, xmin, xmax, ymin, ymax, action);

    return(0);
}
