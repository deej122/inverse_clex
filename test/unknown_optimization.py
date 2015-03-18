import json
#importing scipy
import numpy as np
from scipy.optimize import minimize
from math import *
from decimal import *
import random
from unknown_lnQ import calc_ln_Q
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

#subset of known atoms for each snapshot
# known_sites_subset = []
#list of all subsets of known atoms (passed into calc_lnQ optimization)
# known_sites_list = []

mc_partial_data_list = []

# #read in from the arguments
# for filename in str(sys.argv):
	# filename.split("_")
	# size = filename[1]
	# ECI_index = filename[2]
	# dim_index = filename[3]
	# temp_index = filename[4]
	# num_passes = 100

for filename in str(sys.argv):
	filename.split("_")
	size = filename[1]
	ECI_index = filename[2]
	dim_index = filename[3]
	temp_index = filename[4]

	parent = os.getcwd()
	os.chdir(filename)
	#create dict consisting of a list of files
	file_name = filename
	_file = {file_name:[]}

	file_info = {}
	if size == "large":
		file_info["Dimension"] = dim_large_vec_key[dim_index]
	else if size == "small":
		file_info["Dimension"] = dim_small_vec_key[dim_index]
	file_info["Temperature"] = temp_vec_key[temp_index]
	file_info["ECI"] = ECI_vec_key[ECI_index]

	#create a constructor that, given a set of files, outputs a json object (conditions.json stuff from lnQ) for an [i][j] corresponding to [file][pass]
		#would be a lot easier to use and understand
		#run some tests and make sure this works well first

	json_mc_data = open("monte_carlo_calcs.json").read()
	mc_data = json.loads(json_mc_data)
	for _pass in mc_data["Data_by_pass"]:
		#create dict consisting of list of passes
		index = _pass["pass"]
		current_pass = {index:[]}
		#for each site in every object
		for atom in _pass["sites"]
			#generate random number
			random = random.random()
			#add ~known_percent of atoms to known subset for this snapshot
			if random < percent_known:
				#MAKE THIS AND THEN NO NEED TO PASS KNOWN_SITES_LIST
				#mc_partial_data_list is a list of files > list of passes > list of known atoms (coordinates and current occupant)
				#create object of known_atom and add it to list for this pass
				known_atom = {"coordinate": atom["coordinate"], "current_occupant": atom["current_occupant"]}
				current_pass[index].append(known_atom)
			#otherwise ignore the atom
			else:
				current_pass = current_pass
		#add pass to list in this file
		file_info["Known_Sites"] = []
		file_info["Known_Sites"].append(current_pass)

		_file[file_name].append(file_info)
	os.chdir(parent)

	#add completed list of known items in each pass within a file, to a list of all
	mc_partial_data_list.append(_file)


#take percent (m) of known atoms as input
#open json files
#create a vector of known sites including x, y, species information (known_sites_list)
##For every atom in each snapshot:
###choose a random number between 0 and 1. If number < m, add atom to vector of known sites. Else, ignore it.

# #for every file that we appended
# for data in mc_partial_data_list:
# 	#for every object in the data_by_pass list
# 	for _pass in data:
# 		#for each site in every object
# 		for atom in _pass.sites
# 			#generate random number
# 			random = random.random()
# 			#add ~known_percent of atoms to known subset for this snapshot
# 			if random < percent_known:
# 				known_sites_subset.append(atom)
# 			#otherwise ignore the atom
# 			else:
# 				known_sites_subset = known_sites_subset
		#add the known atoms list for each snapshot to the overall known atoms list which is passed into calc_lnQ
		# known_sites_list.append(known_sites_subset)

# mc_data = [mc_data]
one_ECI = 1
two_ECI = 0
three_ECI = 0
ECI_vec = [one_ECI, two_ECI, three_ECI]

ln_Q = calc_ln_Q(ECI_vec, mc_data)
print "ln(Q) = ", ln_Q
optimization_NM = minimize(calc_ln_Q, ECI_vec, method='nelder-mead', args=(mc_partial_data_list), options={'xtol': 1e-8})
# should calculate derivative and pass in using jas = "derivative" property
#right now it calculates derivative using first differences approximation
# optimization_BFGS = minimize(calc_ln_Q, ECI_vec, method='BFGS', args=(mc_data,))

#prints original ECI vector
print "ECI vector = ", ECI_vec[0], ECI_vec[1], ECI_vec[2]

#display returned optimization stats
print "Nelder-Mead Approximation: ", optimization_NM
# print "Broyden-Fletcher-Goldfarb-Shanno Approximation: ", optimization_BFGS