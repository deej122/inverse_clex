#include <iostream>
#include <vector>
#include <cstdlib>
#include <math.h>
#include "../external/jsonParser/jsonParser.hh"
#include "../h/clex.h"
#include "../h/metropolis.h"

// comment
using namespace std;

//declare procedures
void check_create_ECI_vec(jsonParser & inputs, jsonParser & output_key);
void check_calc_corr(jsonParser & inputs, jsonParser & output_key);
void check_calc_corr_1NN(jsonParser & inputs, jsonParser & output_key);
void check_calc_corr_2NN(jsonParser & inputs, jsonParser & output_key);
void check_calc_corr_3NN(jsonParser & inputs, jsonParser & output_key);
void check_calc_delta_corr(jsonParser & inputs, jsonParser & output_key);
void check_calc_delta_corr_1NN(jsonParser & inputs, jsonParser & output_key);
void check_calc_delta_corr_2NN(jsonParser & inputs, jsonParser & output_key);
void check_calc_delta_corr_3NN(jsonParser & inputs, jsonParser & output_key);
void check_dot(jsonParser & inputs, jsonParser & output_key);


int main()
{
	//test all testable functions in clex.cpp
	jsonParser clex_test_inputs_in;
	clex_test_inputs_in.read(std::string("clex_test_inputs.json"));
	jsonParser clex_test_outputs_in;
	clex_test_outputs_in.read(std::string("clex_test_outputs_key.json"));

	char repeat_YN = 'Y';
	int menu_input;

	for (repeat_YN == 'Y' or repeat_YN == 'y')
	{
		cout << "Menu:" << endl
			 << "To test creat_ECI_vec function enter 1." << endl
			 << "To test calc_corr function enter 2." << endl
			 << "To test calc_corr_1NN function enter 3." << endl
			 << "To test calc_corr_2NN function enter 4." << endl
			 << "To test calc_corr_3NN function enter 5." << endl
			 << "To test calc_delta_corr function enter 6." << endl
			 << "To test calc_delta_corr_1NN function enter 7." << endl
			 << "To test calc_delta_corr_2NN function enter 8." << endl
			 << "To test calc_delta_corr_3NN function enter 9." << endl
			 << "To test dot function enter 10." << endl
			 << "To test all functions listed enter 11." << endl;

		cin >> menu_input;

		switch(menu_input)
		{
			case 1: check_create_ECI_vec(clex_test_inputs_in, clex_test_outputs_in);
					break;
			case 2: check_calc_corr(clex_test_inputs_in, clex_test_outputs_in);
					break;
			case 3:	check_calc_corr_1NN(clex_test_inputs_in, clex_test_outputs_in);
					break;
			case 4: check_calc_corr_2NN(clex_test_inputs_in, clex_test_outputs_in);
					break;
			case 5:	check_calc_corr_3NN(clex_test_inputs_in, clex_test_outputs_in);
					break;
			case 6:	check_calc_delta_corr(clex_test_inputs_in, clex_test_outputs_in);
					break;
			case 7:	check_calc_delta_corr_1NN(clex_test_inputs_in, clex_test_outputs_in);
					break;
			case 8: check_calc_delta_corr_2NN(clex_test_inputs_in, clex_test_outputs_in);
					break;
			case 9:	check_calc_delta_corr_3NN(clex_test_inputs_in, clex_test_outputs_in);
					break;
			case 10:check_dot(clex_test_inputs_in, clex_test_outputs_in);
					break;
			case 11:check_create_ECI_vec(clex_test_inputs_in, clex_test_outputs_in);
					check_calc_corr(clex_test_inputs_in, clex_test_outputs_in);
					check_calc_corr_1NN(clex_test_inputs_in, clex_test_outputs_in);
					check_calc_corr_2NN(clex_test_inputs_in, clex_test_outputs_in);
					check_calc_corr_3NN(clex_test_inputs_in, clex_test_outputs_in);
					check_calc_delta_corr(clex_test_inputs_in, clex_test_outputs_in);
					check_calc_delta_corr_1NN(clex_test_inputs_in, clex_test_outputs_in);
					check_calc_delta_corr_2NN(clex_test_inputs_in, clex_test_outputs_in);
					check_calc_delta_corr_3NN(clex_test_inputs_in, clex_test_outputs_in);
					check_dot(clex_test_inputs_in, clex_test_outputs_in);
					break;
		}

		cout << "Unit test is complete" << endl
			 << "Would you like to run another test? (Y/N)" << endl;
		cin << menu_input;
	}
	
	return 0;
}

//procedure to check the create_ECI_vec 
void check_create_ECI_vec(jsonParser & inputs, jsonParser & output_key)
{
	int pass_counter=0;
	for (int num_tests=0; num_tests < inputs["create_ECI_vec_inputs"].size(); num_tests++)
	{
		vector<double> test_ECI_vec = create_ECI_vec(inputs["create_ECI_vec_inputs"][num_tests][0], inputs["create_ECI_vec_inputs"][num_tests][1], inputs["create_ECI_vec"][num_tests][2]);
		if ( test_ECI_vec == output_key["create_ECI_vec_outputs"][num_tests])
		{
			pass_counter++;
		}
		else
		{
			cout << "Failed create_ECI_vec function on input number " << num_tests << endl;
				 << "current output is: [ " << test_ECI_vec[0] << ", " << test_ECI_vec[1] << ", " << test_ECI_vec[2] << " ]" << endl;
		}
		if (pass_counter == inputs["create_ECI_vec_inputs"].size())
		{
			cout << "Passed create_ECI_vec function!" << endl;
		}
	}
	return;
}

