#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H

#include "genericmatrix.h"

template<unsigned int N, typename T>
class SquareMatrix : public GenericMatrix<N,N,T>
{
public:
		//Constructors & Destructor
        explicit SquareMatrix(const T& defaultValue=0);
        explicit SquareMatrix(const T tab[N][N]);
		SquareMatrix(const SquareMatrix& m);
		virtual ~SquareMatrix();

		const T determinant() const;
};

#include "squarematrix.tpp"

#endif // SQUAREMATRIX_H
