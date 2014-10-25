#include <iostream>
#include <vector>

using namespace std;

//Initialize our ECI vector
vector<double> ECI;

//Function to generate an NxN matrix
vector< vector<int> > generate_matrix(int N)
{
	//should generate an NxN 2D vector
}

//Functions to calculate correlation values and generate sum
double calc_corr_1NN(vector< vector<int> > matrix)
{
	//calculates 1st Neighbor correlation values
}

double calc_corr_2NN(vector< vector<int> > matrix)
{
	//calculates 2nd Neighbor correlation values
	int i, j;
	double sum_corr_2NN = 0;

	vector<double> temp_vec (matrix.size(), 0);
	vector< vector<double> > corr_2NN_matrix(matrix.size(), temp_vec);

	for(i=0; i < matrix[i].size(); i++)
	{
		for(j=0; j < matrix[j].size(); j++)
		{
			//multiply site basis function by sbf of atom to top-right (top row/right-most column assume periodicity)
			if(i-1<0 && j+1<matrix[j].size())
			{
				corr_2NN_matrix[i][j] += matrix[i][j]*matrix[matrix.size()-1][j+1];
			}
			else if(i-1<0 && j+1 >= matrix[j].size())
			{
				corr_2NN_matrix[i][j] += matrix[i][j]*matrix[matrix.size()-1][0];
			}
			else
			{
				corr_2NN_matrix[i][j] += matrix[i][j]*matrix[i-1][j+1];
			}
			//multiply site basis function by sbf of atom to bottom-right (bottom row/right-most column assume periodicity)
			if(i+1>=matrix[i].size() && j+1 < matrix[j].size())
			{
				corr_2NN_matrix[i][j] += matrix[i][j]*matrix[0][j+1];
			}
			else if(i+1>=matrix[i].size() && j+1 >= matrix[j].size())
			{
				corr_2NN_matrix[i][j] += matrix[i][j]*matrix[0][0];
			}
			else
			{
				corr_2NN_matrix[i][j] += matrix[i][j]*matrix[i+1][j+1];
			}
		}
	}

	//add all 2NN correlation values
	for(i=0;i<matrix[i].size();i++)
	{
		for(j=0;j<matrix[j].size();j++)
		{
			sum_corr_2NN += corr_2NN_matrix[i][j];
		}
	}

	return sum_corr_2NN;
}

double calc_corr_3NN(vector< vector<int> > matrix)
{
	//calculates 3rd Neighbor correlation values
	int i, j;
	double sum_corr_3NN;

	vector<double> temp_vec (matrix.size(), 0);
	vector< vector<double> > corr_3NN_matrix(matrix.size(), temp_vec);

	for(i=0; i < matrix[i].size(); i++)
	{
		for(j=0; j < matrix[j].size(); j++)
		{
			//multiple sbf by atom two spots above (assume periodicity if in top two rows)
			if(i-2<0 && i-1>=0)
			{
				corr_3NN_matrix[i][j] += matrix[i][j]*matrix[matrix.size()-1][j];
			}
			else if(i-1<0)
			{
				corr_3NN_matrix[i][j] += matrix[i][j]*matrix[matrix.size()-2][j];
			}
			else
			{
				corr_3NN_matrix[i][j] += matrix[i][j]*matrix[i-2][j];
			}
			//multiply sbf by atom two to the right (assume periodicity if in two right-most columns)
			if(j+2>=matrix[j].size() && j+1<matrix[j].size())
			{
				corr_3NN_matrix[i][j] += matrix[i][j]*matrix[i][0];
			}
			else if(j+1>=matrix[j].size())
			{
				corr_3NN_matrix[i][j] += matrix[i][j]*matrix[i][1];
			}
			else
			{
				corr_3NN_matrix[i][j] += matrix[i][j]*matrix[i][j+1];
			}
		}
	}

	//add all 3NN correlation values
	for(i=0;i<matrix[i].size();i++)
	{
		for(j=0;j<matrix[j].size();j++)
		{
			sum_corr_3NN += corr_3NN_matrix[i][j];
		}
	}

	return sum_corr_3NN;
}

//Function to create vector of correlation values
vector<double> calc_corr(vector< vector<int> > matrix)
{
	//produces vector of correlation values to be used in final calculation?
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