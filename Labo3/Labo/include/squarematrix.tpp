/*------------------------------------------------------------------*\
|*			    Constructors & Destructor				   *|
\*------------------------------------------------------------------*/

template<unsigned int N, typename T>
SquareMatrix<N, T>::SquareMatrix(const T& defaultValue):GenericMatrix<N,N,T>(defaultValue)
{

}

template<unsigned int N, typename T>
SquareMatrix<N, T>::SquareMatrix(const T tab[N][N]):GenericMatrix<N,N,T>(tab)
{
	init(tab);
}

template<unsigned int N, typename T>
SquareMatrix<N, T>::SquareMatrix(const SquareMatrix<N, T>& m):GenericMatrix<N,N,T>(m)
{

}

template<unsigned int N, typename T>
SquareMatrix<N,T>::~SquareMatrix()
{

}
