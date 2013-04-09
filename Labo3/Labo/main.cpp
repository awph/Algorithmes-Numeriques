#include "include/linearsystemsolver.h"
#include "include/squarematrix.h"
#include "include/genericmatrix.h"

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    /* /!\ La matrice doit être régulière (inversible) ! Sinon le système ne peut être résolu /!\ */
	SquareMatrix<3,double> matrix(0.0);
	GenericMatrix<3,1,double> constants(0.0);
    GenericMatrix<3,1,string> variables(" ");

	matrix(0,0) = 1;
	matrix(0,1) = 2;
	matrix(0,2) = 3;
	constants(0,0) = 4;

	matrix(1,0) = 8;
	matrix(1,1) = 7;
	matrix(1,2) = 6;
	constants(1,0) = 5;

	matrix(2,0) = 1;
	matrix(2,1) = 9;
	matrix(2,2) = 2;
	constants(2,0) = 7;

    variables(0,0) = "x";
    variables(1,0) = "y";
    variables(2,0) = "z";

    LinearSystemSolver<3,double> solver(matrix,constants,variables);
    cout << solver << endl;
	return 0;
}
