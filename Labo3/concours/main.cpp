#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>


const int N = 5;

/*Générer la matrice de NxN, récupérer le contenu du fichier et le mettre dans le main*/
/*#include <fstream>
void generateMatrix()
{
    srand(time(NULL));
    double** matrix = new double*[N];
    for(int i = 0; i < N; ++i)
    {
        matrix[i] = new double[N];
        for(int j = 0; j < N; ++j)
            matrix[i][j] = (double)rand()/0x7FFF;//http://cplusplus.com/reference/cstdlib/rand/?kw=rand
    }

    std::ofstream file;
    file.open("matrix.txt");
    file << "{";
    for(int i = 0;i < N; ++i)
    {
        file << "{";
        for(int j = 0; j < N; ++j)
            file << matrix[i][j] << (j == (N-1) ? "" : ",");
        file << "}" << (i == (N-1) ? "" : ",");
    }
    file << "};";
    file.close();
}*/

double computeDeterminant(double matrix[N][N])
{
    /*int nbPermutation = 0;
    int imax = 0;
    for(int i = 0; i < N-1; ++i)
    {
        imax = i;
        for(int j = i+1;j < N; ++j)
            if(fabs(matrix[imax][i]) < matrix[j][i])
                imax = j;

        for(int j = 0; j < N; ++j)
            std::swap(matrix[i][j],matrix[imax][j]);

        if(imax != i)
        {
            ++nbPermutation;
        }
    }
    double det = (nbPermutation%2 == 0) ? 1 : -1;*/

    double det = 1;

    double factor;
    for(int i = 0;i < N-1; ++i)
        for(int j = i+1;j < N; ++j)
        {
            factor = matrix[j][i] / matrix[i][i];
            for(int k = i; k < N; ++k)
                matrix[j][k] -= factor * matrix[i][k];
        }


    for(int i = 0;i < N; ++i)
        det *= matrix[i][i];
    return det;
}

void display(double** matrix)
{
    for(int i = 0; i < N; ++i)
    {
        for(int j = 0;j < N; ++j)
            std::cout << matrix[i][j] << "   ";
        std::cout << std::endl;
    }
}

int main()
{
    //generateMatrix();
    double matrix[N][N] = {{0.0769677,0.0780358,0.840846,0.547075,0.0669881},{0.223548,0.207862,0.583972,0.895871,0.858028},{0.123142,0.837275,0.773309,0.409253,0.631764},{0.685873,0.520341,0.0415662,0.858394,0.40257},{0.87759,0.356151,0.0314341,0.707114,0.971435}};
    std::cout << "Det : " << computeDeterminant(matrix);
    return 0;
}
