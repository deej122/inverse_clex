import os
import shutil, errno

# renames all the json files to be the same name as the directory it was in then makes a copy into a consolidated folder 'json_calcs'
rootDir = '../mc_raw_data'
for dirName, subdirList, files in os.walk(rootDir):
	for filename in files:
		os.rename(filename, subdirList)
		shutil.copy(filename, 'json_calcs')

# runs all the tests with highest temp
for filename in os.listdir("json_calcs"):
	if filename.endswith('12'):
	#run the optimization
	#compare optimization if it's within a certian min squared mean then map
	job = pbs.templates.NonPrismsJob(command='python optimization.py')


# runs all the tests with lowest temp
for filename in os.listdir("json_calcs"):
	if filename.endswith('_1'):
	#run the optimization
	#compare optimization if it's within a certian min squared mean then map


# runs all the tests with transition temp
for filename in os.listdir("json_calcs"):
	if filename.endswith('7'):
	#run the optimization
	#compare optimization if it's within a certian min squared mean then map

# runs all combinations of lowest and highest temp for same dim size
for filename in os.listdir("json_calcs"):
	ECI_index = filename(7)
	dim_index = filename(9)
	if filename.endswith('_1'):
		for filename2 in os.listdir("json_calcs"):
			ECI_index2 = filename(7)
			dim_index2 = filename(9)
			if filename2.endswith('12') and ECI_index == ECI_index2 and dim_index == dim_index2:
			#run the optimization
			#compare with critical value

# runs all combinations of lowest and transition temp
for filename in os.listdir("json_calcs"):
	if filename.endswith('_1'):
		for filename2 in os.listdir("json_calcs"):
			if filename2.endswith('7') and filename(9)==filename2(9):
			#run the optimization
			#compare with critical value

# runs all combinations of highest and transition temp
for filename in os.listdir("json_calcs"):
	if filename.endswith('12'):
		for filename2 in os.listdir("json_calcs"):
			if filename2.endswith('7') and filename(9)==filename2(9):
			#run the optimization
			#compare with critical value


# runs all combinations of highest and transition temp
for filename in os.listdir("json_calcs"):
	if filename.endswith('12'):
		for filename2 in os.listdir("json_calcs"):
			if filename2.endswith('7') and filename(9)==filename2(9):
				for filename3 in os.listdir("json_calcs"):
					if filename3.endswith('_1') and filename(9)==filename3(9):
			#run the optimization
			#compare with critical value