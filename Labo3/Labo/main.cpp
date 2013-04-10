#include "include/linearsystemsolver.h"
#include "include/squarematrix.h"
#include "include/genericmatrix.h"

#include <iostream>
#include <string>
#include <clocale>

using namespace std;

int main()
{
    setlocale(LC_ALL, "frs");
    /* /!\ La matrice doit être régulière (inversible) ! Sinon le système ne peut être résolu /!\ */
	SquareMatrix<3,double> matrix(0.0);
	GenericMatrix<3,1,double> constants(0.0);
    GenericMatrix<3,1,string> variables(" ");

	matrix(0,0) = -8.009;
	matrix(0,1) = -1.00001;
	matrix(0,2) = 2.2222;
	constants(0,0) = 8.56746;

	matrix(1,0) = 1.009;
	matrix(1,1) = -1.00901;
	matrix(1,2) = 2.2222;
	constants(1,0) = 8.56746;

	matrix(2,0) = 0;
	matrix(2,1) = 2;
	matrix(2,2) = -1;
	constants(2,0) = -3;

    variables(0,0) = "x";
    variables(1,0) = "y";
    variables(2,0) = "z";

    LinearSystemSolver<3,double> solver(matrix,constants,variables);
    cout << solver << endl;
	return 0;
}
