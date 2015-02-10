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

	//outputs the conditions to a json file
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
		
		// So we should write to a new json file after every pass, like this?
		// Will this automatically clear the jsonParser variable after 'write', or is there something we need to add to do that?
		/* THE CODE:

		string pc = to_string(pass_count);
		string filename = "monte_carlo_calcs_" + pc + ".json";
		json_out.write(std::string(filename));

		*/
	}

	// Instead of writing out, here?
	// If so, we need to concatenate the written files from the loop into one file (probably done here, after the loop finishes)
	json_out.write(std::string("monte_carlo_calcs.json"));
	
	return 0;
}