#ifndef PERMUTATIONMATRIX_H
#define PERMUTATIONMATRIX_H

template<unsigned int N, typename T> class SquareMatrix;

template<unsigned int N, typename T>
class PermutationMatrix : public SquareMatrix<N,T>
{
    public:
        PermutationMatrix(int nbPermutation = 0);
        virtual ~PermutationMatrix();

        T getDeterminant();

        void setNbPermutation(int n);
        int getNbPermutation() const;
    private:
        int nbPermutation;
};

#include "squarematrix.h"
#include "permutationmatrix.tpp"

#endif // PERMUTATIONMATRIX_H
