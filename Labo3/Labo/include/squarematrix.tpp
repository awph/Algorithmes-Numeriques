/*------------------------------------------------------------------*\
|*			    Constructors & Destructor				   *|
\*------------------------------------------------------------------*/

template<unsigned int N, typename T>
SquareMatrix<N, T>::SquareMatrix(const T& defaultValue):GenericMatrix<N,N,T>(defaultValue),det(1),isDeterminantComputed(false)
{

}

template<unsigned int N, typename T>
SquareMatrix<N, T>::SquareMatrix(const T tab[N][N]):GenericMatrix<N,N,T>(tab),det(1),isDeterminantComputed(false)
{
	init(tab);
}

template<unsigned int N, typename T>
SquareMatrix<N, T>::SquareMatrix(const SquareMatrix<N, T>& m):GenericMatrix<N,N,T>(m),det(1),isDeterminantComputed(false)
{

}

template<unsigned int N, typename T>
SquareMatrix<N,T>::~SquareMatrix()
{

}

/*------------------------------------------------------------------*\
|*					        Functions					            *|
\*------------------------------------------------------------------*/

template<unsigned int N, typename T>
void SquareMatrix<N,T>::setIdentity()
{
    for(unsigned int i = 0;i < N; ++i)
        this->m_values[i][i] = 1;
}

template<unsigned int N, typename T>
T SquareMatrix<N,T>::getDeterminant()
{
    if(!isDeterminantComputed)
        computeDeterminant();

    return det;
}

template<unsigned int N, typename T>
void SquareMatrix<N,T>::computeDeterminant()
{
    //L'utilisation de pointeur devient nécessaire si l'on veut gérer
    //des matrices de plus de 300x300
    isDeterminantComputed = true;
    SquareMatrix<N,T>* u = new SquareMatrix<N,T>(*this);
    PermutationMatrix<N,T>* p = new PermutationMatrix<N,T>(u->partialPivotingWithGettingPermutationMatrix());
    u->forwardElimination();

    /*/!\ Cette boucle sert à définir la matrice l. Dans notre cas, on en a pas besoin, donc on l'enlève.
    //Elle a juste servi à vérifier l'algorithme, mais on la laisse si un jour une méthode de décomposition LU
    //est à implémenter ! /!\*/

    //On complète les cases en dessous de la diagonale de l
    //SquareMatrix<N,T> pa = p*(*this);
    /*
    SquareMatrix<N,T> l;
    l.setIdentity();
    T sum = 0;
    for(unsigned int i = 1;i < N; ++i)
        for(unsigned int j = 0;j < i; ++j)
        {
            sum = 0;
            for(unsigned int k = 0; k < j; ++k)
                sum += u(k,j)*l(i,k);
            l(i,j) = 1/u(j,j) * (pa(i,j)-sum);
        }*/

    for(unsigned int i = 0;i < N; ++i)
        det *= (*u)(i,i);
    det *= p->getDeterminant();

    delete u;
    delete p;
}

template<unsigned int N, typename T>
PermutationMatrix<N,T> SquareMatrix<N,T>::partialPivotingWithGettingPermutationMatrix()
{
    PermutationMatrix<N,T> permutation;

    int nbPermutation = 0;
    int imax = 0;
    for(unsigned int i = 0;i < N-1; ++i)//Lignes -> M - 1, car pas besoin d'aller dernière ligne (pivot implicite)
    {
        //On cherche le pivot
        imax = i;
        for(unsigned int j = i+1;j < N; ++j)
            if(fabs(static_cast<double>(this->m_values[imax][i])) < static_cast<double>(this->m_values[j][i]))
                imax = j;

        //On intervertit les lignes
        for(unsigned int j = 0;j < N; ++j)
            std::swap(this->m_values[i][j],this->m_values[imax][j]);

        if(imax != i)
        {
            ++nbPermutation;
            for(unsigned int j = 0;j < N; ++j)
                std::swap(permutation(i,j),permutation(imax,j));
        }
    }
    permutation.setNbPermutation(nbPermutation);

    return permutation;
}

/*------------------------------------------------------------------*\
|*					        Operators		          	            *|
\*------------------------------------------------------------------*/

/*------------------------------------------------------------------*\
|*					        Friends			          	            *|
\*------------------------------------------------------------------*/

template<unsigned int N, typename T>
SquareMatrix<N,T> operator*(const SquareMatrix<N,T>& m1, const SquareMatrix<N,T>& m2)
{
	SquareMatrix<N, T> result(1);

	for(unsigned int row = 0;row < N; ++row)
		for(unsigned int col = 0;col < N; ++col)
		{
			T sum(0);
			for(unsigned int i = 0;i < N;++i)
				sum += m1.m_values[row][i] * m2.m_values[i][col];
			result.m_values[row][col] = sum;
		}

	return result;
}

