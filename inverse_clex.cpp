#include <iostream>
#include <vector>
#include <cstdlib>
#include <math.h> 

//kristen’s branch

using namespace std;

//declare functions
vector<double> create_ECI_vec (double ECI_1, double ECI_2, double ECI_3);
vector< vector<int> > generate_matrix(int N);
vector<double> calc_corr(vector< vector<int> > matrix);
double calc_corr_1NN(vector< vector<int> > matrix);
double calc_corr_2NN(vector< vector<int> > matrix);
double calc_corr_3NN(vector< vector<int> > matrix);
vector<double> calc_delta_corr(vector< vector<int> > matrix , int row, int col, int end_atom);
double calc_delta_corr_1NN(vector< vector<int> > matrix, int row, int col, int end_atom);
double calc_delta_corr_2NN(vector< vector<int> > matrix, int row, int col, int end_atom);
double calc_delta_corr_3NN(vector< vector<int> > matrix, int row, int col, int end_atom);
double dot(vector<double> vector1, vector<double> vector2);


//Initialize our ECI vector
// why can't we do this in main?
vector<double> create_ECI_vec (double ECI_1, double ECI_2, double ECI_3)
{
	vector<double> ECI_vec (3);
	ECI_vec.at(0) = ECI_1;
	ECI_vec.at(1) = ECI_2;
	ECI_vec.at(2) = ECI_3;
	return ECI_vec;
}

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

	//print random matrix to screen (comment out later)
	cout << "Random square matrix:" << endl;
	for (i=0; i<N; i++)
	{
		for (j=0; j<N; j++)
		{
			cout << random_matrix.at(i).at(j) << "  ";
		}
		cout << endl;
	}

	return random_matrix;
}

//Function to create vector of correlation values
vector<double> calc_corr(vector< vector<int> > matrix)
{
	//produces vector of correlation values to be used in final calculation?
	vector<double> corr_vec (3);
	corr_vec.at(0) = calc_corr_1NN(matrix);
	corr_vec.at(1) = calc_corr_2NN(matrix);
	corr_vec.at(2) = calc_corr_3NN(matrix);
	return corr_vec;
}

//Functions to calculate correlation values and generate sum
double calc_corr_1NN(vector< vector<int> > matrix)
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
				corr_1NN_matrix[i][j] += matrix[i][j]*matrix[matrix.size()-1][j];
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

//print corr values for each site and sum 1NN corr values (comment out later)
	cout << "The 1NN correlation values for each site: " << endl;
	for (i=0; i<matrix.size(); i++)
	{
		for (j=0; j<matrix[i].size(); j++)
		{
			cout << corr_1NN_matrix[i][j] << "  ";
		}
		cout << endl;
	}
	cout << "The total 1NN correlation value is " << sum_corr_1NN << endl;
	
	return sum_corr_1NN;
}

double calc_corr_2NN(vector< vector<int> > matrix)
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
			if(i-1<0 && j+1<matrix[i].size())
			{
				corr_2NN_matrix[i][j] += matrix[i][j]*matrix[matrix.size()-1][j+1];
			}
			else if(i-1<0 && j+1 >= matrix[i].size())
			{
				corr_2NN_matrix[i][j] += matrix[i][j]*matrix[matrix.size()-1][0];
			}
			else
			{
				corr_2NN_matrix[i][j] += matrix[i][j]*matrix[i-1][j+1];
			}
			//multiply site basis function by sbf of atom to bottom-right (bottom row/right-most column assume periodicity)
			if(i+1>=matrix.size() && j+1 < matrix[i].size())
			{
				corr_2NN_matrix[i][j] += matrix[i][j]*matrix[0][j+1];
			}
			else if(i+1>=matrix.size() && j+1 >= matrix[i].size())
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

	cout << "The total 2NN correlation value is " << sum_corr_2NN << endl;
	return sum_corr_2NN;
}

double calc_corr_3NN(vector< vector<int> > matrix)
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
			if(j+2>=matrix[i].size() && j+1<matrix[i].size())
			{
				corr_3NN_matrix[i][j] += matrix[i][j]*matrix[i][0];
			}
			else if(j+1>=matrix[i].size())
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

	cout << "The total 3NN correlation value is " << sum_corr_3NN << endl;
	return sum_corr_3NN;
}

//Function to create vector of correlation values on atom change
vector<double> calc_delta_corr(vector< vector<int> > matrix, int row, int col, int end_atom)
{
	//produces vector of the change in correlation values
	vector<double> delta_corr_vec(3);
	delta_corr_vec[0] = calc_delta_corr_1NN(matrix, row, col, end_atom);
	delta_corr_vec[1] = calc_delta_corr_2NN(matrix, row, col, end_atom);
	delta_corr_vec[2] = calc_delta_corr_3NN(matrix, row, col, end_atom);
	return delta_corr_vec;	
}

