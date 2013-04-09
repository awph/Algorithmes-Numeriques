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

    partialPivoting();
    transformToTriangular();
    findSolution();
}

template<unsigned int N, typename T>
LinearSystemSolver<N,T>::~LinearSystemSolver()
{
    for(int i = 0;i < N; ++i)
        delete solutions[i];
}

/*------------------------------------------------------------------*\
|*					Functions					*|
\*------------------------------------------------------------------*/

/*------------------------------------------------------------------*\
|*					Friends			          	            *|
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

template<unsigned int N, typename T>
void LinearSystemSolver<N,T>::partialPivoting()
{
    for(int i = N-1;i > 0; --i)
        if(coefficientsAndConstants(i-1,0) < coefficientsAndConstants(i,0))
            for(unsigned int j = 0;j <= N; ++j)
            {
                std::swap(coefficientsAndConstants(i,j),coefficientsAndConstants(i-1,j));
                std::swap(solutions[i],solutions[i-1]);
            }
}

template<unsigned int N, typename T>
void LinearSystemSolver<N,T>::transformToTriangular()
{
    T temp;
    for(unsigned int i = 0;i < N-1; ++i)
        for(unsigned int j = i; j < N-1; ++j)
        {
            temp = coefficientsAndConstants(j+1,i)/coefficientsAndConstants(i,i) ;

            for(unsigned int k = 0;k <= N; ++k)
                coefficientsAndConstants(j+1,k) -= temp*coefficientsAndConstants(i,k);
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
