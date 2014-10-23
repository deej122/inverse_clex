#include <iostream>
#include <vector>

//kristen’s branch

using namespace std;

//Initialize our ECI vector
vector<double> ECI;

//Function to generate an NxN matrix
vector< vector<int> > generate_matrix(int N)
{
	//should generate an NxN 2D vector
}

//Function to create vector of correlation values
vector<double> calc_corr(vector< vector<int> > matrix)
{
	//produces vector of correlation values to be used in final calculation?
}

//Functions to calculate correlation values and generate sum
double calc_corr_1NN(vector< vector<int> > matrix)
{
	//calculates 1st Neighbor correlation values
}

double calc_corr_2NN(vector< vector<int> > matrix)
{
	//calculates 2nd Neighbor correlation values
}

double calc_corr_3NN(vector< vector<int> > matrix)
{
	//calculates 3rd Neighbor correlation values
}

//Function to create vector of correlation values on atom change
vector<double> calc_delta_corr(vector< vector<int> > matrix)
{
	//produces vector of new correlation values to be used in final calculation?
}

//Functions to calculate new correlation values and generate sum
double calc_delta_corr_1NN(vector< vector<int> > matrix, int row, int col, int start_atom, int end_atom)
{
	//calculates new 1st Neighbor correlation values
}

double calc_delta_corr_2NN(vector< vector<int> > matrix, int row, int col, int start_atom, int end_atom)
{
	//calculates new 2nd Neighbor correlation values
}

double calc_delta_corr_3NN(vector< vector<int> > matrix, int row, int col, int start_atom, int end_atom)
{
	//calculates new 3rd Neighbor correlation values
}

//Function to calculate energy of the system using a simple dot product of our ECI vector and our vector of correlation values
double dot(vector<double> vector1, vector<double> vector2)
{
	//dot product of corresponding ECI and correlation values
	//ECI = vector1, correlation values = vector2
}

//MAIN
int main()
{
	//should prompt user for:
	//1. an N value (size of matrix)
	//2. the contents of the ECI (V) vector
}