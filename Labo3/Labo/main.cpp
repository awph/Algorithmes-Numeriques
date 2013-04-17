#include "include/linearsystemsolver.h"
#include "include/squarematrix.h"
#include "include/genericmatrix.h"

#include <iostream>
#include <sstream>
#include <string>
#include <clocale>

using namespace std;

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

void waitHumanAction()
{
    cin.ignore();
    cin.get();
}

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
    const unsigned int NB_EQUATIONS = 3;
    setlocale(LC_ALL, "frs");
    printHeader();

    cout << endl << "Pour modifier le nombre d'équations, il faut modifier la constante dans le main,";
    cout << "car il est impossible d'instancier une classe template avec une constante qui n'a pas été instanciée durant la compilation !" << endl << endl;

    //Utilisation de pointeur devient nécessaire pour les grands systèmes (+300) car
    //la taille de la heap > stack
    int choix = 1;
    do
    {
        SquareMatrix<
                    NB_EQUATIONS,
                    double
                    >* coefficients = new SquareMatrix<NB_EQUATIONS,double>(0.0);

        GenericMatrix<
                    NB_EQUATIONS,
                    1,
                    double>* constants = new GenericMatrix<NB_EQUATIONS,1,double>(0.0);

        GenericMatrix<
                    NB_EQUATIONS,
                    1,
                    string>* variables = new GenericMatrix<NB_EQUATIONS,1,string>(" ");

        cout << "Entrez les noms des variables : " << endl;
        string variable;
        for(unsigned int i = 0;i < NB_EQUATIONS; ++i)
        {
            cout << "Variable " << (i+1) << " : ";
            cin >> variable;
            (*variables)(i,0) = variable;
        }

        for(unsigned int i = 0;i < NB_EQUATIONS; ++i)
        {
            clear();
            cout << "Entrez les coefficients et la constante de l'équation n° " << (i+1) << " : " << endl;

            double valeur;
            for(unsigned int j = 0;j < NB_EQUATIONS; ++j)
            {
                cout << "Coefficient de " << (*variables)(j,0) << " : ";
                (*coefficients)(i,j) = readDouble();
            }
            cout << "Constante : ";
            (*constants)(i,0) = readDouble();
        }

        clear();
        LinearSystemSolver<
                        NB_EQUATIONS,
                        double>* solver = new LinearSystemSolver<NB_EQUATIONS,double>(*coefficients,*constants,*variables);

        cout << *solver;
        waitHumanAction();
        cout << "Voulez-vous résoudre un autre système linéaire ? " << endl <<"1) Oui" << endl << "2) Non" << endl << endl << "Choix : ";
        cin >> choix;
        if(choix == 1)
            clear();

        delete coefficients;
        delete variables;
        delete constants;
        delete solver;
    }
    while(choix == 1);

	return 0;
}
