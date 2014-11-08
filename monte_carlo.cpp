#include <iostream>
#include <vector>
#include <cstdlib>
#include <math.h>
#include "jsonParser.hh"
#include "clex.h"
#include "metropolis.h"

using namespace std;

int main()
{
	//declare variables
	int num_passes;
	double temp;
	vector<int> dim;
	vector<double> ECI_vec, species;

	//read in json information from ECI_conditions.json and set variables equal to the inputs
	read_json_in(temp, dim, species, ECI_vec, num_passes);

	//outputs the conditions ot a json file
	jsonParser json_out;
	json_out["Temp"] = temp;
	json_out["Species"] = species;
	json_out["Data_by_pass"] = jsonParser::array();

	//generates the matrix
	//will have to change this when have more than 2 atoms and when theyre different than 1 and -1
	vector< vector<int> > matrix = generate_matrix(dim[0], dim[1]);

	// write out to a json file
	int pass_count = 0;
	write_json_out (ECI_vec, matrix, json_out, pass_count, species)

	for(pass_count=1; pass_count <= num_passes; pass_count++)
	{
		matrix=metropolis(matrix, ECI_vec, temp);
		write_json_out (ECI_vec, matrix, json_out, pass_count, species);

	}

	return 0;
}