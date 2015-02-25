import numpy as np
from math import *
import subprocess
#move to separate file and import inverse_clex
#make contour plot using matplotlib
def ln_Ps(site, ECI_vec, beta):
	P = 0
	val = [-beta*np.dot(np.array(delta_corr_vec), ECI_vec) for delta_corr_vec in site["delta_corrs"]]
	m = max(val)
	for v in val:
		P += exp(v - m)
	return m + log(P)

#function to calculate ln_Q
#I put 'f' in front of the variable names to not confuse it with the variables outside of the function
def calc_ln_Q (f_ECI_vec, f_mc_partial_data_list, known_sites_list):
	#set up needed variables
	f_mc_full_data_list = []
	delta_corr_count = 0
	f_ln_Q = 0

	#fill in missing atoms in partial mc_data files
	for f_partial_mc_data in f_mc_partial_data_list:
		#call unknown_mc function with f_partial_mc_data as input to fill in matrix
			#create a json file with known_sites, dimension, temp, eci, species, passes
		subprocess.call(['unknown_monte_carlo'])
		#read mc_data
		json_mc_full_data = open("monte_carlo_calcs.json").read()
		mc_full_data = json.loads(json_mc_full_data)
		f_mc_full_data_list.append(mc_full_data)

	#loop to do for data at three temperatures
	for f_mc_data in f_mc_full_data_list:
		for data_set in f_mc_data:
			temp = data_set["Temp"] #set temp to "temp" in data set
			beta = 1/(temp*8.62*10**-5)
			#Q is the probablity we see the matrix we found. To avoid multiplying all the P's together, we can say lnQ = ln(sum of P's)
			pass_info = data_set["Data_by_pass"]
			for iteration in pass_info:
				for site in iteration["sites"]:
					f_ln_Q += ln_Ps(site, f_ECI_vec, beta)
	# print f_ln_Q, f_ECI_vec
	# return f_ln_Q