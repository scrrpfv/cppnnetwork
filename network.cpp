#include <iostream>
#include <iomanip>
#include <random>

using namespace std;

typedef struct Matrix {
    float **v;
    int nrows;
    int ncols;
} Matrix;

/* Initialize a matrix with defined size */
Matrix initMatrix(int nrows, int ncols) {
    Matrix newMatrix;
    
    newMatrix.v = (float**)malloc(nrows * sizeof(float*));
    for (int i = 0; i < nrows; i++) {
        newMatrix.v[i] = (float*)malloc(ncols * sizeof(float));
    }
    newMatrix.nrows = nrows;
    newMatrix.ncols = ncols;

    return newMatrix;
}

typedef struct MatrixSet {
    Matrix *set;
    int *sizes;
    int size;
} MatrixSet;

/* Initialzie empty set of matrices with defined sizes */
MatrixSet initMatrixSet(int *sizes, int size) {
    MatrixSet newMatrixSet;
    newMatrixSet.set = (Matrix*)malloc(size * sizeof(Matrix));

    for (int i = 0; i < size; i++) {
        Matrix newMatrix = initMatrix(sizes[i], sizes[i+1]);
        newMatrixSet.set[i] = newMatrix;
    }
    newMatrixSet.sizes = sizes;
    newMatrixSet.size = size;

    return newMatrixSet;
}

typedef struct VectorFloat {
    float *v;
    int size;
} VectorFloat;

VectorFloat initVectorFloat(int size) {
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

VectorFloatSet initVectorFloatSet(int *sizes, int size) {
    VectorFloatSet newVectorFloatSet;
    newVectorFloatSet.set = (VectorFloat*)malloc(size * sizeof(VectorFloat));
    for(int i = 0; i < size + 1; i++) {
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

VectorInt initVectorInt(int size) {
    VectorInt newVectorInt;

    newVectorInt.v = (int*)malloc(size * sizeof(int));
    newVectorInt.size = size;

    return newVectorInt;
}

typedef struct ActiFuncs {
    float (**f)(float, float);
} ActiFuncs;

typedef struct Network {
    MatrixSet weights; /* Set of matrices defining the network's weights */
    VectorFloatSet biases; /* Set of vectors defining the network's biases */
    VectorFloatSet nodes;
    ActiFuncs acti_funcs;
    int *sizes;
    int n_layers;
} Network;

VectorFloatSet GenerateBiases(int *sizes, int n_layers) {
    return initVectorFloatSet(sizes, n_layers);
}

VectorFloatSet GenerateNodes(int *sizes, int n_layers) {
    return initVectorFloatSet(sizes, n_layers);
}

/* Function to initialize network's layers with random values */
void GenerateLayer(Matrix layer, int n, int m) {
    /* Creating the rng with normal distribution around 0 */
    random_device rd;
    mt19937_64 gen(rd());
    normal_distribution<float> dis(0, 1);
    auto rand = [&](){ return dis(gen); }; /* Different function call for each value to ensure no repeats */

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            layer.v[i][j] = rand(); /* Attributes random values to the layers */
        }
    }
}

/* Function to initialize the weights of a network using the GenerateLayer function iteratively */
void GenerateWeights(MatrixSet weights, int* sizes, int n_layers) {
    for(int i = 0; i<n_layers; i++) {
        GenerateLayer(weights.set[i], sizes[i], sizes[i + 1]);
    }
}

float ReLu(float x, float bias) {
    return (abs(x) + x)/2;
}

float Linear(float x, float bias) {
    return x + bias;
}

ActiFuncs GenerateActiFuncs(int *acti_funcs, int size) {
    ActiFuncs functions;
    for (int i = 0; i < size; i++) {
        switch (acti_funcs[i]) {
        case 0:
            functions.f[i] = Linear;
            break;
        case 1:
            functions.f[i] = ReLu;
            break;
        default:
            functions.f[i] = Linear;
            break;
        }
    }
    return functions;
}

Network InitNetwork(int *acti_funcs, int *sizes, int size) {
    Network network;

    MatrixSet weights = initMatrixSet(sizes, size);
    GenerateWeights(weights, sizes, size);
    network.weights = weights;

    network.biases = GenerateBiases(sizes, size);
    network.nodes = GenerateNodes(sizes, size);
    
    network.acti_funcs = GenerateActiFuncs(acti_funcs, size);
    network.sizes = sizes;
    network.n_layers = size;
    
    return network;
}

VectorFloat VectorByMatrix(VectorFloat vector, Matrix matrix, VectorFloat result) {
    for (int i = 0; i < matrix.ncols; i++) {
        float c = 0;
        for (int j = 0; j < vector.size; j++) {
            c += vector.v[j] * matrix.v[j][i];
        }
        result.v[i] = c;
    }
    return result;
}

/* Function to define the feed forward loop for the neural network based on the entry data */
void FeedForward(Network network, float *entry_data) {
    VectorFloat *nodes = network.nodes.set;
    for (int i = 0; i < network.sizes[0]; i++) {
        nodes[0].v[i] = entry_data[i]; /* Set entry nodes to input values */
    }
    for (int i = 0; i < network.n_layers; i++)
    {
        /* Pega os valores dos nodos anteriores, multiplica pelos pesos e coloca nos próximos nodos */
        VectorByMatrix(nodes[i], network.weights.set[i], nodes[i + 1]);

        for (int j = 0; j < nodes[i].size; j++) {
            nodes[i].v[j] = network.acti_funcs.f[i](nodes[i].v[j], network.biases.set[i].v[j]);
        }
    }
}

int main() {
    cout << setprecision(4);
    int acti_funcs[2] = {0, 1};
    int sizes[3] = {3, 5, 3};
    int size = 2;
    float entry[3] = {1, 2, 3};

    Network network = InitNetwork(acti_funcs, sizes, size);
    for (int n = 0; n < network.n_layers; n++) {
        Matrix matrix = network.weights.set[n];

        for (int i = 0; i < matrix.nrows; i++) {
            for (int j = 0; j < matrix.ncols; j++) {
                cout << matrix.v[i][j] << " | ";
            }
            cout << endl;
        }
    }

    FeedForward(network, entry);

    cout << "Output: " << endl;
    for (int i = 0; i < network.sizes[network.n_layers]; i++) {
        cout << network.nodes.set[network.n_layers].v[i] << " ";
    }
    cout << endl;
}