//procedure to check the calc_corr function
void check_calc_corr(jsonParser & inputs, jsonParser & output_key)
{
	int pass_counter=0;
	for (int num_tests=0; num_tests < inputs["calc_corr_inputs"].size(); num_tests++)
	{
		vector<double> test_calc_corr = calc_corr(inputs["calc_corr_inputs"][num_tests]);
		if ( test_calc_corr == output_key["calc_corr_outputs"][num_tests])
		{
			pass_counter++;
		}
		else
		{
			cout << "Failed calc_corr function on input number " << num_tests << endl
				 << "current output is: [ " << test_calc_corr[0] << ", " << test_calc_corr[1] << ", " << test_calc_corr[2] << ", " << endl; 
		}
		if (pass_counter == inputs["calc_corr_inputs"].size())
		{
			cout << "Passed calc_corr function!" << endl;
		}
	}
	return;
}

void check_calc_corr_1NN(jsonParser & inputs, jsonParser & output_key)
{
	int pass_counter=0;
	for(int num_tests=0; num_tests < inputs["calc_corr_1NN_inputs"].size(); num_tests++)
	{
		double test_calc_corr_1NN = calc_corr_1NN(inputs["calc_corr_1NN_inputs"][num_tests]);
		if(test_calc_corr_1NN == out_key["calc_corr_1NN_outputs"][num_tests])
		{
			pass_counter++;
		}
		else
		{
			cout << "Failed calc_corr_1NN function on input number " << num_tests << endl
				 << "current output is: " << test_calc_corr_1NN << endl;
		}
		if (pass_counter == inputs["calc_corr_1NN_inputs"].size())
		{
			cout << "Passed calc_corr_1NN function!" << endl;
		}
	}
	return;
}

void check_calc_corr_2NN(jsonParser & inputs, jsonParser & output_key)
{
	int pass_counter=0;
	for(int num_tests=0; num_tests < inputs["calc_corr_2NN_inputs"].size(); num_tests++)
	{
		double test_calc_corr_2NN = calc_corr_2NN(inputs["calc_corr_2NN_inputs"][num_tests]);
		if(test_calc_corr_2NN == out_key["calc_corr_2NN_outputs"][num_tests])
		{
			pass_counter++;
		}
		else
		{
			cout << "Failed calc_corr_2NN function on input number " << num_tests << endl
				 << "current output is: " << test_calc_corr_2NN << endl;
		}
		if (pass_counter == inputs["calc_corr_2NN_inputs"].size())
		{
			cout << "Passed calc_corr_2NN function!" << endl;
		}
	}
	return;
}

void check_calc_corr_3NN(jsonParser & inputs, jsonParser & output_key)
{
	int pass_counter=0;
	for(int num_tests=0; num_tests < inputs["calc_corr_3NN_inputs"].size(); num_tests++)
	{
		double test_calc_corr_3NN = calc_corr_2NN(inputs["calc_corr_3NN_inputs"][num_tests]);
		if(test_calc_corr_3NN == out_key["calc_corr_3NN_outputs"][num_tests])
		{
			pass_counter++;
		}
		else
		{
			cout << "Failed calc_corr_3NN function on input number " << num_tests << endl
				 << "current output is: " << test_calc_corr_3NN << endl;
		}
		if (pass_counter == inputs["calc_corr_3NN_inputs"].size())
		{
			cout << "Passed calc_corr_3NN function!" << endl;
		}
	}
	return;
}


void check_calc_delta_corr(jsonParser & inputs, jsonParser & output_key)
{
	int pass_counter=0;
	for (int num_tests=0; num_tests < inputs["calc_delta_corr_inputs"].size(); num_tests++)
	{
		vector<double> test_calc_delta_corr = calc_delta_corr(inputs["calc_delta_corr_inputs"][num_tests][0], inputs["calc_delta_corr_inputs"][num_tests][1], inputs["calc_delta_corr_inputs"][num_tests][2], inputs["calc_delta_corr_inputs"][num_tests][3]);
		if ( test_calc_delta_corr == output_key["calc_delta_corr_outputs"][num_tests])
		{
			pass_counter++;
		}
		else
		{
			cout << "Failed calc_delta_corr function on input number " << num_tests << endl
				 << "current output is: [ " << test_calc_delta_corr[0] << ", " << test_calc_delta_corr[1] << ", " << test_calc_delta_corr[2] << ", " << endl; 
		}
		if (pass_counter == inputs["calc_delta_corr_inputs"].size())
		{
			cout << "Passed calc_delta_corr function!" << endl;
		}
	}
	return;
}

