#include <iostream>

/*------------------------------------------------------------------*\
|*			    Constructors & Destructor				   *|
\*------------------------------------------------------------------*/
template<unsigned int N, typename T>
LinearSystemSolver<N,T>::LinearSystemSolver(const SquareMatrix<N,T>& coefficients,const GenericMatrix<N,1,T>& constants,const GenericMatrix<N,1,std::string>& variables)
:coefficients(coefficients),constants(constants),variables(variables),coefficientsAndConstants(concatenateMatrix(coefficients,constants))
{
    for(unsigned int i = 0;i < N; ++i)
        solutions[i] = new Solution<T>(variables(i,0));

    triangularisation();
    findSolution();
}

template<unsigned int N, typename T>
LinearSystemSolver<N,T>::~LinearSystemSolver()
{
    for(int i = 0;i < N; ++i)
        delete solutions[i];
}

/*------------------------------------------------------------------*\
|*					Functions					                    *|
\*------------------------------------------------------------------*/

/*------------------------------------------------------------------*\
|*					Friends			          	                    *|
\*------------------------------------------------------------------*/

template<unsigned int N, typename T>
std::ostream& operator<<(std::ostream& os, const LinearSystemSolver<N, T>& lss)
{
    os << "Coefficients : " << std::endl;
    os << lss.coefficients << std::endl;
    os << "Variables : " << std::endl;
    os << lss.variables << std::endl;
    os << "Constantes : " << std::endl;
    os << lss.constants << std::endl;
    os << "Coefficients + Constants : " << std::endl;
    os << lss.coefficientsAndConstants << std::endl;
    os << "Solutions : " << std::endl;
    for(unsigned int i = 0;i < N; ++i)
        os << lss.solutions[i]->getKey() << " = " << lss.solutions[i]->getData() << std::endl;
    return os;
}

/*------------------------------------------------------------------*\
|*					Normal			          	            *|
\*------------------------------------------------------------------*/

/*
Aussi appelé scaled pivoting (cf wiki)

    Le but du pivotage partiel est d'avoir comme premier pivot, le nombre le plus grand.
    Le premier pivot se situer à A11 donc on va intervetir les lignes afin d'obtenir
    la valeur la plus grande tout en haut. Le pivot partiel a une complexité de n2 et le
    pivot complet une de n3.

    L'utilisation du pivot devient nécessaire, lorsque l'on désire obtenir une stabilité numérique.
    Pour cela, on peut choisir un le pivot complet et le partiel. L'avantage du partiel c'est que celui-ci
    a une complexité de O(n2) tandis que le complet O(n3). Le pivot partiel est généralement suffisant pour obtenir
    cette stabilité mais dans certains systèmes d'équations, il vaudrait mieux utiliser le pivot complet.
    Il est intéressant d'utiliser le pivot partiel pour obtenir une stabilité numérique

    Une variation du pivot partiel est le scaled partial pivoting où la méthode consiste à prendre la valeur la plus grande
    de la colonne.
*/

//Méthode du pivot partiel
template<unsigned int N, typename T>
void LinearSystemSolver<N,T>::triangularisation()
{
    int imax = 0;
    for(unsigned int i = 0;i < N-1; ++i)//Lignes -> N, -1 car pas besoin d'aller dernière ligne (pivot implicite)
    {
        //On cherche le pivot
        T max = coefficientsAndConstants(i,i);
        for(unsigned int j = i+1; j < N; ++j)//Lignes -> N
            if(max < coefficientsAndConstants(j,i))
            {
                max = coefficientsAndConstants(i,i);
                imax = j;
            }

        //On intervertit les lignes
        for(unsigned int j = 0; j < N + 1; ++j)//Colonnes -> N+1
            std::swap(coefficientsAndConstants(i,j),coefficientsAndConstants(imax,j));

        T factor;
        //On effectue les divisions & soustractions
        for(unsigned int j = i+1;j < N; ++j)//Lignes -> N
        {
            factor = coefficientsAndConstants(j,i) / coefficientsAndConstants(i,i);
            for(unsigned int k = i; k < N + 1; ++k)//Colonnes -> N+1
                coefficientsAndConstants(j,k) -= factor * coefficientsAndConstants(i,k);
         }
    }
}

template<unsigned int N, typename T>
void LinearSystemSolver<N,T>::findSolution()
{
    T temp;
    for(int i= N-1;i >= 0; --i)
    {
        temp = 0;
        for(unsigned int j = i;j <= N-1; ++j)
            temp += coefficientsAndConstants(i,j)*solutions[j]->getData();

        solutions[i]->setData((coefficientsAndConstants(i,N)-temp)/coefficientsAndConstants(i,i));
    }
}
