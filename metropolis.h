#ifndef METROPOLIS_H
#define METROPOLIS_H

void read_json_in (double & temp, vector<int> & dim, vector<double> & species, vector<double> & ECI_vec, int & num_passes);
void write_json_out (const vector<double> ECI_vec, const vector< vector<int> > & matrix, jsonParser & json_out, const int & pass_count, const vector<double> & species);
vector< vector<int> > metropolis(vector< vector<int> > & matrix, const vector<double> & ECI_vec, const double & T);

#endif