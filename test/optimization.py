import json
import math
#importing scipy
import numpy
from scipy.optimize import minimize


from decimal import *
json_mc_data = open("monte_carlo_calcs.json").read()
mc_data = json.loads(json_mc_data)

one_ECI = 1
two_ECI = 1
three_ECI = 1
ECI_vec = [one_ECI, two_ECI, three_ECI]

temp = mc_data["Temp"]
delta_corr_count = 0
site_count = 0
sum_delta_corr = 0
#dot_product will be dotting the delta_corr vec and the ECI_vec
dot_product = 0
beta = 1/(temp*8.62*10**-5)
#summation is the sum of the exp(-beta*dot_product) for add different atoms of one site
summation = 0
#P is the probability of the atom ending up as the atom we saw, P=1/summation
P = 0
#Q is the probablity we see the matrix we found. To avoid multiplying all the P's together, we can say lnQ = ln(sum of P's)
ln_Q = 0
e = 2.71821

#this for loop finds the information for the matrix after the last pass
for site_count in mc_data["Data_by_pass"][len(mc_data["Data_by_pass"])-1]["sites"]:
	#summation needs to be reset to 0 after each site
	summation = 0 
	#this for loop iterates over the delta_corr vecs
	for delta_corr_count in mc_data["Data_by_pass"][len(mc_data["Data_by_pass"])-1]["sites"][site_count]["delta_corrs"]:
		delta_corr_vec = mc_data["Data_by_pass"][len(mc_data["Data_by_pass"])-1]["sites"][site_count]["delta_corrs"][delta_corr_count]
		#dot product of delta_corr and ECI_vec
		for a in range (0, len(delta_corr_vec)-1):
			dot_product += delta_corr_vec[a]*ECI_vec[a]
			#Where do we do this minimization? Because ECI_vec is our variable and has to be one of the inputs.
			result = minimize(dot_product, ECI_vec, method="nelder-mead")
		#This causes an overflow error
		summation += e**(dot_product*beta*-1)
		P = 1/summation
	ln_Q += P

print "P = ", P