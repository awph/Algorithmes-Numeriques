#include <cassert>
#include <iomanip>

/*------------------------------------------------------------------*\
|*			    Constructors & Destructor				   *|
\*------------------------------------------------------------------*/

template<unsigned int M, unsigned int N, typename T>
GenericMatrix<M, N, T>::GenericMatrix(const T& defaultValue)
{
	fill(defaultValue);
}

template<unsigned int M, unsigned int N, typename T>
GenericMatrix<M, N, T>::GenericMatrix(const T tab[M][N])
{
	init(tab);
}

template<unsigned int M, unsigned int N, typename T>
GenericMatrix<M, N, T>::GenericMatrix(const GenericMatrix<M, N, T>& m)
{
	for(unsigned int row = 0;row < M;++row)
		for(unsigned int col = 0;col < N;++col)
			m_values[row][col] = m.m_values[row][col];
}

template<unsigned int M, unsigned int N, typename T>
GenericMatrix<M, N, T>::~GenericMatrix()
{

}

/*------------------------------------------------------------------*\
|*					Functions					*|
\*------------------------------------------------------------------*/

template<unsigned int M, unsigned int N, typename T>
void GenericMatrix<M, N, T>::init(const T tab[M][N])
{
	for(unsigned int row = 0;row < M;++row)
		for(unsigned int col = 0;col < N;++col)
			m_values[row][col] = tab[row][col];
}

template<unsigned int M, unsigned int N, typename T>
void GenericMatrix<M, N, T>::fill(const T& value)
{
	for(unsigned int row = 0;row < M;++row)
		for(unsigned int col = 0;col < N;++col)
			m_values[row][col] = value;
}

template<unsigned int M, unsigned int N, typename T>
GenericMatrix<N, M, T> GenericMatrix<M, N, T>::transpose() const
{
	GenericMatrix<N, M, T> result(1);
    for (unsigned int row = 0; row < N; ++row)
        for (unsigned int col = 0; col < M; ++col)
            result(row,col) = (*this)(col,row);
    return result;
}

/*------------------------------------------------------------------*\
|*					Operators			          	            *|
\*------------------------------------------------------------------*/

/*------------------------------------------------------------------*\
|*					Friends			          	            *|
\*------------------------------------------------------------------*/

template<unsigned int M, unsigned int N, typename T>
std::ostream& operator<<(std::ostream& os, const GenericMatrix<M, N, T>& m)
{
	for(unsigned int row = 0;row < M;++row)
	{
	    os << ((row == 0) ? "/" : ((row == M-1) ? "\\" : "|"));
		for(unsigned int col = 0;col < N;++col)
        {
            os << m(row,col) << std::setfill(' ');
			if (col != N -1)
                os << std::setw(6);
        }

        os << ((row == 0) ? "\\" : ((row == M-1) ? "/" : "|"));
		os << std::endl;
	}
	os << std::setfill(' ') << std::setw(0);
	return os;
}

template<unsigned int M, unsigned int N, typename T>
GenericMatrix<M, N, T> operator+(const GenericMatrix<M, N, T>& m1, const GenericMatrix<M, N, T>& m2)
{
	GenericMatrix<M, N, T> result(1);
	for(unsigned int row = 0;row < M;++row)
		for(unsigned int col = 0;col < N;++col)
			result.m_values[row][col] = m1.m_values[row][col] + m2.m_values[row][col];
	return result;
}

template<unsigned int M, unsigned int N, typename T>
GenericMatrix<M, N, T> operator-(const GenericMatrix<M, N, T>& m1, const GenericMatrix<M, N, T>& m2)
{
	GenericMatrix<M, N, T> result(1);
	for(unsigned int row = 0;row < M;++row)
		for(unsigned int col = 0;col < N;++col)
			result.m_values[row][col] = m1.m_values[row][col] - m2.m_values[row][col];
	return result;
}

