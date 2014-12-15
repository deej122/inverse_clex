import json
#importing scipy
import numpy as np
from scipy.optimize import minimize
from math import *


from decimal import *
# json_mc_data_10 = open("monte_carlo_calcs_10.json").read()
# json_mc_data_100 = open("monte_carlo_calcs_100.json").read()
json_mc_data_1000 = open("monte_carlo_calcs_1000.json").read()
json_mc_data_10000 = open("monte_carlo_calcs_10000.json").read()
json_mc_data_30000 = open("monte_carlo_calcs_30000.json").read()
json_mc_data_100000 = open("monte_carlo_calcs_100000.json").read()
json_mc_data_200000 = open("monte_carlo_calcs_200000.json").read()
json_mc_data_300000 = open("monte_carlo_calcs_300000.json").read()
#add temperatures > 30000K
# mc_data_10 = json.loads(json_mc_data_10)
# mc_data_100 = json.loads(json_mc_data_100)
mc_data_1000 = json.loads(json_mc_data_1000)
mc_data_10000 = json.loads(json_mc_data_10000)
mc_data_30000 = json.loads(json_mc_data_30000)
mc_data_100000 = json.loads(json_mc_data_100000)
mc_data_200000 = json.loads(json_mc_data_200000)
mc_data_300000 = json.loads(json_mc_data_300000)

mc_data = [mc_data_1000, mc_data_10000, mc_data_30000, mc_data_100000, mc_data_200000, mc_data_300000]

one_ECI = 0
two_ECI = 0
three_ECI = 0
ECI_vec = [one_ECI, two_ECI, three_ECI]

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
def calc_ln_Q (f_ECI_vec, f_mc_data):
	"Calculates ln(Q)"

	#set up needed variables
	delta_corr_count = 0
	f_ln_Q = 0
	#loop to do for data at three temperatures
	for data_set in f_mc_data:
		temp = data_set["Temp"] #set temp to "temp" in data set
		beta = 1/(temp*8.62*10**-5)
		#Q is the probablity we see the matrix we found. To avoid multiplying all the P's together, we can say lnQ = ln(sum of P's)
		pass_info = data_set["Data_by_pass"]
		for iteration in pass_info:
			for site in iteration["sites"]:
				f_ln_Q += ln_Ps(site, f_ECI_vec, beta)
	print f_ln_Q, f_ECI_vec
	return f_ln_Q

ln_Q = calc_ln_Q(ECI_vec, mc_data)
print "ln(Q) = ", ln_Q
optimization_NM = minimize(calc_ln_Q, ECI_vec, method='nelder-mead', args=(mc_data,))
# should calculate derivative and pass in using jas = "derivative" property
#right now it calculates derivative using first differences approximation
# optimization_BFGS = minimize(calc_ln_Q, ECI_vec, method='BFGS', args=(mc_data,))

#prints original ECI vector
print "ECI vector = ", ECI_vec[0], ECI_vec[1], ECI_vec[2]

#display returned optimization stats
print "Nelder-Mead Approximation: ", optimization_NM
# print "Broyden-Fletcher-Goldfarb-Shanno Approximation: ", optimization_BFGS