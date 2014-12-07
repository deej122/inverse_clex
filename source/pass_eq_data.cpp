#include <iostream>
#include <vector>
#include <cstdlib>
#include <math.h>
#include "../external/jsonParser/jsonParser.hh"
#include "../h/clex.h"
#include "../h/metropolis.h"

using namespace std;

int main()
{
	//declare variables
	int num_passes;
	double temp;
	vector<int> dim;
	vector<double> ECI_vec, species;
	double sum_pass_till_eq = 0;

	//read in json information from ECI_conditions.json and set variables equal to the inputs
	read_json_in(temp, dim, species, ECI_vec, num_passes);
	cout << "here 2" << endl;

	//outputs the conditions ot a json file
	jsonParser json_out_pass_eq_data;
	json_out_pass_eq_data["passes_till_eqilibrium"] = jsonParser::array();
	cout << "here 1" << endl;

	int max_passes = 0;
	int min_passes = 1000;
	int trial_count;

	// this tests 100 times how many passes are needed until the matrix reaches equilibrium
	for(trial_count = 0; trial_count < 100; trial_count++)
	{
		cout << "for-loop 1" << endl;
		vector< vector<int> > matrix = generate_matrix(dim[0], dim[1]);

		bool passed_eq_test = false;

		for (int pass_count = 1; pass_count < 1001; pass_count++)
		{
			cout << "for-loop 2" << endl;
			matrix=metropolis(matrix, ECI_vec, temp);
			int i = 0;
			int j = 0;
			bool passed_eq_test = false;
			int species = matrix[0][0];

			//checks if the entire matrix is one species and returns a bool true if it is
			while (matrix[i][j] == species)
			{
				cout << "while-loop 1" << endl;
				j++;
				//if it has reached the end of the row, will move onto the next row
				if (j >= matrix[i].size())
				{
					cout << "if 1" << endl;
					j = 0;
					i++;
				}
				// if the entire matrix is one species, this if loop will exit the while loop without a seg fault
				if (i >= matrix.size() and j >= matrix.size())
				{
					cout << "if 2" << endl;
					passed_eq_test = true;
					species = -1;
					j += -1;
				}
			}

			cout << "out of while loop" << endl;

			//if the matrix is one species, it will exit out of this for-loop, otherwise it will move onto the next pass
			if (passed_eq_test == true)
			{
				if (pass_count < 1001)
				{
					pass_count = 1001;
				}
			}

			cout << "here 21" << endl;

			//writes out to the json
			json_out_pass_eq_data["passes_till_equilibrium"].push_back(pass_count);
			sum_pass_till_eq += pass_count;

			cout << "here 22" << endl;

			// checks if the number of passes is a min or max value thus far
			if (pass_count < min_passes)
			{
				min_passes = pass_count;
			}
			if (pass_count > max_passes)
			{
				max_passes = pass_count;
			}

			cout << "end of for loop" << endl;

		}

		cout << "out of for-loop" << endl;
		json_out_pass_eq_data["average_passes_till_equilibrium"] = sum_pass_till_eq/(trial_count+1);
		json_out_pass_eq_data["minumum_passes_till_equilibrium"] = min_passes;
		json_out_pass_eq_data["maximum_passes_till_equilibrium"] = max_passes;
		json_out_pass_eq_data.write(std::string("pass_eq_data.json"));

	}
	return 0;

}

