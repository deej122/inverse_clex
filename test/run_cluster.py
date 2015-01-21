import numpy as np
import json

ECI_vec = [[1,0,0], [-1,0,0], [.3,-.7,.05]]
transition_temp = 30000
temp_mult = [.001, .01, .1, .2, .5, .9, 1, 1.1, 1.5, 10, 100, 1000]
temp_vec = [transition_temp*multiple for multiple in temp_mult]
num_passes = 100000
dim_small_vec = [10, 20, 50]
dim_large_vec = [100, 1000]
species = [1, -1]
for ECI in ECI_vec:
	print ECI
	for small_dimensions in dim_small_vec:
		dimensions = [small_dimensions, small_dimensions]
		for temperature in temp_vec:
			with open("ECI_conditions.json", "w") as outfile:
				json.dump({'Temperature': temperature, 'Dimensions': dimensions, 'Species': species, 'ECI': ECI, 'Passes': num_passes}, outfile, indent=4)
			# run in the cluster
		print "ECI: ", ECI
		print "T: ", temperature
		print "Passes: ", num_passes
		print "Dimension: ", small_dimensions
	for large_dimensions in dim_large_vec:
		dimensions = [large_dimensions, large_dimensions]
		for temperature in temp_vec:
			with open("ECI_conditions.json", "w") as outfile:
				json.dump({'Temperature': temperature, 'Dimensions': dimensions, 'Species': species, 'ECI': ECI, 'Passes': num_passes}, outfile, indent=4)
			# run in the cluster
		print "ECI: ", ECI
		print "T: ", temperature
		print "Passes: ", num_passes
		print "Dimension: ", large_dimensions

