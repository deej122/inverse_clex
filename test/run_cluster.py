import numpy as np

ECI_vec = np.array([[1,0,0], [-1,0,0], [.3,-.7,.05]])
transition_temp = 30000
temp_mult = [.001, .01, .1, .2, .5, .9, 1, 1.1, 1.5, 10, 100, 1000]
temp_vec = [transition_temp*multiple for multiple in temp_mult]
num_passes = 100000
dim_small_vec = [10, 20, 50]
dim_large_vec = [100, 1000]

for ECI in ECI_vec:
	for temperature in temp_vec:
		for small_dimensions in dim_small_vec:
			# instead having it print to screen, have some type of command that will run in the cluster
			print "ECI: ", ECI
			print "T: ", temperature
			print "Passes: ", num_passes
			print "Dimension: ", small_dimensions
		for large_dimensions in dim_large_vec:
			# instead having it print to screen, have some type of command that will run in the cluster
			print "ECI: ", ECI
			print "T: ", temperature
			print "Passes: ", num_passes
			print "Dimension: ", large_dimensions

