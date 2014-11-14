#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

//declaring functions
vector<double> create_ECI_vec (const double & ECI_1, const double & ECI_2, const double & ECI_3);
vector< vector<int> > generate_matrix(const int & row, const int & col);
vector<double> calc_corr(const vector< vector<int> > & matrix);
double calc_corr_1NN(const vector< vector<int> > & matrix);
double calc_corr_2NN(const vector< vector<int> > & matrix);
double calc_corr_3NN(const vector< vector<int> > & matrix);
vector<double> calc_delta_corr(const vector< vector<int> > & matrix , const int & row, const int & col, const int & end_atom);
double calc_delta_corr_1NN(const vector< vector<int> > & matrix, const int & row, const int & col, const int & end_atom);
double calc_delta_corr_2NN(const vector< vector<int> > & matrix, const int & row, const int & col, const int & end_atom);
double calc_delta_corr_3NN(const vector< vector<int> > & matrix, const int & row, const int & col, const int & end_atom);
double dot(const vector<double> & vector1, const vector<double> & vector2);
template<class T>
void print_matrix (const vector< vector<T> > & matrix);


//creates a vector of the ECI constants passed in
vector<double> create_ECI_vec (const double & ECI_1, const double & ECI_2, const double & ECI_3)
{
	vector<double> ECI_vec (3);
	ECI_vec.at(0) = ECI_1;
	ECI_vec.at(1) = ECI_2;
	ECI_vec.at(2) = ECI_3;
	return ECI_vec;
}

