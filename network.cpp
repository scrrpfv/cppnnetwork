#include <iostream>
#include <random>

using namespace std;


typedef struct Matrix {
    float **v;
    int nrows;
    int ncols;
} Matrix;


Matrix initMatrix(int nrows, int ncols) /* Initialize a matrix with defined size */
{
    Matrix newMatrix;
    
    newMatrix.v = (float**)malloc(nrows * sizeof(float*));
    for(int i=0; i<nrows; i++)
    {
        newMatrix.v[i] = (float*)malloc(ncols * sizeof(float));
    }

    newMatrix.nrows = nrows;
    newMatrix.ncols = ncols;
    
    return newMatrix;
}


typedef struct MatrixSet {
    Matrix **set;
    int *sizes;
    int size;
} MatrixSet;


MatrixSet initMatrixSet(int *sizes, int size) /* Initialzie empty set of matrices with defined sizes */
{
    MatrixSet newMatrixSet;
    newMatrixSet.set = (Matrix**)malloc(size * sizeof(Matrix*));

    for(int i=0; i<size; i++)
    {
        Matrix newMatrix = initMatrix(sizes[i], sizes[i+1]);
        newMatrixSet.set[i] = &newMatrix;
    }
    newMatrixSet.sizes = sizes;
    newMatrixSet.size = size;

    return newMatrixSet;
}


typedef struct VectorFloat {
    float *v;
    int size;
} VectorFloat;


VectorFloat initVectorFloat(int size)
{
    VectorFloat newVectorFloat;

    newVectorFloat.v = (float*)malloc(size * sizeof(float));
    newVectorFloat.size = size;

    return newVectorFloat;
}


typedef struct VectorFloatSet {
    VectorFloat *set;
    int *sizes;
    int size;
} VectorFloatSet;


VectorFloatSet initVectorFloatSet(int *sizes, int size)
{
    VectorFloatSet newVectorFloatSet;
    newVectorFloatSet.set = (VectorFloat*)malloc(size * sizeof(VectorFloat));
    for(int i=0; i<size; i++)
    {
        VectorFloat newVectorFloat = initVectorFloat(sizes[i]);
        newVectorFloatSet.set[i] = newVectorFloat;
    }
    newVectorFloatSet.sizes = sizes;
    newVectorFloatSet.size = size;

    return newVectorFloatSet;
}


typedef struct VectorInt {
    int *v;
    int size;
} VectorInt;


VectorInt initVectorInt(int size)
{
    VectorInt newVectorInt;

    newVectorInt.v = (int*)malloc(size * sizeof(int));
    newVectorInt.size = size;

    return newVectorInt;
}


typedef struct Network {
    MatrixSet weights; /* Set of matrices defining the network's weights */
    VectorFloatSet biases; /* Set of vectors defining the network's biases */
    VectorFloatSet nodes;
    int *acti_funcs;
    int *sizes;
    int n_layers;
} Network;


VectorFloatSet GenerateBiases(int *sizes, int n_layers)
{
    VectorFloatSet biases = initVectorFloatSet(sizes, n_layers);
    return biases;
}


VectorFloatSet GenerateNodes(int *sizes, int n_layers)
{
    VectorFloatSet nodes = initVectorFloatSet(sizes, n_layers);
    return nodes;
}


/* Function to initialize network's layers with random values */
void GenerateLayer(Matrix layer, int n, int m)
{
    /* Creating the rng with normal distribution around 0 */
    random_device rd;
    mt19937_64 gen(rd());
    normal_distribution<float> dis(0, 1);
    auto rand = [&](){ return dis(gen); }; /* Different function call for each value to ensure no repeats */

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            layer.v[i][j] = rand(); /* Attributes random values to the layers */
        }
    }
}


/* Function to initialize the weights of a network using the GenerateLayer function iteratively */
void GenerateWeights(MatrixSet weights, int* sizes, int n_layers)
{
    for(int i = 0; i<n_layers; i++)
    {
        GenerateLayer(*weights.set[i], sizes[i], sizes[i + 1]);
    }
}


Network InitNetwork(int *acti_funcs, int *sizes, int size)
{ 
    Network network;

    MatrixSet weights = initMatrixSet(sizes, size);
    GenerateWeights(weights, sizes, size);
    network.weights = weights;

    network.biases = GenerateBiases(sizes, size);
    network.nodes = GenerateNodes(sizes, size);

    network.acti_funcs = acti_funcs;
    network.sizes = sizes;
    network.n_layers = size;
    
    return network;
}


void VectorByMatrix(VectorFloat vector, Matrix matrix, VectorFloat result)
{   
    for(int i=0; i<matrix.ncols; i++)
    {
        int c = 0;
        for(int j=0; j<matrix.nrows; j++)
        {
            c += vector.v[j] * matrix.v[i][j];
        }
        result.v[i] = c;
    }
}


/* Function to define the feed forward loop for the neural network based on the entry data */
void FeedForward(Network network, float *entry_data)
{
    for(int i=0; i<network.sizes[0]; i++)
    {
        network.nodes.set[0].v[i] = entry_data[i];
    }
    for(int i=0; i<network.n_layers; i++)
    {
        
    }
}


int main()
{   
    int acti_funcs[2] = {1, 1};
    int sizes[3] = {3, 5, 3};
    int size = 2;

    Network network = InitNetwork(acti_funcs, sizes, size);
    Matrix matrix1 = *network.weights.set[0];
    cout << "matriz 1" << endl;
    for(int i=0; i<matrix1.nrows; i++)
    {
        for(int j=0; j<matrix1.ncols; j++)
        {
        int v = matrix1.v[i][j];
        cout << v << " ";
        }
    }
}
