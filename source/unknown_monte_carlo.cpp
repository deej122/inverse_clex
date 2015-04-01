#include <iostream>
#include <vector>
#include <cstdlib>
#include <math.h>
#include "../external/jsonParser/jsonParser.hh"
#include "../h/clex.h"
#include "../h/metropolis.h"


using namespace std;

//declaring functions
vector< vector<int> > fill_in_matrix(vector< vector<int> > & known_sites, vector<int> & dim_size);
vector< vector<int> > unknown_metropolis(vector< vector<int> > & matrix, const vector<double> & ECI_vec, const double & T, vector< vector<int> > unknown_sites);


int main()
{
	//declaring variables
	vector< vector<int> > known_sites;
	vector<int> dim_size;
	double temp;
	vector<double> ECI_vec;
	vector<double> species;
	int equilibriation_passes;
	int num_passes;
	int sampling_increment;

	//create output json file
	jsonParser json_out;

	//take in known conditions from json file known_species_conditions.json
	jsonParser known_species_in;
	known_species_in.read(std::string("known_species_conditions.json"));
	known_sites = known_species_in["Known_Species"].get< vector< vector<int> > >();
	dim_size = known_species_in["Dimensions"].get< vector<int> >();
	temp = known_species_in["Temp"].get<double>();
	ECI_vec = known_species_in["ECI"].get< vector<double> >();
	species = known_species_in["Species"].get< vector<double> >();
	num_passes = known_species_in["Sampling_Passes"].get<int>();
	equilibriation_passes = known_species_in["Equilibriation_Passes"].get<int>();
	sampling_increment = known_species_in["Sampling_Increment"].get<int>();

	//create a unknown_sites vector of vectors containing the coordinates of unknown sites
	vector< vector<int> > unknown_sites;
	vector<int>temporary_row (dim_size[0], 0);
	vector< vector<int> > binary_matrix (dim_size[1], temporary_row);
	for(int count = 0; count < known_sites.size(); count++)
	{
		binary_matrix[known_sites[count][0]][known_sites[count][1]] = 1;
	}
	vector<int> holder (2,0);
	for(int x=0; x<dim_size[0]; x++)
	{
		for(int y=0; y<dim_size[1]; y++)
		{
			if (binary_matrix[x][y] ==0)
			{
				holder[0]=x;
				holder[1]=y;
				// unknown_sites.append(holder);
				//is this doing the right thing?
				unknown_sites[x] = holder;
			}
		}
	}


	//fill in matrix
	vector< vector<int> > filled_matrix = fill_in_matrix(known_sites, dim_size);

	//based on an ECI from input run montecarlo, only flipping unknown site
	int pass_count = 0;
	write_json_out (ECI_vec, filled_matrix, json_out, pass_count, species);


	// allow the matrix to equilibriate. these passes are not considered when doing any calculations
	for(int equilibriate=0; equilibriate < equilibriation_passes; equilibriate++)
	{
		filled_matrix=unknown_metropolis(filled_matrix, ECI_vec, temp, unknown_sites);
	}

	//run for number of passes 
	for(pass_count=1; pass_count <= num_passes; pass_count++)
	{
		filled_matrix=unknown_metropolis(filled_matrix, ECI_vec, temp, unknown_sites);
		write_json_out (ECI_vec, filled_matrix, json_out, pass_count, species);
	}

	return 0;
}

//function that fills in unfixed atoms
vector< vector<int> > fill_in_matrix(vector< vector<int> > & known_sites, vector<int> & dim_size)
{
	//generates a random matrix filling in with 1 and -1 at random
	vector< vector<int> > filled_matrix = generate_matrix(dim_size[0], dim_size[1]);
	
	//changes the known sites
	for(int counter = 0; counter < known_sites.size(); counter++)
	{
		filled_matrix[known_sites[counter][0]][known_sites[counter][1]] = known_sites[counter][2];
	}

	return filled_matrix;
}

//metropolis function for partially unknown
vector< vector<int> > unknown_metropolis(vector< vector<int> > & matrix, const vector<double> & ECI_vec, const double & T, vector< vector<int> > unknown_sites)
{

	//boltzmann constant = k
	double k = 8.62e-5;

	//calculates initial energy
	double init_energy = dot(calc_corr(matrix), ECI_vec);

	//repeat as many times as there are atoms in the unit cell matrix
	for(int i = 0; i < matrix.size()*matrix[0].size(); i++)	
	{
		//generate random row, col from possible unkown sites
		int random_indice = rand() % unknown_sites.size();
		int row = unknown_sites[random_indice][0];
		int col = unknown_sites[random_indice][1];		
		//flip atom in matrix row/col 
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
	return matrix;
}