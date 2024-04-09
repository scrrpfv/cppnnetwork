#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <numeric>

using namespace std;

/* Function to initialize network's columns with random values */
vector<float> GenerateColumn(int n)
{
    /* Creating the rng with normal distribution around 0 */
    random_device rd;
    mt19937_64 gen(rd());
    normal_distribution<float> dis(0, 1);
    auto rand = [&](){ return dis(gen); }; /* Ugly piece of code to ensure no repeats */

    vector<float> column(n);
    for(int i=0; i<n; i++)
    {
        column[i] = rand(); /* Attributes random values to the columns */
    }
    return column;
}

/* Function to initialize the weights of a network using the GenerateColumn function iteratively */
vector<vector<float>> GenerateWeights(vector<int> sizes)
{
    vector<vector<float>> weights;
    for(int rowsize : sizes)
    {
        weights.push_back(GenerateColumn(rowsize)); /* Adds new column to the weights vector */
    }
    return weights;
}

/* Function to define the feed forward loop for the neural network based on the entry data and activation functions passed*/
vector<float> FeedForward(
    vector<vector<float>> weights,
    vector<vector<float>> biases, /* TODO add function to initialize biases (maybe all set to 0) */
    vector<float> entry_data,
    vector<int> activation_functions /* TODO define some differente ativation functions for the ff loop*/
    )
    /* ADD actual code for the feed forward loop */
{
    int n_columns = weights.size();
    vector<float> result(n_columns); /* Random placeholder */
    return result;
}

int main()
{
    vector<int> size = {5, 10, 10, 5};
    vector<vector<float>> weights = GenerateWeights(size);
    for(int i=0; i<weights.size(); i++)
    {
        cout << "Column: " << i << endl;

        vector<float> column = weights[i];

        for(int j=0; j<column.size(); j++)
        {
            cout << column[j] << endl;
        }
    }
    return 0;
}
