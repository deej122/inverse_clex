#include <iostream>
#include <vector>
#include <cstdlib>

//kristen’s branch

using namespace std;

//Initialize our ECI vector
vector<double> ECI;

//Function to generate an NxN matrix
vector< vector<int> > generate_matrix(int N)
{
	//should generate an NxN 2D vector
	int i,j;
	vector<int> row (N, 0);
	vector< vector<int> > random_matrix (N, row);

	srand(time(NULL));
	for (i=0; i<N; i++)
	{
		for (j=0; j<N; j++)
		{
			random_matrix.at(i).at(j) = rand()%2;		
			if (random_matrix.at(i).at(j) == 0)
			{
				random_matrix.at(i).at(j) = -1;
			}	
		}
	}
	return random_matrix;

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
	
	int i, j;
	double sum_corr_1NN = 0;
	//create’s a matrix of the same size as input matrix, filled with 0’s
	vector<double> temp_vec (matrix.size(), 0);
	vector< vector<double> > corr_1NN_matrix (matrix.size(), temp_vec);

	for (i=0; i<matrix.size(); i++)
	{
		for(j=0; j<matrix.size(); j++)
		{
			//multiply site basis function’s of each atom with atom above (if on top row, assumes periodicity) and adds to 1NN correlation matrix
			if (i-1<0)
			{
				corr_1NN_matrix.at(i).at(j) += matrix.at(i).at(j)*matrix.at(matrix.size()-1).at(j);
			}
			else
			{
				corr_1NN_matrix.at(i).at(j) += matrix.at(i).at(j)*matrix.at(i-1).at(j);
			}

			//multiply site basis function’s of each atom with atom to the left (if on first column, assumes periodicity) and adds to 1NN correlation matrix
			if (j-1<0)
			{
				corr_1NN_matrix.at(i).at(j) += matrix.at(i).at(j)*matrix.at(i).at(matrix.size()-1);
			}
			else
			{
				corr_1NN_matrix.at(i).at(j) += matrix.at(i).at(j)*matrix.at(i).at(j-1);
			}
		}
	} 
	
	//sums all the 1NN correlation values
	for (i=0; i<matrix.size(); i++)
	{
		for (j=0; j<matrix.size(); j++)
		{
			sum_corr_1NN += corr_1NN_matrix.at(i).at(j);
		}
	}
	
	return sum_corr_1NN;
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
	int count;
	double dot=0;
	if (vector1.size() != vector2.size() )
	{
		cout << "ECI vector and corelation values vector are not the same size" << endl;
	}
	for (count=0; count<vector1.size(); count++)
	{
		dot += vector1.at(count)*vector2.at(count);
	}
	return dot;

}

//MAIN
int main()
{
	//should prompt user for:
	//1. an N value (size of matrix)
	//2. the contents of the ECI (V) vector
}