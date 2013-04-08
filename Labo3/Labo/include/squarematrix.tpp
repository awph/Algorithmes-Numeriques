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

/*------------------------------------------------------------------*\
|*					Functions					*|
\*------------------------------------------------------------------*/

template<unsigned int N, typename T>
const T SquareMatrix<N,T>::determinant() const
{
	return this->m_values[0][0];//Oui sous CB faut foutre ce this-> sinon ça marche pas (et dire qu'après on crache sur VS...)
}
