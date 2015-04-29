#!/usr/bin/env python 

import json
#importing scipy
import numpy as np
from scipy.optimize import minimize
from math import *
from lnQ import calc_ln_Q
import sys
import os

#print "here1"

ECI_vec_key = [[1,0,0], [-1,0,0], [.3,-.7,.05]]
transition_temp_key = 30000
temp_mult_key = [.001, .01, .1, .2, .5, .9, 1, 1.1, 1.5, 10, 100, 1000]
temp_vec_key = [transition_temp_key*multiple for multiple in temp_mult_key]
num_passes_key = 100000
dim_small_vec_key = [10, 20, 50]
dim_large_vec_key = [100, 1000]
species_key = [1, -1]

mc_data_list = []

#read in from the arguments
#for filename in str(sys.argv):
#	filename_subset = filename.split("_")
#	size = filename_subset[0]
#	ECI_index = filename_subset[1]
#	dim_index = filename_subset[2]
#	temp_index = filename_subset[3]
#	num_passes = 100

from decimal import *

file_list = []

print sys.argv
for filename in sys.argv[1:]:
	parent = os.getcwd()
	print "filename",  filename
	os.chdir(filename)

    filename_subset = filename.split("_")
    #print filename_subset
    size = filename_subset[0]
    ECI_index = int(filename_subset[1])
    dim_index = int(filename_subset[2])
    temp_index = int(filename_subset[3])

	json_mc_data = open("monte_carlo_calcs.json").read()
	mc_data = json.loads(json_mc_data)
	os.chdir(parent)
	mc_data_list.append(mc_data)
	file_list.append(filename)

# mc_data = [mc_data]
one_ECI = 1
two_ECI = 0
three_ECI = 0
ECI_vec = [one_ECI, two_ECI, three_ECI]

ln_Q = calc_ln_Q(ECI_vec, mc_data)
#print "ln(Q) = ", ln_Q
optimization_NM = minimize(calc_ln_Q, ECI_vec, method='nelder-mead', args=(mc_data_list,), options={'xtol': 1e-8})
# should calculate derivative and pass in using jas = "derivative" property
#right now it calculates derivative using first differences approximation
# optimization_BFGS = minimize(calc_ln_Q, ECI_vec, method='BFGS', args=(mc_data,))

#prints original ECI vector
#print "ECI vector = ", ECI_vec[0], ECI_vec[1], ECI_vec[2]

#display returned optimization stats
print "Nelder-Mead Approximation: ", optimization_NM
print "optimization_NM.get('x'): ", optimization_NM.get('x')
# print "Broyden-Fletcher-Goldfarb-Shanno Approximation: ", optimization_BFGS
#append this to a json file "optimization_results.json" (ECI value, file names aka conditions, calculate difference squared of known ECI and write to json)
print "ECI_vec_key: ", ECI_vec_key[ECI_index]
ECI_diff_squared = (ECI_vec_key[ECI_index][0] - optimization_NM.get('x')[0])**2 + (ECI_vec_key[ECI_index][1] - optimization_NM.get('x')[1])**2 + (ECI_vec_key[ECI_index][2] - optimization_NM.get('x')[2])**2
#prints an "optimization_results.json" file in each folder. contains (Actual ECI, Approximated ECI, file names aka conditions, difference squared of known ECI)
with open("optimization_results.json", "w") as outfile:
	json.dump({'ECI_calculation': {'ECI': ECI_vec_key[ECI_index], 'Filenames': file_list, 'Aprroximated_ECI': optimization_NM, 'ECI_sum_diff_squared': ECI_diff_squared}}, outfile)


