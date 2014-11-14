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
	json_out["plotting_data"].push_back(jsonParser::array());


	vector< vector<int> > matrix = generate_matrix(dim[0], dim[1]);
	cout << "generated matrix" << endl;

	// write out to a json file
	int pass_count = 0;

	cout << 'writing json' << endl;

	for (temp=0; temp<=500; temp+=10)
	{

		for(pass_count=1; pass_count <= num_passes; pass_count++)
		{
			matrix=metropolis(matrix, ECI_vec, temp);
		}
		cout << "finished metropolis" << endl;

		double average=0;
		int i,j;
		for (i=0; i<matrix.size(); i++)
		{
			for (j=0; j<matrix[i].size(); j++)
			{
				average += matrix[i][j];
			}

		}
		cout << "about to calculate average" << endl;

		average = average/(matrix.size()*matrix[0].size());

		json_out["plotting_data"][temp] = jsonParser::array();
		json_out["plotting_data"][temp].push_back(temp);
		json_out["plotting_data"][temp].push_back(average);
	}
	
	cout << "here 100" << endl;
	json_out.write(std::string("plotting_data.json"));
	
	return 0;
}