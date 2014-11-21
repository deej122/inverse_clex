import json
import math

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
dot_product = 0
beta = 1/(temp*8.62*10**-5)
summation = 0
P = 0
Q = 0
e = 2.71821


for site_count in range (0, len(mc_data["Data_by_pass"][len(mc_data["Data_by_pass"])-1]["sites"])-1):
	summation = 0 
	for delta_corr_count in range (0, len(mc_data["Data_by_pass"][len(mc_data["Data_by_pass"])-1]["sites"][site_count]["delta_corrs"])-1):
		delta_corr_vec = mc_data["Data_by_pass"][len(mc_data["Data_by_pass"])-1]["sites"][site_count]["delta_corrs"][delta_corr_count]
		#dot product of delta_corr and ECI_vec
		for a in range (0, len(delta_corr_vec)-1):
			dot_product += delta_corr_vec[a]*ECI_vec[a]
		summation += e**(dot_product*beta*-1)
		P = 1/summation
	Q += P

print "P = ", P