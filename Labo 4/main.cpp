#include <iostream>
#include <clocale>
#include <sstream>
#include <cmath>

#include "GeomGlut.h"
#include "functions.h"

extern GeomGlut graphWin;

using namespace std;

double readDouble()
{
    double output = 0;
    bool isOk = false;
    do
    {
        string input = "";
        output = 0;
        cin >> input;

        stringstream stream(input);
        if(stream >> output)
            isOk = true;
    }while(!isOk);

    return output;
}

int main()
{
	setlocale(LC_ALL, "frs");
    double x_min = 0;
    double x_max = 0;
    double y_min = 0;
    double y_max = 0;

    printHeader();
    cout << "Please enter the absolute biggest value of the square that'll contain the graphic : ";
    x_max = y_max = abs(readDouble());
    x_min = y_min = -x_max;

    int choice = 0;
    do
    {
        clear();
        printHeader();
        cout << "Choose a function : " << endl;
        cout << "1) x^5 + 5x^3 + 2x" << endl;
        cout << "2) x/(1-x^2)" << endl;
        cout << "Choice : ";
        cin >> choice;
    }while(choice < 1 ||choice > 2);

    long double (*f)(long double);//Function pointer

    if(choice == 1)
        f = &f1;
    else if(choice == 2)
        f = &f2;

    cout << endl << endl;

    graphWin.initGraphicsWin( 1000, x_min, x_max, y_min, y_max, f);

    return( 0 );
}
