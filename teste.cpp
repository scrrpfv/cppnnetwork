#include <iostream>
#include <random>
#include <iterator>
#include <numeric>

using namespace std;

typedef struct Matrix {
    int nrows;
    int ncols;
    float **v;
} Matrix;

Matrix initMatrix(int nrows, int ncols)
{
    Matrix newmatrix;
    
    newmatrix.v = (float**)malloc(nrows * sizeof(float*));
    for(int i=0; i<nrows; i++)
    {
        newmatrix.v[i] = (float*)malloc(ncols * sizeof(float));
    }

    newmatrix.nrows = nrows;
    newmatrix.ncols = ncols;
    
    return newmatrix;
}

typedef struct MatrixSet {
    Matrix **set;
    int *sizes;
    int size;
} MatrixSet;

MatrixSet initMatrixSet(int *sizes, int size)
{
    MatrixSet newmatrixset;
    newmatrixset.set = (Matrix**)malloc(size * sizeof(Matrix*));

    for(int i=0; i<size; i++)
    {
        Matrix newmatrix = initMatrix(sizes[i], sizes[i+1]);
        newmatrixset.set[i] = &newmatrix;
    }

    newmatrixset.sizes = sizes;
    newmatrixset.size = size;

    return newmatrixset;
}

int main()
{
    Matrix matrix = initMatrix(2, 3);
    matrix.v[1][2] = 5.5;
    cout << matrix.v[1][2];

    MatrixSet set;
    int size = 2;
    int sizes[3] = {2, 3, 2};
    set = initMatrixSet(sizes, size);
    Matrix pmatrix = *set.set[0];
    pmatrix.v[0][0] = 1.5;
    cout << (*set.set[0]).v[0][0];
}