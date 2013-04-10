#include <iostream>
#include <cmath>
#include <limits>

/*------------------------------------------------------------------*\
|*			    Constructors & Destructor				   *|
\*------------------------------------------------------------------*/
template<unsigned int N, typename T>
LinearSystemSolver<N,T>::LinearSystemSolver(const SquareMatrix<N,T>& coefficients,const GenericMatrix<N,1,T>& constants,const GenericMatrix<N,1,std::string>& variables)
:coefficients(coefficients),constants(constants),variables(variables),
coefficientsAndConstants(concatenateMatrix(coefficients,constants)),isResolvable(true)
{
    for(unsigned int i = 0;i < N; ++i)
        solutions[i] = new Solution<T>(variables(i,0));

    partialPivoting();
    forwardElimination();
    backSubstitution();
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
    os << "Matrice triangualis�e avec les constantes : " << std::endl;
    os << lss.coefficientsAndConstants << std::endl;
    os << "Solutions : " << std::endl;

    if(lss.isResolvable)
        for(unsigned int i = 0;i < N; ++i)
            os << lss.solutions[i]->getKey() << " = " << lss.solutions[i]->getData() << std::endl;
    else
        os << "Pas de solution, car il s'agit d'un syst�me lin�airement d�pendant !" << std::endl;

    return os;
}

/*------------------------------------------------------------------*\
|*					Normal			          	            *|
\*------------------------------------------------------------------*/

//M�thode du pivot partiel
template<unsigned int N, typename T>
void LinearSystemSolver<N,T>::partialPivoting()
{
    int imax = 0;
    for(unsigned int i = 0;i < N-1; ++i)//Lignes -> N, -1 car pas besoin d'aller derni�re ligne (pivot implicite)
    {
        //On cherche le pivot
        imax = i;
        for(unsigned int j = i+1; j < N; ++j)//Lignes -> N
            if(fabs(static_cast<double>(coefficientsAndConstants(imax,i))) < static_cast<double>(coefficientsAndConstants(j,i)))
                imax = j;

        //On intervertit les lignes
        for(unsigned int j = 0; j < N + 1; ++j)//Colonnes -> N+1
            std::swap(coefficientsAndConstants(i,j),coefficientsAndConstants(imax,j));
    }
}

template<unsigned int N, typename T>
void LinearSystemSolver<N,T>::forwardElimination()
{
    T factor;
    for(unsigned int i = 0;i < N-1; ++i)//Lignes -> N, -1 car pas besoin d'aller derni�re ligne (pivot implicite)
        //On effectue les divisions & soustractions
        for(unsigned int j = i+1;j < N; ++j)//Lignes -> N
        {
            factor = coefficientsAndConstants(j,i) / coefficientsAndConstants(i,i);
            for(unsigned int k = i; k < N + 1; ++k)//Colonnes -> N+1
                coefficientsAndConstants(j,k) -= factor * coefficientsAndConstants(i,k);
         }
}

template<unsigned int N, typename T>
void LinearSystemSolver<N,T>::backSubstitution()
{
    double det = coefficientsAndConstants(0,0);
    for(unsigned int i = 1;i < N; ++i)
        det *= coefficientsAndConstants(i,i);

    isResolvable = (fabs(det-0) > std::numeric_limits<double>::epsilon());//!=0

    if(isResolvable)
        for(int i= N-1;i >= 0; --i)
        {
            T temp = 0;
            for(unsigned int j = i;j < N; ++j)
                temp += coefficientsAndConstants(i,j)*solutions[j]->getData();

            solutions[i]->setData((coefficientsAndConstants(i,N)-temp)/coefficientsAndConstants(i,i));
        }
}
