#include <iostream>
#include <vector>
#include <cstdlib>
#include <math.h>
#include "../external/jsonParser/jsonParser.hh"
#include "../h/clex.h"
#include "../h/metropolis.h"

// comment
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

	cout << "Output" << endl;
	//generates the matrix
	//will have to change this when have more than 2 atoms and when theyre different than 1 and -1
	cout << dim[0] << endl;
	cout << dim[1] << endl;
	vector< vector<int> > matrix = generate_matrix(dim[0], dim[1]);

	print_matrix(matrix);

	cout << "generated matrix" << endl;
	// write out to a json file
	int pass_count = 0;
	write_json_out (ECI_vec, matrix, json_out, pass_count, species);

	cout << 'writing json' << endl;

	// allow the matrix to equilibriate. these passes are not considered when doing any calculations
	for(int equilibriate=0; equilibriate < 10000; equilibriate++)
	{
		matrix=metropolis(matrix, ECI_vec, temp);
	}

	for(pass_count=1; pass_count <= num_passes; pass_count++)
	{
		matrix=metropolis(matrix, ECI_vec, temp);
		write_json_out (ECI_vec, matrix, json_out, pass_count, species);
	}

	json_out.write(std::string("monte_carlo_calcs_1000.json"));
	
	return 0;
}