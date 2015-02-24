#include <iostream>
#include <vector>
#include <cstdlib>
#include <math.h>
#include "../external/jsonParser/jsonParser.hh"
#include "../h/clex.h"

using namespace std;

//declaring functions
vector< vector<int> > fill_in_matrix(vector< vector<int> > & known_sites, vector<int> & dim_size);


main()
{
	//take in known x,y,and species

	//fill in matrix
	vector< vector<int> > filled_matrix = fill_in_matrix(known_sites, dm_size);

	//based on an estimated eci (?) run montecarlo, only flipping unknown site

	//run optimization 
}

//function that fills in unfixed atoms
vector< vector<int> > fill_in_matrix(vector< vector<int> > & known_sites, vector<int> & dim_size)
{
	//generates a random matrix filling in with 1 and -1 at random
	filled_matrix = generate_matrix(dim_size[0], dim_size[1]);
	
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