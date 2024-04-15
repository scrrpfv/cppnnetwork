#include <iostream>
#include <random>
#include <iterator>
#include <numeric>

using namespace std;

/*
TO DO:
Trocar todas as funções por void eu acho?
*/

struct NETWORK
{
    float **weights; /* Set of matrices defining the network's weights */
    float **biases; /* Set of arrays defining the network's biases */
    int *acti_funcs;
    int *sizes;
    int n_layers;
};

float **GenerateBiases(int *sizes)
{
    int n_layers = sizeof(sizes) / sizeof(sizes[0]) - 1;
    float **biases;
    biases = (float **) malloc (sizeof(float*) * n_layers);
    for(int l=0; l<n_layers; l++)
    {
        int n = sizes[l], m = sizes[l+1];
        float layer[n * m];
        biases[l] = layer;
    }
    return biases;
}

/* Function to initialize network's layers with random values */
float *GenerateLayer(int n, int m)
{
    /* Creating the rng with normal distribution around 0 */
    random_device rd;
    mt19937_64 gen(rd());
    normal_distribution<float> dis(0, 1);
    auto rand = [&](){ return dis(gen); }; /* Different function call for each value to ensure no repeats */
    float layer[n * m]; /* Sadly using a 1d array to avoid triple pointer madness */
    float (*ptr)[m];
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            layer[i * m + j] = rand(); /* Attributes random values to the layers */
        }
    }
    return layer;
}

/* Function to initialize the weights of a network using the GenerateLayer function iteratively */
float **GenerateWeights(int* sizes)
{
    int n_layers = sizeof(sizes) / sizeof(sizes[0]) - 1;
    float **weights;
    weights = (float**) malloc (sizeof(float*) * n_layers);
    for(int i = 0; i<n_layers; i++)
    {
        int n = sizes[i], m = sizes[i+1]; 
        float *layer = GenerateLayer(n, m);
        weights[i] = layer; /* Adds new layers to the weights array */
    }
    return weights;
}

NETWORK InitNetwork(int *sizes, int *acti_funcs)
{
    NETWORK network;
    network.weights = GenerateWeights(sizes);
    network.biases = GenerateBiases(sizes);
    network.acti_funcs = acti_funcs;
    network.sizes = sizes;
    network.n_layers = sizeof(sizes) / sizeof(sizes[0]) - 1;
    return network;
}

/* Function to define the feed forward loop for the neural network based on the entry data and activation functions passed*/
float *FeedForward(NETWORK network, float *entry_data)
    /* ADD actual code for the feed forward loop */
{
    float values[2] = {10, 20};
    return values;
}

int main()
{
    return 0;
}
