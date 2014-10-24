#include <iostream>
#include <vector>
#include <cstdlib>

//kristen’s branch

using namespace std;

//declare functions
vector<double> create_ECI_vec (double ECI_1, double ECI_2, double ECI_3);
vector< vector<int> > generate_matrix(int N);
vector<double> calc_corr(vector< vector<int> > matrix);
double calc_corr_1NN(vector< vector<int> > matrix);
double calc_corr_2NN(vector< vector<int> > matrix);
double calc_corr_3NN(vector< vector<int> > matrix);
vector<double> calc_delta_corr(vector< vector<int> > matrix);
double calc_delta_corr_1NN(vector< vector<int> > matrix, int row, int col, int start_atom, int end_atom);
double calc_delta_corr_2NN(vector< vector<int> > matrix, int row, int col, int start_atom, int end_atom);
double calc_delta_corr_3NN(vector< vector<int> > matrix, int row, int col, int start_atom, int end_atom);
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
	corr_vec.at(2) = calc_corr_2NN(matrix);
	return corr_vec;
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

//print corr values for each site and sum 1NN corr values (comment out later)
	cout << "The 1NN correlation values for each site: " << endl;
	for (i=0; i<matrix.size(); i++)
	{
		for (j=0; j<matrix.size(); j++)
		{
			cout << corr_1NN_matrix.at(i).at(j) << "  ";
		}
		cout << endl;
	}
	cout << "The total 1NN correlation value is " << sum_corr_1NN << endl;
	
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
//why do we need the start atom? don't we know the start atom from the input matrix?
double calc_delta_corr_1NN(vector< vector<int> > matrix, int row, int col, int start_atom, int end_atom)
{
	//calculates new 1st Neighbor correlation values
	vector< vector<int> > new_matrix = matrix;
	new_matrix.at(row).at(col) = end_atom;
	return calc_corr_1NN(new_matrix) - calc_corr_1NN(matrix);
}

double calc_delta_corr_2NN(vector< vector<int> > matrix, int row, int col, int start_atom, int end_atom)
{
	//calculates new 2nd Neighbor correlation values
	vector< vector<int> > new_matrix = matrix;
	new_matrix.at(row).at(col) = end_atom;
	return calc_corr_2NN(new_matrix) - calc_corr_2NN(matrix);
}

double calc_delta_corr_3NN(vector< vector<int> > matrix, int row, int col, int start_atom, int end_atom)
{
	//calculates new 3rd Neighbor correlation values
	vector< vector<int> > new_matrix = matrix;
	new_matrix.at(row).at(col) = end_atom;
	return calc_corr_3NN(new_matrix) - calc_corr_3NN(matrix);
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

	//initialie the ECI vector
	vector<double> ECI_vec = create_ECI_vec(ECI_1, ECI_2, ECI_3);
	//generate the NxN matrix
	vector< vector<int> > random_matrix;
	random_matrix = generate_matrix (N);
	//calculate correlation value
	vector<double> corr_vec = calc_corr(random_matrix);


	return 0;
}