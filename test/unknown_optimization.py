import json
#importing scipy
import numpy as np
from scipy.optimize import minimize
from math import *
from decimal import *
import random
from unknown_lnQ import calc_ln_Q
import unknown_monte_carlo
import sys
import os

ECI_vec_key = [[1,0,0], [-1,0,0], [.3,-.7,.05]]
transition_temp_key = 30000
temp_mult_key = [.001, .01, .1, .2, .5, .9, 1, 1.1, 1.5, 10, 100, 1000]
temp_vec_key = [transition_temp*multiple for multiple in temp_mult]
num_passes_key = 100000
dim_small_vec_key = [10, 20, 50]
dim_large_vec_key = [100, 1000]
species_key = [1, -1]
percent_known = 0.80
mc_passes = 10 #use this in calc_lnQ when creating conditions.json

mc_partial_data_list = []

#document file structure needed for this to work
for filename in str(sys.argv):
	split_filename = filename.split("_")
	size = split_filename[0]
	ECI_index = split_filename[1]
	dim_index = split_filename[2]
	temp_index = split_filename[3]

	parent = os.getcwd()
	os.chdir(filename)

	#create dict consisting of a list of files
	file_name = filename

	file_info = {}
	if size == "large":
		file_info["Dimension"] = dim_large_vec_key[dim_index]
	else if size == "small":
		file_info["Dimension"] = dim_small_vec_key[dim_index]
	file_info["Temperature"] = temp_vec_key[temp_index]
	file_info["ECI"] = ECI_vec_key[ECI_index]
	file_info["Sampling_Passes"] = mc_passes
	file_info["Equilibriation_Passes"] = 10000
	file_info["Sampling_Increment"] = 100

	_file = create_mc_partial_data(file_name, file_info, percent_known)
	#add completed list of known items in each pass within a file, to a list of all
	mc_partial_data_list.append(_file)
	os.chdir(parent)

#create full mc_files for passing into 
mc_full_data_list = create_complete_mc(mc_partial_data_list)

one_ECI = 1
two_ECI = 0
three_ECI = 0
ECI_vec = [one_ECI, two_ECI, three_ECI]

ln_Q = calc_ln_Q(ECI_vec, mc_data)

optimization_NM = minimize(calc_ln_Q, ECI_vec, method='nelder-mead', args=(mc_full_data_list), options={'xtol': 1e-8})
# should calculate derivative and pass in using jas = "derivative" property
#right now it calculates derivative using first differences approximation
# optimization_BFGS = minimize(calc_ln_Q, ECI_vec, method='BFGS', args=(mc_data,))

#prints original ECI vector
print "ECI vector = ", ECI_vec[0], ECI_vec[1], ECI_vec[2]

#display returned optimization stats
print "Nelder-Mead Approximation: ", optimization_NM
# print "Broyden-Fletcher-Goldfarb-Shanno Approximation: ", optimization_BFGS