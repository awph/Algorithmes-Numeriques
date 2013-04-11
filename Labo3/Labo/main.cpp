#include "include/linearsystemsolver.h"
#include "include/squarematrix.h"
#include "include/genericmatrix.h"

#include <iostream>
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
int main()
{
    const unsigned int NB_EQUATIONS = 3;
    setlocale(LC_ALL, "frs");
    printHeader();

    cout << endl << "Pour modifier le nombre d'équations, il faut modifier la constante dans le main,";
    cout << "car il est impossible d'instancier une classe template avec une constante qui n'a pas été instanciée durant la compilation !" << endl << endl;

    int choix = 1;
    do
    {
        /* /!\ La matrice doit être régulière (inversible) ! Sinon le système ne peut être résolu /!\ */
        SquareMatrix<
                    NB_EQUATIONS,
                    double
                    > coefficients(0.0);

        GenericMatrix<
                    NB_EQUATIONS,
                    1,
                    double> constants(0.0);

        GenericMatrix<
                    NB_EQUATIONS,
                    1,
                    string> variables(" ");

        cout << "Entrez les noms des variables : " << endl;
        string variable;
        for(unsigned int i = 0;i < NB_EQUATIONS; ++i)
        {
            cout << "Variable " << (i+1) << " : ";
            cin >> variable;
            variables(i,0) = variable;
        }

        for(unsigned int i = 0;i < NB_EQUATIONS; ++i)
        {
            clear();
            cout << "Entrez les coefficients et la constante de l'équation n° " << (i+1) << " : " << endl;

            double valeur;
            for(unsigned int j = 0;j < NB_EQUATIONS; ++j)
            {
                cout << "Coefficient de " << variables(j,0) << " : ";
                cin >> valeur;
                coefficients(i,j) = valeur;
            }
            cout << "Constante : ";
            cin >> valeur;
            constants(i,0) = valeur;
        }

        clear();
        LinearSystemSolver<
                        NB_EQUATIONS,
                        double> solver(coefficients,constants,variables);
        cout << solver;
        waitHumanAction();

        cout << "Voulez-vous résoudre un autre système linéaire ? " << endl <<"1) Oui" << endl << "2) Non" << endl << endl << "Choix : ";
        cin >> choix;
        if(choix == 1)
            clear();
    }
    while(choix == 1);

	return 0;
}
