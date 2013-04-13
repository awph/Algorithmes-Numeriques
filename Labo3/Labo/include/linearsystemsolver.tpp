#include <iostream>

/*------------------------------------------------------------------*\
|*			            Constructors & Destructor				    *|
\*------------------------------------------------------------------*/

template<unsigned int N, typename T>
LinearSystemSolver<N,T>::LinearSystemSolver(const SquareMatrix<N,T>& coefficients,const GenericMatrix<N,1,T>& constants,const GenericMatrix<N,1,std::string>& variables)
:coefficients(coefficients),constants(constants),variables(variables),
coefficientsAndConstants(concatenateMatrix(coefficients,constants)),isResolvable(true)
{
    for(unsigned int i = 0;i < N; ++i)
        solutions[i] = new Solution<T>(variables(i,0));

    solve();
}

template<unsigned int N, typename T>
LinearSystemSolver<N,T>::~LinearSystemSolver()
{
    for(unsigned int i = 0;i < N; ++i)
        delete solutions[i];
}

/*------------------------------------------------------------------*\
|*					        Functions			                    *|
\*------------------------------------------------------------------*/

/*------------------------------------------------------------------*\
|*					        Friends		       	                    *|
\*------------------------------------------------------------------*/

template<unsigned int N, typename T>
std::ostream& operator<<(std::ostream& os, LinearSystemSolver<N, T>& lss)
{
    os << "Coefficients : " << std::endl;
    os << lss.coefficients << std::endl;
    os << "Déterminant : " << lss.coefficients.getDeterminant() << std::endl;
    os << "Variables : " << std::endl;
    os << lss.variables << std::endl;
    os << "Constantes : " << std::endl;
    os << lss.constants << std::endl;
    os << "Matrice triangualisée avec les constantes : " << std::endl;
    os << lss.coefficientsAndConstants << std::endl;
    os << "Solutions : " << std::endl;

    if(lss.isResolvable)
        for(unsigned int i = 0;i < N; ++i)
            os << lss.solutions[i]->getKey() << " = " << lss.solutions[i]->getData() << std::endl;
    else
        os << "Pas de solution, car il s'agit d'un système linéairement dépendant !" << std::endl;

    return os;
}

/*------------------------------------------------------------------*\
|*					        Normal			          	            *|
\*------------------------------------------------------------------*/

template<unsigned int N, typename T>
void LinearSystemSolver<N,T>::solve()
{
    coefficientsAndConstants.partialPivoting();
    SquareMatrix<N,T> coef(coefficients);
    PermutationMatrix<N,T> p = coef.partialPivotingWithGettingPermutationMatrix();

    //On met dans le bon ordre les variables
    int finalIndexe = 0;
    for(unsigned int i = 0;i < N; ++i)
    {
        finalIndexe = -1;
        for(unsigned int j = 0;j < N && finalIndexe == -1; ++j)
            if(p(j,i) == 1)//On recherche par colonne et pas par ligne
                finalIndexe = j;

        if(finalIndexe != -1)
            std::swap(solutions[i],solutions[finalIndexe]);
    }

    coefficientsAndConstants.forwardElimination();
    backSubstitution();
}

template<unsigned int N, typename T>
void LinearSystemSolver<N,T>::backSubstitution()
{
    double det = 1;
    for(unsigned int i = 0;i < N; ++i)
        det *= coefficientsAndConstants(i,i);

    // != 0 -> linéairement indépendant
    isResolvable = (fabs(det-0) > std::numeric_limits<double>::epsilon());

    if(isResolvable)
        for(int i= N-1;i >= 0; --i)
        {
            T temp = 0;
            for(unsigned int j = i;j < N; ++j)
                temp += coefficientsAndConstants(i,j)*solutions[j]->getData();

            solutions[i]->setData((coefficientsAndConstants(i,N)-temp)/coefficientsAndConstants(i,i));
        }
}
