#ifndef LINEARSYSTEMSOLVER_H
#define LINEARSYSTEMSOLVER_H

#include "squarematrix.h"
#include "genericmatrix.h"
#include "solution.h"

#include <string>
#include <vector>

template<unsigned int N, typename T>
GenericMatrix<N,N+1,T> concatenateMatrix(const SquareMatrix<N,T>& m,const GenericMatrix<N,1,T>& m2)
{
    GenericMatrix<N,N+1,T> out;

    for(unsigned int i = 0; i < N; ++i)
    {
        for(unsigned int j = 0;j < N; ++j)
            out(i,j) = m(i,j);
        out(i,N) = m2(i,0);
    }

    return out;
}

template<unsigned int N, typename T>
class LinearSystemSolver
{
    public:
        explicit LinearSystemSolver(const SquareMatrix<N,T>& coefficients,
                                    const GenericMatrix<N,1,T>& constants,
                                    const GenericMatrix<N,1,std::string>& variables);
        ~LinearSystemSolver();

        template<unsigned int NN, typename TT>
        friend std::ostream& operator<<(std::ostream& os, const LinearSystemSolver<NN, TT>& lss);

    private:
        void scaledPartialPivoting();
        void transformToTriangular();
        void findSolution();

        SquareMatrix<N,T> coefficients;
        GenericMatrix<N,1,T> constants;
        GenericMatrix<N,1,std::string> variables;
        GenericMatrix<N,N+1,T> coefficientsAndConstants;

        Solution<T>* solutions[N];
};

#include "linearsystemsolver.tpp"

#endif // LINEARSYSTEMSOLVER_H
