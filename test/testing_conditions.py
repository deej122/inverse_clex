import os
import shutil, errno

# renames all the json files to be the same name as the directory it was in then makes a copy into a consolidated folder 'json_calcs'
rootDir = '.'
for dirName, subdirList, files in os.walk(rootDir):
	for file in files:
		os.rename(file, subdirList)
		shutil.copy(file, 'json_calcs')

# 