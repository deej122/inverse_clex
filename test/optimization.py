import json
#importing scipy
import numpy as np
from scipy.optimize import minimize
from math import *
from lnQ import calc_ln_Q


from decimal import *
# json_mc_data_10 = open("monte_carlo_calcs_10.json").read()
# json_mc_data_100 = open("monte_carlo_calcs_100.json").read()
# json_mc_data_1000 = open("monte_carlo_calcs_1000.json").read()
# json_mc_data_10000 = open("monte_carlo_calcs_10000.json").read()
json_mc_data_30000 = open("monte_carlo_calcs_30000.json").read()
# json_mc_data_100000 = open("monte_carlo_calcs_100000.json").read()
# json_mc_data_200000 = open("monte_carlo_calcs_200000.json").read()
# json_mc_data_300000 = open("monte_carlo_calcs_300000.json").read()
#add temperatures > 30000K
# mc_data_10 = json.loads(json_mc_data_10)
# mc_data_100 = json.loads(json_mc_data_100)
# mc_data_1000 = json.loads(json_mc_data_1000)
# mc_data_10000 = json.loads(json_mc_data_10000)
mc_data_30000 = json.loads(json_mc_data_30000)
# mc_data_100000 = json.loads(json_mc_data_100000)
# mc_data_200000 = json.loads(json_mc_data_200000)
# mc_data_300000 = json.loads(json_mc_data_300000)

# mc_data = [mc_data_1000, mc_data_10000, mc_data_30000, mc_data_100000, mc_data_200000, mc_data_300000]
mc_data = [mc_data_30000]
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