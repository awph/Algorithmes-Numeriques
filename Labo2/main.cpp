#include <iostream>
#include <clocale>
#include "GeomGlut.h"
#include "functions.h"

extern GeomGlut graphWin;

using namespace std;

int main()
{
	setlocale(LC_ALL, "frs");
    double x_min = 0;
    double x_max = 0;
    double y_min = 0;
    double y_max = 0;

    printHeader();
    cout << "Entrez la valeur la plus grande en x : ";
    cin >> x_max;
    cout << "Entrez la valeur la plus petite en x : ";
    cin >> x_min;
    cout << "Entrez la valeur la plus grande en y : ";
    cin >> y_max;
    cout << "Entrez la valeur la plus petite en y : ";
    cin >> y_min;

    int choix = 0;
    do
    {
        clear();
        printHeader();
        cout << "Choisissez la fonction à résoudre : " << endl;
        cout << "1) Sin(x) -x/3" << endl;
        cout << "2) x/(1-x^2)" << endl;
        cout << "Choix : ";
        cin >> choix;
    }while(choix < 1 ||choix > 2);

    long double (*f)(long double);//Pointeur de fonction

    if(choix == 1)
        f = &f1;
    else if(choix == 2)
        f = &f2;

    cout << endl << endl;


    graphWin.initGraphicsWin( 1000, x_min, x_max, y_min, y_max, f);

    return( 0 );
}
