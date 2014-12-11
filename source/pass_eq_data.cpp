#include <iostream>
#include <vector>
#include <cstdlib>
#include <math.h>
#include "../external/jsonParser/jsonParser.hh"
#include "../h/clex.h"
#include "../h/metropolis.h"

using namespace std;

int pass_eq()
{
	//declare variables
	int num_passes;
	double temp;
	vector<int> dim;
	vector<double> ECI_vec, species;
	double sum_pass_till_eq = 0;

	// change these for different tests
	int test_pass_num = 1000;
	int test_trial_num = 10;

	//read in json information from ECI_conditions.json and set variables equal to the inputs
	read_json_in(temp, dim, species, ECI_vec, num_passes);
	cout << "here 2" << endl;

	//outputs the conditions ot a json file
	jsonParser json_out_pass_eq_data;
	json_out_pass_eq_data["passes_till_eqilibrium"] = jsonParser::array();
	cout << "here 1" << endl;

	int max_passes = 0;
	int min_passes = test_pass_num;
	int trial_count;


	// this tests 100 times how many passes are needed until the matrix reaches equilibrium
	for(trial_count = 0; trial_count < test_trial_num; trial_count++)
	{
		cout << "for-loop 1" << endl;

		//for every trial, generates a new matrix
		vector< vector<int> > matrix = generate_matrix(dim[0], dim[1]);
		//print out matrix 
		print_matrix(matrix);
		bool passed_eq_test = false;

		//tests for how many passes it must go through to have a matrix of all the same values (equilibrate)
		for (int pass_count = 0; pass_count < test_pass_num; pass_count++)
		{
			cout << "for-loop 2" << endl;
			matrix=metropolis(matrix, ECI_vec, temp);

			//for every pass, these must get reset
			int row = 0;
			int col = 0;
			int species = matrix[0][0];
			int pass_eq;

			//checks if the entire matrix is one species and returns a bool true if it is. exits while loop as soon as it finds a species that is different
			while (matrix[row][col] == species)
			{
				cout << "while-loop 1" << endl;
				col++;
				//if it has reached the end of the row, will move onto the next row
				if (col = matrix[row].size())
				{
					cout << "if 1" << endl;
					col = 0;
					row++;
					// if the entire matrix is one species (has reached the end of the last row), this if loop will exit the while loop without a seg fault
					if (row = matrix.size())
					{
						cout << "if 2" << endl;
						passed_eq_test = true;
						pass_eq = pass_count+1;
						row = 0;
						species = species*-1;
					}
				}

				cout << "end of while loop" << endl;
			}

			cout << "out of while loop" << endl;

			//if the matrix is one species, it will exit out of this for-loop, otherwise it will move onto the next pass
			if (passed_eq_test == true)
			{
				json_out_pass_eq_data["passes_till_eqilibrium"].push_back(pass_eq);
				cout << "passed test. pass_eq = " << pass_eq << endl;
				sum_pass_till_eq += pass_eq;
				if (pass_eq < min_passes)
				{
					min_passes = pass_eq;
				}
				if (pass_eq > max_passes)
				{
					max_passes = pass_eq;
				}
				pass_count = test_pass_num;
			}

			cout << "end of for loop" << endl;

			//if matrix is still not equilibrated after the last pass, will print out last pass as the number of passes needed to equilibrate
			if (passed_eq_test == false and pass_count+1 == test_pass_num)
			{
				json_out_pass_eq_data["passes_till_eqilibrium"].push_back(test_pass_num);
				cout << "reached end of passes w/o equilibrating" << endl;
				sum_pass_till_eq += test_pass_num;
				max_passes = test_pass_num;
			}
		}

		cout << "out of for-loop" << endl;

		json_out_pass_eq_data["average_passes_till_equilibrium"] = sum_pass_till_eq/(test_trial_num);
		json_out_pass_eq_data["minumum_passes_till_equilibrium"] = min_passes;
		json_out_pass_eq_data["maximum_passes_till_equilibrium"] = max_passes;

		json_out_pass_eq_data.write(std::string("pass_eq_data.json"));

	}
	return 0;

}