template<unsigned int M, unsigned int N, unsigned int M2, typename T>
GenericMatrix<M, M2, T> operator*(const GenericMatrix<M, N, T>& m1, const GenericMatrix<N, M2, T>& m2)
{
	GenericMatrix<M, M2, T> result(1);

	for(unsigned int row = 0;row < M;++row)
		for(unsigned int col = 0;col < M2;++col)
		{
			T sum(0);
			for(unsigned int i = 0;i < N;++i)
				sum += m1.m_values[row][i] * m2.m_values[i][col];
			result.m_values[row][col] = sum;
		}
	return result;
}

template<unsigned int M, unsigned int N, typename T>
GenericMatrix<M, N, T> operator-(const GenericMatrix<M, N, T>& m)
{
	GenericMatrix<M, N, T> result(1);
	for(unsigned int row = 0;row < M;++row)
		for(unsigned int col = 0;col < N;++col)
			result.m_values[row][col] = -m.m_values[row][col];
	return result;
}

template<unsigned int M, unsigned int N, typename T>
GenericMatrix<M, N, T> operator*(const T& t, const GenericMatrix<M, N, T>& m)
{
	GenericMatrix<M, N, T> result(1);
	for(unsigned int row = 0;row < M;++row)
		for(unsigned int col = 0;col < N;++col)
			result.m_values[row][col] = t * m.m_values[row][col];
	return result;
}

template<unsigned int M, unsigned int N, typename T>
GenericMatrix<M, N, T> operator*(const GenericMatrix<M, N, T>& m, const T& t)
{
	GenericMatrix<M, N, T> result(1);
	for(unsigned int row = 0;row < M;++row)
		for(unsigned int col = 0;col < N;++col)
			result.m_values[row][col] = m.m_values[row][col] * t;
	return result;
}

template<unsigned int M, unsigned int N, typename T>
GenericMatrix<M, N, T> operator/(const GenericMatrix<M, N, T>& m, const T& t)
{
	GenericMatrix<M, N, T> result(1);
	for(unsigned int row = 0;row < M;++row)
		for(unsigned int col = 0;col < N;++col)
			result.m_values[row][col] = m.m_values[row][col] / t;
	return result;
}

/*------------------------------------------------------------------*\
|*					Normal			          	            *|
\*------------------------------------------------------------------*/

template<unsigned int M, unsigned int N, typename T>
GenericMatrix<M, N, T>& GenericMatrix<M, N, T>::operator+=(const GenericMatrix<M, N, T>& m)
{
	*this = *this + m;
	return *this;
}

template<unsigned int M, unsigned int N, typename T>
GenericMatrix<M, N, T>& GenericMatrix<M, N, T>::operator-=(const GenericMatrix<M, N, T>& m)
{
	*this = *this - m;
	return *this;
}

template<unsigned int M, unsigned int N, typename T>
GenericMatrix<M, N, T>& GenericMatrix<M, N, T>::operator*=(const T& t)
{
	*this = t * *this;
	return *this;
}

template<unsigned int M, unsigned int N, typename T>
GenericMatrix<M, N, T>& GenericMatrix<M, N, T>::operator/=(const T& t)
{
	*this = *this / t;
	return *this;
}

template<unsigned int M, unsigned int N, typename T>
bool GenericMatrix<M, N, T>::operator==(const GenericMatrix<M, N, T>& m) const
{
	if(this == &m)
		return true;
	else
	{
		for(unsigned int row = 0;row < M;++row)
			for(unsigned int col = 0;col < N;++col)
				if(m_values[row][col] != m.m_values[row][col])
					return false;
		return true;
	}
}

template<unsigned int M, unsigned int N, typename T>
bool GenericMatrix<M, N, T>::operator!=(const GenericMatrix<M, N, T>& m) const
{
	return !((*this)==m);
}

template<unsigned int M, unsigned int N, typename T>
const T& GenericMatrix<M, N, T>::operator()(const unsigned int row, const unsigned int col) const
{
	assert(row < M && col < N);
	return m_values[row][col];
}

template<unsigned int M, unsigned int N, typename T>
T& GenericMatrix<M, N, T>::operator()(const unsigned int row, const unsigned int col)
{
	assert(row < M && col < N);
	return m_values[row][col];
}
