#include <iostream>
#include <vector>
#include <cstdlib>
#include <math.h>
#include "../external/jsonParser/jsonParser.hh"
#include "../h/clex.h"

using namespace std;

void read_json_in (double & temp, vector<int> & dim, vector<double> & species, vector<double> & ECI_vec, int & num_passes);
void write_json_out (const vector<double> ECI_vec, const vector< vector<int> > & matrix, jsonParser & json_out, const int & pass_count, const vector<double> & species);
vector< vector<int> > metropolis(vector< vector<int> > & matrix, const vector<double> & ECI_vec, const double & T);


void read_json_in (double & temp, vector<int> & dim, vector<double> & species, vector<double> & ECI_vec, int & num_passes)
{
	jsonParser json_in;
	json_in.read(std::string("ECI_conditions.json"));
	temp = json_in["Temperature"].get<double>();
	dim = json_in["Dimensions"].get< vector<int> >();
	species = json_in["Species"].get< vector<double> >();
	ECI_vec = json_in["ECI"].get< vector<double> >();
	num_passes = json_in["Passes"].get<int>();
	// json_in.close();
	return;
} 

void write_json_out (const vector<double> ECI_vec, const vector< vector<int> > & matrix, jsonParser & json_out, const int & pass_count, const vector<double> & species)
{
	cout << "Here 1" << endl;
	//creates another object in the data_by_pass vector of objects
	json_out["Data_by_pass"].push_back(jsonParser::array());
	json_out["Data_by_pass"][pass_count] = jsonParser::object();
	json_out["Data_by_pass"][pass_count]["pass"] = pass_count;

	cout << "Here 2" << endl;
	//calculates corr vector
	vector<double> corr_vec = calc_corr(matrix);

	cout << "3" << endl;
	//write corr vector to object in json
	json_out["Data_by_pass"][pass_count]["corr"] = corr_vec;

	cout << "Here 4" << endl;
	//calculates energy of the system
	double energy = dot(corr_vec, ECI_vec);
	//writes out energy to object to json
	json_out["Data_by_pass"][pass_count]["energy"] = energy;

	cout << "Here 5" << endl;
	//counts how many of each species
	vector<int> num_species (species.size(), 0);
	int row, col;
	cout << "Here 6" << endl;
	for (row=0; row< matrix.size(); row++)
	{
		cout << "Here 7" << endl;
		for (col=0; col<matrix[row].size(); col++)
		{
			cout << "Here 8" << endl;
			for(int s=0; s<species.size(); s++)
			{
				cout << "Here 9" << endl;
				if (matrix[row][col] == species[s])
				{
					num_species[s]++;
				}
			}
		}
	}

	cout << "End of loop" << endl;
	//writes out the vector of number of species to json
	json_out["Data_by_pass"][pass_count]["num_species"] = num_species;

	cout << "Here 10" << endl;
	//creates another vector inside the site object called "sites"
	json_out["Data_by_pass"][pass_count]["sites"] = jsonParser::array();

	cout << "Here 11" << endl;
	//finds the coordinates, curr_occupant, and delta_correlations for each site in matrix
	int atom_count = 0;
	for(row = 0; row < matrix.size(); row++)
	{
		cout << "Here 12" << endl;
		for(col=0; col < matrix[row].size(); col++)
		{
			cout << "Here 13" << endl;
			jsonParser &tjson = json_out["Data_by_pass"][pass_count]["sites"];
			tjson.push_back(jsonParser::object());
			atom_count = tjson.size()-1;
			//creates a coordination vector and writes to json
			vector<int> coord (2);
			coord[0]=row;
			coord[1]=col;
			tjson[atom_count]["coord"] = coord;
			//writes to json the current occupants
			tjson[atom_count]["curr_occupant"] = matrix[row][col];
			//creates a vector of delta corr values for each change in species (vector of vector)
			tjson[atom_count]["delta_corrs"] = jsonParser::array();
			vector<double> delta_corr (3);
			for(int s=0; s<species.size(); s++)
			{
				tjson[atom_count]["delta_corrs"].push_back(calc_delta_corr(matrix, row, col, species[s]));
			}
		}
	}
	cout << "end of function" << endl;
	return;

}

vector< vector<int> > metropolis(vector< vector<int> > & matrix, const vector<double> & ECI_vec, const double & T)
{

	//boltzmann constant = k
	double k = 8.62e-5;

	//calculates initial energy
	double init_energy = dot(calc_corr(matrix), ECI_vec);

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
		}
	}
	//print out new energy
	//should always be <= to total_energy printed out in main
	cout << "The new energy of the system is: " << init_energy << endl;

	return matrix;
}
