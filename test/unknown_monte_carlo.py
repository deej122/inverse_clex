import json
import subprocess

def create_mc_partial_list(file_name, file_info, mc_partial_data_list):
	#create a constructor that, given a set of files, outputs a json object (conditions.json stuff from lnQ) for an [i][j] corresponding to [file][pass]
		#would be a lot easier to use and understand
		#run some tests and make sure this works well first
	_file = {file_name:[]}

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

	return _file

def create_complete_mc(f_mc_partial_data_list):
	#fill in missing atoms in partial mc_data files
	for f_partial_mc_data in f_mc_partial_data_list:
		#file_name
		for _pass in f_partial_mc_data:
			#file_info
			#create a json file for every pass with known_sites, dimension, temp (depends on file), eci (depends on file), species, passes (~ 10 -> same number passes)
				#conditions.json
			data = {'known_sites': _pass["Known_Sites"], 'Dimensions': _pass["Dimensions"], 'Temperature': _pass["Temperature"], 'ECI': _pass["ECI"]}
			with open('known_species_conditions.json', 'w') as f:
				json.dump(data, f)
			subprocess.call(["unknown_monte_carlo()"])
			#read mc_data
			json_mc_full_data = open("monte_carlo_calcs.json").read()
			mc_full_data = json.loads(json_mc_full_data)
			f_mc_full_data_list.append(mc_full_data)

	return f_mc_full_data_list