import numpy as np
import json
import os
import pbs


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
			# run in the cluster
			# copy all files over to flux and compile files (make execute_mc)
			eci_index = str(ECI_vec.index(ECI))
			dim_index = str(dim_small_vec.index(small_dimensions))
			temp_index = str(temp_vec.index(temperature))

			parent = os.getcwd() #find parent directory and save it (CD back to this later)
			directory = "small_" + eci_index + "_" + dim_index + "_" + temp_index #join path using os.path.join (look up how this works)
			os.chdir(parent)
			print directory
			if not os.path.exists(directory):
				os.makedirs(directory)
			os.chdir(directory) # --> create a new folder every time running with different ECI_conditions and THEN submit the job
			with open("ECI_conditions.json", "w") as outfile:
				json.dump({'Temperature': temperature, 'Dimensions': dimensions, 'Species': species, 'ECI': ECI, 'Passes': num_passes}, outfile, indent=4)
			job = pbs.templates.NonPrismsJob(command='execute_mc')
			# test it first
			print os.getcwd() #test
			print job.qsub_string() #test
		    job.submit() # --> submits job

			#CD BACK TO PARENT DIRECTORY
			os.chdir(parent)
		print "ECI: ", ECI
		print "T: ", temperature
		print "Passes: ", num_passes
		print "Dimension: ", small_dimensions
	for large_dimensions in dim_large_vec:
		dimensions = [large_dimensions, large_dimensions]
		for temperature in temp_vec:
			# run in the cluster
			# copy all files over to flux and compile files (make execute_mc)
			eci_index = str(ECI_vec.index(ECI))
			dim_index = str(dim_large_vec.index(large_dimensions))
			temp_index = str(temp_vec.index(temperature))
			parent = os.getcwd()
			directory = "large_" + eci_index + "_" + dim_index + "_" + temp_index
			os.chdir(parent)
			print directory
			if not os.path.exists(directory):
				os.makedirs(directory)
			os.chdir(directory) # --> create a new folder every time running with different ECI_conditions and THEN submit the job
			with open("ECI_conditions.json", "w") as outfile:
				json.dump({'Temperature': temperature, 'Dimensions': dimensions, 'Species': species, 'ECI': ECI, 'Passes': num_passes}, outfile, indent=4)
			job = pbs.templates.NonPrismsJob(command='execute_mc')
			# test it first
			print os.getcwd() #test
			print job.qsub_string() #test

		    job.submit() # --> submits job
			
			os.chdir(parent)

		print "ECI: ", ECI
		print "T: ", temperature
		print "Passes: ", num_passes
		print "Dimension: ", large_dimensions

