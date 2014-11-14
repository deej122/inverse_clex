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
	json_out["plotting_data"] = jsonParser::array();


	vector< vector<int> > matrix = generate_matrix(dim[0], dim[1]);
	cout << "generated matrix" << endl;

	// write out to a json file
	int pass_count = 0;
	int index = 0;

	int i,j;

	double mean_spin = 0;
	double ensemble_average = 0;

	cout << 'writing json' << endl;

	for (temp=0.001; temp<=1000000000; temp = temp*10)
	{
		double mean_spin_sum = 0;
		for(pass_count=1; pass_count <= num_passes; pass_count++)
		{
			double spin_sum = 0;
			matrix=metropolis(matrix, ECI_vec, temp);
			for (i=0; i<matrix.size(); i++)
			{
				for (j=0; j<matrix[i].size(); j++)
				{
					spin_sum += matrix[i][j];
				}

			}
			mean_spin = abs(spin_sum/(matrix.size()*matrix[0].size()));

			mean_spin_sum += mean_spin;
		}

		ensemble_average = mean_spin_sum/(num_passes);

		cout << "begin" << endl;
		cout << "index: " << index << endl;
		json_out["plotting_data"].push_back(jsonParser::array());
		// json_out["plotting_data"][index].push_back(jsonParser::array());
		cout << "uno" << endl;
		// json_out["plotting_data"][index]["temperature"] = temp;
		json_out["plotting_data"][index].push_back(temp);
		cout << "dos" << endl;
		// json_out["plotting_data"][index]["average"] = average;
		json_out["plotting_data"][index].push_back(ensemble_average);
		cout << "tres" << endl;

		index += 1;
	}
	
	cout << "here 100" << endl;
	json_out.write(std::string("plotting_data.json"));
	
	return 0;
}