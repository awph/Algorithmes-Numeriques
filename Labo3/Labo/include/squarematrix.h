#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H

#include "genericmatrix.h"
#include "permutationmatrix.h"

template<unsigned int N, typename T>
class SquareMatrix : public GenericMatrix<N,N,T>
{
public:
        explicit SquareMatrix(const T& defaultValue=0);
        explicit SquareMatrix(const T tab[N][N]);
		SquareMatrix(const SquareMatrix& m);
		virtual ~SquareMatrix();

        void setIdentity();
        virtual T getDeterminant();
        PermutationMatrix<N,T> partialPivotingWithGettingPermutationMatrix();

        template<unsigned int NN, typename TT>
        friend SquareMatrix<NN,TT> operator*(const SquareMatrix<NN,TT>& m1, const SquareMatrix<NN,TT>& m2);
private:
    void computeDeterminant();

    bool isDeterminantComputed;
    T det;
};

#include "squarematrix.tpp"

#endif // SQUAREMATRIX_H