void check_calc_delta_corr_1NN(jsonParser & inputs, jsonParser & output_key)
{
	int pass_counter=0;
	for(int num_tests=0; num_tests < inputs["calc_delta_corr_1NN_inputs"].size(); num_tests++)
	{
		double test_calc_delta_corr_1NN = calc_delta_corr_1NN(inputs["calc_corr_1NN_inputs"][num_tests][0], inputs["calc_corr_1NN_inputs"][num_tests][1], inputs["calc_corr_1NN_inputs"][num_tests][2], inputs["calc_corr_1NN_inputs"][num_tests][3]);
		if(test_calc_delta_corr_1NN == out_key["calc_delta_corr_1NN_outputs"][num_tests])
		{
			pass_counter++;
		}
		else
		{
			cout << "Failed calc_delta_corr_1NN function on input number " << num_tests << endl
				 << "current output is: " << test_calc_delta_corr_1NN << endl;
		}
		if (pass_counter == inputs["calc_delta_corr_1NN_inputs"].size())
		{
			cout << "Passed calc_delta_corr_1NN function!" << endl;
		}
	}
	return;
}

void check_calc_delta_corr_2NN(jsonParser & inputs, jsonParser & output_key)
{
	int pass_counter=0;
	for(int num_tests=0; num_tests < inputs["calc_delta_corr_2NN_inputs"].size(); num_tests++)
	{
		double test_calc_delta_corr_2NN = calc_delta_corr_1NN(inputs["calc_corr_2NN_inputs"][num_tests][0], inputs["calc_corr_2NN_inputs"][num_tests][1], inputs["calc_corr_2NN_inputs"][num_tests][2], inputs["calc_corr_2NN_inputs"][num_tests][3]);
		if(test_calc_delta_corr_2NN == out_key["calc_delta_corr_2NN_outputs"][num_tests])
		{
			pass_counter++;
		}
		else
		{
			cout << "Failed calc_delta_corr_2NN function on input number " << num_tests << endl
				 << "current output is: " << test_calc_delta_corr_1NN << endl;
		}
		if (pass_counter == inputs["calc_delta_corr_2NN_inputs"].size())
		{
			cout << "Passed calc_delta_corr_2NN function!" << endl;
		}
	}
	return;
}

void check_calc_delta_corr_2NN(jsonParser & inputs, jsonParser & output_key)
{
	int pass_counter=0;
	for(int num_tests=0; num_tests < inputs["calc_delta_corr_2NN_inputs"].size(); num_tests++)
	{
		double test_calc_delta_corr_2NN = calc_delta_corr_2NN(inputs["calc_corr_2NN_inputs"][num_tests][0], inputs["calc_corr_2NN_inputs"][num_tests][1], inputs["calc_corr_2NN_inputs"][num_tests][2], inputs["calc_corr_2NN_inputs"][num_tests][3]);
		if(test_calc_delta_corr_2NN == out_key["calc_delta_corr_2NN_outputs"][num_tests])
		{
			pass_counter++;
		}
		else
		{
			cout << "Failed calc_delta_corr_2NN function on input number " << num_tests << endl
				 << "current output is: " << test_calc_delta_corr_2NN << endl;
		}
		if (pass_counter == inputs["calc_delta_corr_2NN_inputs"].size())
		{
			cout << "Passed calc_delta_corr_2NN function!" << endl;
		}
	}
	return;
}

void check_calc_delta_corr_3NN(jsonParser & inputs, jsonParser & output_key)
{
	int pass_counter=0;
	for(int num_tests=0; num_tests < inputs["calc_delta_corr_3NN_inputs"].size(); num_tests++)
	{
		double test_calc_delta_corr_3NN = calc_delta_corr_3NN(inputs["calc_corr_3NN_inputs"][num_tests][0], inputs["calc_corr_3NN_inputs"][num_tests][1], inputs["calc_corr_3NN_inputs"][num_tests][2], inputs["calc_corr_3NN_inputs"][num_tests][3]);
		if(test_calc_delta_corr_3NN == out_key["calc_delta_corr_3NN_outputs"][num_tests])
		{
			pass_counter++;
		}
		else
		{
			cout << "Failed calc_delta_corr_3NN function on input number " << num_tests << endl
				 << "current output is: " << test_calc_delta_corr_3NN << endl;
		}
		if (pass_counter == inputs["calc_delta_corr_3NN_inputs"].size())
		{
			cout << "Passed calc_delta_corr_3NN function!" << endl;
		}
	}
	return;
}

void check_dot(jsonParser & inputs, jsonParser & output_key)
{
	int pass_counter=0;
	for(int num_tests=0; num_tests < inputs["dot_inputs"].size(); num_tests++)
	{
		double test_dot = dot(inputs["dot_inputs"][num_tests][0], inputs["dot_inputs"][num_tests][1]);
		if(test_dot == out_key["dot_outputs"][num_tests])
		{
			pass_counter++;
		}
		else
		{
			cout << "Failed dot function on input number " << num_tests << endl
				 << "current output is: " << test_dot << endl;
		}
		if (pass_counter == inputs["dot_inputs"].size())
		{
			cout << "Passed dot function!" << endl;
		}
	}
	return;
}