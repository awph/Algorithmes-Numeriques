/*------------------------------------------------------------------*\
|*			          Constructors & Destructor				        *|
\*------------------------------------------------------------------*/

template<unsigned int N, typename T>
PermutationMatrix<N,T>::PermutationMatrix(int nbPermutation):SquareMatrix<N,T>(),nbPermutation(nbPermutation)
{
    for(unsigned int i = 0;i < N; ++i)
        this->m_values[i][i] = 1;
}

template<unsigned int N, typename T>
PermutationMatrix<N,T>::~PermutationMatrix()
{

}

/*------------------------------------------------------------------*\
|*					        Functions					            *|
\*------------------------------------------------------------------*/

template<unsigned int N, typename T>
T PermutationMatrix<N,T>::getDeterminant()
{
    return (nbPermutation %2 == 0) ? 1.0 : -1.0;
}

template<unsigned int N, typename T>
void PermutationMatrix<N,T>::setNbPermutation(int n)
{
    nbPermutation = n;
}

template<unsigned int N, typename T>
int PermutationMatrix<N,T>::getNbPermutation() const
{
    return nbPermutation;
}
