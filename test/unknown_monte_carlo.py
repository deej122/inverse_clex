import json
import subprocess

def create_mc_partial_list(file_name, file_info, percent_known):
	"""
	creates a list of partially filled matrices for monte carlo data
	file_name = name of monte carlo output file being used to generate partial matrix
	file_info = size, dimension, temperature, and eci for monte carlo output file being used
	percent_known = desired percentage of atoms to be filled in in matrix

	returns a dict of known sites for a partially filled matrix based on inputted data and percentage of atoms desired

	STRUCTURE OF THE DICT IN JSON FORMAT:
	NOTE: mc_partial_data_list is a list containing many of these ([_file{}, _file{}, _file{}]):

	_file: {
		file_name: [
			file_info: 
			{
				"Dimension": 10,
				"Temperature": 300,
				"ECI": [1,0,0],
				"Sampling_Passes": 10,
				"Equilibriation_Passes": 10000,
				"Sampling_Increment": 100,
				"Known_Sites": [
						[0,0,1],
						[1,1,0],
						[2,2,1],
					# //this format is commented out	
					# current_pass{
					# 	1: [
					# 		[0,0,1],
					# 		[1,1,0],
					# 		[2,2,1],
					# 	]
					# },
					# current_pass{
					# 	2: [
					# 		[0,0,1],
					# 		[1,1,0],
					# 		[2,2,1],
					# 	]
					# },
					# ////////////////
				]
			}
		]

	}
	"""
	_file = {file_name:[]}

	json_mc_data = open("monte_carlo_calcs.json").read()
	mc_data = json.loads(json_mc_data)
	for _pass in mc_data["Data_by_pass"]:
		#create dict consisting of list of passes
		pass_number = _pass["pass"]
		# current_pass = {pass_number:[]}
		file_info["Known_Sites"] = []
		#for each site in every object
		for atom in _pass["sites"]
			#generate random number
			random = random.random()
			#add ~known_percent of atoms to known subset for this snapshot
			if random < percent_known:
				#mc_partial_data_list is a list of files > list of passes > list of known atoms (coordinates and current occupant)
				#create object of known_atom and add it to list for this pass
				# known_atom = [{"coordinate": atom["coordinate"], "current_occupant": atom["current_occupant"]}]
				known_atom = []
				known_atom.append(atom["coordinate"][0])
				known_atom.append(atom["coordinate"][1])
				known_atom.append(atom["current_occupant"])
				file_info["Known_Sites"].append(known_atom)
				# current_pass[pass_number].append(known_atom)
			#otherwise ignore the atom
			else:
				file_info["Known_Sites"] = file_info["Known_Sites"]
				# current_pass = current_pass
		#add pass to list in this file
		# file_info["Known_Sites"] = []
		# file_info["Known_Sites"].append(current_pass)

		_file[file_name].append(file_info)

	return _file

def create_complete_mc(f_mc_partial_data_list):
	"""
	fills in missing atoms in partial_mc_data files
	f_mc_partial_data_list = list of partially filled matrices from 'create_mc_partial_list' to be filled in

	STRUCTURE OF THE DICT IN JSON FORMAT:

	"""
	for f_partial_mc_data in f_mc_partial_data_list:
		#file_name
		for _pass in f_partial_mc_data:
			#file_info
			#create a json file for every pass with known_sites, dimension, temp (depends on file), eci (depends on file), species, passes (~ 10 -> same number passes)
				#conditions.json
			data = {'known_sites': _pass["Known_Sites"], 'Dimensions': _pass["Dimensions"], 'Temperature': _pass["Temperature"], 'ECI': _pass["ECI"], 'Sampling_Passes': _pass["Sampling_Passes"], 'Equilibriation_Passes': _pass["Equilibriation_Passes"], _pass["Sampling_Increment"]}
			with open('known_species_conditions.json', 'w') as f:
				json.dump(data, f)
			subprocess.call(["unknown_monte_carlo()"])
			#read mc_data
			json_mc_full_data = open("monte_carlo_calcs.json").read()
			mc_full_data = json.loads(json_mc_full_data)
			f_mc_full_data_list.append(mc_full_data)

	return f_mc_full_data_list