//generates a random matrix of 1's and -1's of size row x col
vector< vector<int> > generate_matrix(const int & row, const int & col)
{
	//should generate an NxN 2D vector
	int i,j;
	vector<int> temp_vec (col, 0);
	vector< vector<int> > random_matrix (row, temp_vec);

	srand(time(NULL));
	for (i=0; i<row; i++)
	{
		for (j=0; j<col; j++)
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

//Function to create vector <1NN,2NN,3NN> correlation values
vector<double> calc_corr(const vector< vector<int> > & matrix)
{
	vector<double> corr_vec (3);
	corr_vec.at(0) = calc_corr_1NN(matrix);
	corr_vec.at(1) = calc_corr_2NN(matrix);
	corr_vec.at(2) = calc_corr_3NN(matrix);
	return corr_vec;
}

//Function to calculate 1NN correlation values and generate sum
double calc_corr_1NN(const vector< vector<int> > & matrix)
{
	//calculates 1st Neighbor correlation values
	int i, j;
	double sum_corr_1NN = 0;
	//create’s a matrix of the same size as input matrix, filled with 0’s
	vector<double> temp_vec (matrix[0].size(), 0);
	vector< vector<double> > corr_1NN_matrix (matrix.size(), temp_vec);

	for (i=0; i<matrix.size(); i++)
	{
		for(j=0; j<matrix[i].size(); j++)
		{
			//multiply site basis function’s of each atom with atom above (if on top row, assumes periodicity) and adds to 1NN correlation matrix
			if (i-1<0)
			{
				corr_1NN_matrix[i][j] += matrix[i][j]*matrix[matrix[i].size()-1][j];
			}
			else
			{
				corr_1NN_matrix[i][j] += matrix[i][j]*matrix[i-1][j];
			}

			//multiply site basis function’s of each atom with atom to the left (if on first column, assumes periodicity) and adds to 1NN correlation matrix
			if (j-1<0)
			{
				corr_1NN_matrix[i][j] += matrix[i][j]*matrix[i][matrix[i].size()-1];
			}
			else
			{
				corr_1NN_matrix[i][j] += matrix[i][j]*matrix[i][j-1];
			}
		}
	} 

	//sums all the 1NN correlation values
	for (i=0; i<matrix.size(); i++)
	{
		for (j=0; j<matrix[i].size(); j++)
		{
			sum_corr_1NN += corr_1NN_matrix[i][j];
		}
	}
	return sum_corr_1NN;
}

//Function to calculate 2NN correlation values and generate sum
double calc_corr_2NN(const vector< vector<int> > & matrix)
{
	//calculates 2nd Neighbor correlation values
	int i, j;
	double sum_corr_2NN = 0;

	vector<double> temp_vec (matrix.size(), 0);
	vector< vector<double> > corr_2NN_matrix(matrix.size(), temp_vec);

	for(i=0; i < matrix.size(); i++)
	{
		for(j=0; j < matrix[i].size(); j++)
		{
			//multiply site basis function by sbf of atom to top-right (top row/right-most column assume periodicity)
			if(i-1<0 && j+1<matrix.size())
			{
				corr_2NN_matrix[i][j] += matrix[i][j]*matrix[matrix.size()-1][j+1];
			}
			else if(i-1<0 && j+1 >= matrix.size())
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
	for(i=0;i<matrix.size();i++)
	{
		for(j=0;j<matrix[i].size();j++)
		{
			sum_corr_2NN += corr_2NN_matrix[i][j];
		}
	}
	return sum_corr_2NN;
}

//Function to calculate 2NN correlation values and generate sum
double calc_corr_3NN(const vector< vector<int> > & matrix)
{
	//calculates 3rd Neighbor correlation values
	int i, j;
	double sum_corr_3NN;

	vector<double> temp_vec (matrix.size(), 0);
	vector< vector<double> > corr_3NN_matrix(matrix.size(), temp_vec);

	for(i=0; i < matrix.size(); i++)
	{
		for(j=0; j < matrix[i].size(); j++)
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
	for(i=0;i<matrix.size();i++)
	{
		for(j=0;j<matrix[i].size();j++)
		{
			sum_corr_3NN += corr_3NN_matrix[i][j];
		}
	}
	return sum_corr_3NN;
}

//Function to create vector of change in correlation values after atom change
vector<double> calc_delta_corr(const vector< vector<int> > & matrix , const int & row, const int & col, const int & end_atom)
{
	//produces vector of the change in correlation values
	vector<double> delta_corr_vec(3);
	delta_corr_vec[0] = calc_delta_corr_1NN(matrix, row, col, end_atom);
	delta_corr_vec[1] = calc_delta_corr_2NN(matrix, row, col, end_atom);
	delta_corr_vec[2] = calc_delta_corr_3NN(matrix, row, col, end_atom);
	return delta_corr_vec;	
}

//Function to calculate 1NN delta correlation values and returns the sum
double calc_delta_corr_1NN(const vector< vector<int> > & matrix, const int & row, const int & col, const int & end_atom)
{
	//calculates new 1st Neighbor correlation values
	int row_above = row-1;
	int row_below = row+1;
	int col_left = col-1;
	int col_right = col+1;
	if (row_above<0)
	{
		row_above = matrix.size()-1;
	}
	if (row_below >= matrix.size())
	{
		row_below = 0;
	}
	if (col_left < 0)
	{
		col_left = matrix[0].size()-1;
	}
	if (col_right >= matrix[0].size())
	{
		col_right = 0;
	}

	return (end_atom - matrix[row][col])*(matrix[row][col_left] + matrix[row][col_right] + matrix [row_below][col] + matrix[row_above][col]);
}

//Function to calculate 2NN delta correlation values and returns the sum
double calc_delta_corr_2NN(const vector< vector<int> > & matrix, const int & row, const int & col, const int & end_atom)
{
	//calculates new 2nd Neighbor correlation values
	int row_above = row-1;
	int row_below = row+1;
	int col_left = col-1;
	int col_right = col+1;
	if (row_above<0)
	{
		row_above = matrix.size()-1;
	}
	if (row_below >= matrix.size())
	{
		row_below = 0;
	}
	if (col_left < 0)
	{
		col_left = matrix[0].size()-1;
	}
	if (col_right >= matrix[0].size())
	{
		col_right = 0;
	}

	return (end_atom - matrix[row][col])*(matrix[row_above][col_left] + matrix[row_above][col_right] + matrix [row_below][col_left] + matrix[row_below][col_right]);
}

//Function to calculate 3NN delta correlation values and returns the sum
double calc_delta_corr_3NN(const vector< vector<int> > & matrix, const int & row, const int & col, const int & end_atom)
{
	//calculates new 3rd Neighbor correlation values
	int row_2above = row-2;
	int row_2below = row+2;
	int col_2left = col-2;
	int col_2right = col+2;
	if (row_2above<0)
	{
		row_2above = matrix.size() + row_2above;
	}
	if (row_2below >= matrix.size())
	{
		row_2below = row_2below - matrix.size();
	}
	if (col_2left < 0)
	{
		col_2left = matrix[0].size() + col_2left;
	}
	if (col_2right >= matrix[0].size())
	{
		col_2right = col_2right - matrix[0].size();
	}
	return (end_atom - matrix[row][col])*(matrix[row][col_2left] + matrix[row][col_2right] + matrix [row_2below][col] + matrix[row_2above][col]);
}

//Function to calculate energy of the system using a simple dot product of our ECI vector and our vector of correlation values
double dot(const vector<double> & vector1, const vector<double> & vector2)
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
		dot += vector1[count]*vector2[count];
	}
	return dot;

}
