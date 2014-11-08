#ifndef CLEX_H
#define CLEX_H

vector<double> create_ECI_vec (const double & ECI_1, const double & ECI_2, const double & ECI_3);
vector< vector<int> > generate_matrix(const int & row, const int & col);
vector<double> calc_corr(const vector< vector<int> > & matrix);
double calc_corr_1NN(const vector< vector<int> > & matrix);
double calc_corr_2NN(const vector< vector<int> > & matrix);
double calc_corr_3NN(const vector< vector<int> > & matrix);
vector<double> calc_delta_corr(const vector< vector<int> > & matrix , const int & row, const int & col, const int & end_atom);
double calc_delta_corr_1NN(const vector< vector<int> > & matrix, const int & row, const int & col, const int & end_atom);
double calc_delta_corr_2NN(const vector< vector<int> > & matrix, const int & row, const int & col, const int & end_atom);
double calc_delta_corr_3NN(const vector< vector<int> > & matrix, const int & row, const int & col, const int & end_atom);
double dot(const vector<double> & vector1, const vector<double> & vector2);
template<class T>
void print_matrix (const vector< vector<T> > & matrix);

#endif