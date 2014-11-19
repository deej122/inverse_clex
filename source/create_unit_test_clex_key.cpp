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

	//read in json information from ECI_conditions.json and set variables equal to the inputs
	read_json_in(temp, dim, species, ECI_vec, num_passes);

	//declare json out file to set inputs of functions
	jsonParser json_out_inputs;
	//declare json out file to set key of functions
	jsonParser json_out_key;

	//generate matrix and set as inputs in clex_test_inputs.json
	vector< vector<int> > matrix = generate_matrix(dim[0], dim[1]);
	json_out_inputs["calc_corr_inputs"].push_back(jsonParser::array());
	for(int i=0; i<dim[0]; i++)
	{
		json_out_inputs["calc_corr_inputs"][json_out_inputs["calc_corr_inputs"].size()-1].pushback(jsonParser::array());
		json_out_inputs["calc_corr_inputs"][json_out_inputs["calc_corr_inputs"].size-1][i] = matrix[i];
	}


	//write json files
	json_out_inputs.write(std::string("clex_test_inputs.json"));
	json_out_key.write(std::string("clex_test_outputs.json"));
}