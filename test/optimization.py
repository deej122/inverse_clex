import json
import math
#importing scipy
import numpy as np
from scipy.optimize import minimize


from decimal import *
json_mc_data = open("monte_carlo_calcs.json").read()
mc_data = json.loads(json_mc_data)

one_ECI = 1
two_ECI = 0
three_ECI = 0
ECI_vec = [one_ECI, two_ECI, three_ECI]

#function to calculate ln_Q
#I put 'f' in front of the variable names to not confuse it with the variables outside of the function
def calc_ln_Q (f_ECI_vec):
	"Calculates ln(Q)"

	#set mc_data in function rather than taking input
	f_mc_data = mc_data

	#set up needed variables
	delta_corr_count = 0
	site_count = 0
	#dot_product will be dotting the delta_corr vec and the ECI_vec
	dot_product = 0
	temp = f_mc_data["Temp"]
	beta = 1/(temp*8.62*10**-5)
	#summation is the sum of the exp(-beta*dot_product) for add different atoms of one site
	summation = 0
	#P is the probability of the atom ending up as the atom we saw, P=1/summation
	P = 0
	#Q is the probablity we see the matrix we found. To avoid multiplying all the P's together, we can say lnQ = ln(sum of P's)
	f_ln_Q = 0
	e = 2.71821
	last_pass_info = f_mc_data["Data_by_pass"][len(f_mc_data["Data_by_pass"])-1]

	#this loop finds the information for the matrix after the last pass
	for site in last_pass_info["sites"]:
		#get index of site_count item
		site_count = last_pass_info["sites"].index(site)
		#reset summation to 0 after each site
		summation = 0
		#this loop iterates over the delta_corr vecs for a single site
		#this only works for two species matrixes
		for delta_corr_count in range (0, 1):
			delta_corr_count = int(delta_corr_count)
			delta_corr_vec = last_pass_info["sites"][site_count]["delta_corrs"][delta_corr_count]
			for a in delta_corr_vec:
				#get index of a
				i = delta_corr_vec.index(a)
				dot_product += delta_corr_vec[i]*f_ECI_vec[i]
		f_ln_Q += (dot_product*beta)

	return f_ln_Q

# ln_Q = calc_ln_Q(ECI_vec, mc_data)
ln_Q = calc_ln_Q(ECI_vec)
print "ln(Q) = ", ln_Q
# optimization = minimize(calc_ln_Q, ECI_vec, method='nelder-mead', args=(mc_data))
optimization = minimize(calc_ln_Q, ECI_vec, method='nelder-mead')
#prints original ECI vector
print "ECI vector = ", ECI_vec[0], ECI_vec[1], ECI_vec[2]
#display returned optimization stats
#this is a MAXIMIZATION of ln_Q. We want this to be a minimization. So should we change line 58 to return 1/f_ln_Q ?
print optimization
#x = new ECI_vector?