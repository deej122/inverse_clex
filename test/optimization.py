import json
#importing scipy
import numpy as np
from scipy.optimize import minimize
from math import *
from lnQ import calc_ln_Q
import sys

ECI_vec_key = [[1,0,0], [-1,0,0], [.3,-.7,.05]]
transition_temp_key = 30000
temp_mult_key = [.001, .01, .1, .2, .5, .9, 1, 1.1, 1.5, 10, 100, 1000]
temp_vec_key = [transition_temp*multiple for multiple in temp_mult]
num_passes_key = 100000
dim_small_vec_key = [10, 20, 50]
dim_large_vec_key = [100, 1000]
species_key = [1, -1]

#read in from the arguments
for filename in str(sys.argv):
	filename.split("_")
	size = filename[1]
	ECI_index = filename[2]
	dim_index = filename[3]
	temp_index = filename[4]
	num_passes = 100

from decimal import *
json_mc_data = open("monte_carlo_calcs.json").read()
mc_data = json.loads(json_mc_data)

mc_data = [mc_data]
one_ECI = 1
two_ECI = 0
three_ECI = 0
ECI_vec = [one_ECI, two_ECI, three_ECI]

ln_Q = calc_ln_Q(ECI_vec, mc_data)
print "ln(Q) = ", ln_Q
optimization_NM = minimize(calc_ln_Q, ECI_vec, method='nelder-mead', args=(mc_data,), options={'xtol': 1e-8})
# should calculate derivative and pass in using jas = "derivative" property
#right now it calculates derivative using first differences approximation
# optimization_BFGS = minimize(calc_ln_Q, ECI_vec, method='BFGS', args=(mc_data,))

#prints original ECI vector
print "ECI vector = ", ECI_vec[0], ECI_vec[1], ECI_vec[2]

#display returned optimization stats
print "Nelder-Mead Approximation: ", optimization_NM
# print "Broyden-Fletcher-Goldfarb-Shanno Approximation: ", optimization_BFGS