//Functions to calculate new correlation values and generate sum
double calc_delta_corr_1NN(vector< vector<int> > matrix, int row, int col, int end_atom)
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

double calc_delta_corr_2NN(vector< vector<int> > matrix, int row, int col, int end_atom)
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

double calc_delta_corr_3NN(vector< vector<int> > matrix, int row, int col, int end_atom)
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
		dot += vector1[count]*vector2[count];
	}
	return dot;

}

vector< vector<int> > metropolis(vector< vector<int> > & matrix, vector<double> & ECI_vec, double init_energy, double T)
{
	//boltzmann constant = k
	double k = 8.62e-5;
	for(int h = 0; h < 100; h ++)
	{
		//repeat as many times as there are atoms in the unit cell matrix
		for(int i = 0; i < matrix.size()*matrix[0].size(); i++)
		{
			//create new matrix to make changes in rather than editing matrix itself?
			// vector< vector<int> > new_matrix = matrix;
			//generate random row, col
			int row = rand() % matrix.size();
			int col = rand() % matrix[0].size();
			//flip atom in matrix row/col 
			//TODO: [only works for binary system --> fix to work for any system]
			// matrix[row][col] = (matrix[row][col])*(-1);

			//calculate delta correlation value (based on atom change)
			vector<double> delta_corr_vec = calc_delta_corr(matrix, row, col, matrix[row][col]*-1);

			double delta_energy = dot(ECI_vec, delta_corr_vec);
			//if deltaE is negative, keep change
			if(delta_energy < 0)
			{
				init_energy = init_energy + delta_energy;
				matrix[row][col] = matrix[row][col]*-1;
			}
			//otherwise (deltaE >= 0) use comparison to decided whether to keep or not
			else
			{
				double comparator = exp(-(delta_energy/(k*T)));
				double random = rand() % 1000;
				random = random/1000;

				if(comparator > random)
				{
					init_energy = init_energy + delta_energy;
					matrix[row][col] = matrix[row][col]*-1;
				}
				else
				{
				}
			}

			for(int m = 0; m < matrix.size(); m++)
			{
				for(int n = 0; n < matrix[m].size();n++)
				{
					cout << matrix[m][n] << "   ";
				}
				cout << endl;
			}
		}
	}
	//print out new energy
	//should always be <= to total_energy printed out in main
	cout << "The new energy of the system is: " << init_energy << endl;

	return matrix;
}

//MAIN
int main()
{
	//should prompt user for:
	//1. an N value (size of matrix)
	int N;
	cout << "Please enter value of the size of the square matrix: ";
	cin >> N;
	cout << endl;
	//2. the contents of the ECI (V) vector
	double ECI_1, ECI_2, ECI_3;
	cout << "Please enter value of the 1NN ECI: ";
	cin >> ECI_1;
	cout << endl
		 << "Please enter value of the 2NN ECI: ";
	cin >> ECI_2;
	cout << endl
		 << "Please enter value of the 3NN ECI: ";
	cin >> ECI_3;
	cout << endl;
	double T;
	cout << "Please enter the temperature of the system: ";
	cin >> T;
	cout << endl;

	//initialie the ECI vector
	vector<double> ECI_vec = create_ECI_vec(ECI_1, ECI_2, ECI_3);
	//generate the NxN matrix
	vector< vector<int> > random_matrix;
	random_matrix = generate_matrix (N);
	//calculate correlation value
	vector<double> corr_vec = calc_corr(random_matrix);
	//calculate energy of the system
	double total_energy = dot(ECI_vec, corr_vec);
	cout << "The total energy of the configuration is: " << total_energy << endl;

	//promt user to make a change to matrix
	// int change_row, change_col, new_value;
	// cout << "Please enter row number of site to change: ";
	// cin >> change_row;
	// cout << endl
	// 	 << "Please enter column number of site to change: ";
	// cin >> change_col;
	// cout << endl
	// 	 << "Please enter value to change site to: ";
	// cin >> new_value;
	// cout << endl;

	//calculate delta corr
	// vector<double> delta_corr = calc_delta_corr(random_matrix, change_row, change_col, new_value);
	//calculate total change in energy of the system
	// double delta_total_energy = dot(delta_corr, ECI_vec);
	// cout << "The change in total energy of the configuration is: " << delta_total_energy << endl;

	vector< vector<int> > new_matrix = metropolis(random_matrix, ECI_vec, total_energy, T);

	//print out initial matrix
	cout << "INITIAL MATRIX: " << endl;
	for(int i = 0; i < random_matrix.size(); i++)
	{
		for(int j = 0; j < random_matrix[i].size();j++)
		{
			cout << random_matrix[i][j] << " ";
		}
		cout << endl;
	}

	//print out new matrix
	cout << "NEW MATRIX: " << endl;
	for(int i = 0; i < new_matrix.size(); i++)
	{
		for(int j = 0; j < new_matrix[i].size();j++)
		{
			cout << new_matrix[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}