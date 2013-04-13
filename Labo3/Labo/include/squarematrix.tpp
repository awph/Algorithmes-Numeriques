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

template<unsigned int N, typename T>
double SquareMatrix<N,T>::determinant() const
{
    /*SquareMatrix<N,T> l(0);
    SquareMatrix<N,T> u(0);

    for(unsigned int i = 0;i < N; ++i)
        l(i,i) = 1;

    for(unsigned int i = 0;i < N; ++i)
        u(1,i) = this->(1,i);*/


}
