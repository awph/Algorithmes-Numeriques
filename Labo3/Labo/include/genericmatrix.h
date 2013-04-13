#ifndef GenericMatrix_H
#define GenericMatrix_H

#include <ostream>

template<unsigned int M, unsigned int N, typename T>
class GenericMatrix
{
public:
	//Constructors & Destructor
	explicit GenericMatrix(const T& defaultValue=0);
	explicit GenericMatrix(const T tab[M][N]);
	GenericMatrix(const GenericMatrix& m);
	virtual ~GenericMatrix();

	//Functions
	void init(const T tab[M][N]);
	void fill(const T& value);

	GenericMatrix<N, M, T> transpose() const;
    void partialPivoting();

	//Operators

	//Friends
	template<unsigned int MM, unsigned int NN, typename TT>
	friend std::ostream& operator<<(std::ostream& os, const GenericMatrix<MM, NN, TT>& m);

	template<unsigned int MM, unsigned int NN, typename TT>
	friend GenericMatrix<MM, NN, TT> operator+(const GenericMatrix<MM, NN, TT>& m1, const GenericMatrix<MM, NN, TT>& m2);

	template<unsigned int MM, unsigned int NN, typename TT>
	friend GenericMatrix<MM, NN, TT> operator-(const GenericMatrix<MM, NN, TT>& m1, const GenericMatrix<MM, NN, TT>& m2);

	template<unsigned int MM, unsigned int NN, unsigned int M2, typename TT>
	friend GenericMatrix<MM,M2,TT> operator*(const GenericMatrix<MM, NN, TT>& m1, const GenericMatrix<NN,M2,TT>& m2);

	template<unsigned int MM, unsigned int NN, typename TT>
	friend GenericMatrix<MM, NN, TT> operator-(const GenericMatrix<MM, NN, TT>& m);

	template<unsigned int MM, unsigned int NN, typename TT>
	friend GenericMatrix<MM, NN, TT> operator*(const TT& t, const GenericMatrix<MM, NN, TT>& m);

	template<unsigned int MM, unsigned int NN, typename TT>
	friend GenericMatrix<MM, NN, TT> operator*(const GenericMatrix<MM, NN, TT>& m, const TT& t);

	template<unsigned int MM, unsigned int NN, typename TT>
	friend GenericMatrix<MM, NN, TT> operator/(const GenericMatrix<MM, NN, TT>& m, const TT& t);

	//Normal
	GenericMatrix& operator+=(const GenericMatrix& m);
	GenericMatrix& operator-=(const GenericMatrix& m);
	GenericMatrix& operator*=(const T& t);
	GenericMatrix& operator/=(const T& t);

	bool operator==(const GenericMatrix& m) const;
	bool operator!=(const GenericMatrix& m) const;

	const T& operator()(const unsigned int r,const unsigned int c) const;
	T& operator()(const unsigned int r,const unsigned int c);

	//Get
	unsigned int rows() const {return M;}
	unsigned int cols() const {return N;}

protected:
	T m_values[M][N];
};

#include "genericmatrix.tpp"

#endif
